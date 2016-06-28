//client
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>

void read_info(int csocket, int psize, char *cipher);	
void send_info(int csocket, int ksize, char *key, int csize, char* cipher);
//int newSocket(int nsocket, struct sockaddr_in serv_addr,struct hostent *server, int newPort);

void error(const char *msg)
{
	perror(msg);
	exit(2);	
}

int main(int argc, char *argv[]){

	int csocket, nsocket, portNum, write_result, read_result;
	struct sockaddr_in serv_addr;
	struct hostent *server;

	char *plaintext = NULL;
	
	if (argc < 3){
		fprintf(stderr, "Not Enough Arguments\n");
		exit(1);
	}	
	
	//set up buffer
	char *ciphertext = NULL;
	size_t csize = 0;
	//open plaintext
	FILE *fpc = fopen(argv[1], "r");
	//go to end
	fseek(fpc, 0, SEEK_END);
	//get size
	csize = ftell(fpc);
	//go back to beginning
	rewind(fpc);
	//allocate the buffer
	ciphertext = malloc((csize + 1) * sizeof(*ciphertext));
	//read file into the buffer
	fread(ciphertext, csize, 1, fpc);
	
	///set up buffer
	char *key = NULL;
	size_t ksize = 0;
	//open keyfile
	FILE *fpk = fopen(argv[2], "r");
	//go to end
	fseek(fpk, 0, SEEK_END);
	//get size
	ksize = ftell(fpk);
	//go back to beginning
	rewind(fpk);
	//allocate the buffer
	key = malloc((ksize + 1) * sizeof(*key));
	//read file into the buffer
	fread(key, ksize, 1, fpk);

	//get port number
	//printf("%s\n", argv[3]);
	if(sscanf (argv[3], "%i", &portNum) != 1){
		error("Please enter a valid integer\n");
		exit(1);
	}
	//open socket
	csocket = socket(AF_INET, SOCK_STREAM, 0);
	//check if socket is valid
	if(csocket < 0)
		error("error: opening socket\n");
	server = gethostbyname("localhost");
	if(server == NULL){
		error("Host Doesn't Exist\n");
	}
	//clear serv_addr
	bzero((char *) &serv_addr, sizeof(serv_addr));
	//set variable for serv_addr struct
	serv_addr.sin_family = AF_INET;
	bcopy((char *)server->h_addr, (char *)&serv_addr.sin_addr.s_addr, server->h_length);
	serv_addr.sin_port = htons(portNum);
	
	//connect function
	if(connect(csocket, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0 )
		error("error: connecting\n");
	
	//check if valid connection
	char type[] = "decrypt";
	char rType[10];
	read_result = recv(csocket, rType, sizeof(rType), 0);
	if (read_result < 0){
		error("error reading type decrypt from socket\n");
	}
	if(strcmp(type, rType) != 0){
		fprintf(stderr, "Cannot Connect to Encrypt Program\n");
		exit(1);
	}
	//get newPort
	int newPort;
	read_result = recv(csocket, &newPort, sizeof(newPort), 0);
	if (read_result < 0){
		error("error reading port number from socket\n");
	}
	newPort = ntohl(newPort);
	//printf("New Port Sent:  %d\n", newPort);
	
	//printf("Closing old socket\n");
	//close old socket	
	close(csocket);
	
	//open new socket
	nsocket = socket(AF_INET, SOCK_STREAM, 0);
	//check if socket is valid
	if(nsocket < 0)
		error("error: opening new socket\n");
	
			
	//clear serv_addr
	bzero((char *) &serv_addr, sizeof(serv_addr));
	
	//fill serv_addr struct
	serv_addr.sin_family = AF_INET;
	bcopy((char *)server->h_addr, (char *)&serv_addr.sin_addr.s_addr, server->h_length);
	serv_addr.sin_port = htons(newPort);
	
	//connect function
	if(connect(nsocket, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0 )
		error("error: connecting socket 2d\n");

	//printf("New Socket connected at Port Num: %d", newPort);
	
	
	send_info(nsocket, ksize, key, csize, ciphertext);
	//get returned plaintext
	plaintext = malloc((csize + 1) * sizeof(*plaintext));
	read_info(nsocket, csize, plaintext);
	//}
	printf("%s\n", plaintext);
	
	close(nsocket);
	free(plaintext);
	free(ciphertext);
	free(key);	
return 0;
}

/**********************************************************************
 * Purpose: Read Info from socket
 * Input: Socket FD, cipher input size, plaintext pointer
 * Output: Updated plaintext with decrypted text
 * *******************************************************************/

void read_info(int csocket, int csize, char *plaintext){
	
	int read_result;
	int premainder = csize;
	while(((read_result = recv(csocket, plaintext, csize, 0)) > 0 && premainder > 0)){	
		//printf("w: %d\n", write_result);
		premainder -= read_result;
		if (read_result < 0){error("Error reading plaintext from socket\n");}
	}

}

/**********************************************************************
 * Purpose: Send info through socket
 * Input: Socket FD, key size, key, cipher size, ciphertext
 * Output: Sends cipher text to server
 * *******************************************************************/


void send_info(int csocket, int ksize, char *key, int csize, char* ciphertext){
	
	int write_result;	
	
	//send cipher size
	int cCsize = htonl(csize);
	//send cipher size
	write_result = send(csocket, &cCsize, sizeof(cCsize), 0);
	if (write_result < 0){error("Error writing to cipher size to socket\n");}
	

	//send plaintext
	ciphertext[strcspn(ciphertext, "\r\n")] = 0;
	int cremainder = csize; 
	//send whole cipher to server
	while(((write_result = send(csocket, ciphertext, csize, 0)) > 0 && cremainder > 0)){	
		//printf("w: %d\n", write_result);
		cremainder -= write_result;
		if (write_result < 0){error("Error writing ciphertext to socket\n");}
	}

	//send key size
	int cKsize = htonl(ksize);
	//send key size
	write_result = send(csocket, &cKsize, sizeof(cKsize), 0);
	if (write_result < 0){error("Error writing key size to socket\n");}
	

	//send key
	key[strcspn(key, "\r\n")] = 0;
	int kremainder = ksize;
	//send key
	while(((write_result = send(csocket, key, ksize, 0)) > 0 && kremainder > 0)){	
		//printf("w: %d\n", write_result);
		kremainder -= write_result;
		if (write_result < 0){error("Error writing key to socket\n");}
	}


}

/**********************************************************************
 * Purpose: Get a new socket
 * Input: None
 * Output: An int representing success or failure
 * *******************************************************************/
/*int newSocket(int nsocket, struct sockaddr_in serv_addr, struct hostent *server, int newPort){
	//int nsocket;
	//open new socket
	//nsocket = socket(AF_INET, SOCK_STREAM, 0);
	//check if socket is valid
	
	//clear serv_addr
	bzero((char *) &serv_addr, sizeof(serv_addr));
	
	//fill serv_addr struct
	serv_addr.sin_family = AF_INET;
	bcopy((char *)server->h_addr, (char *)&serv_addr.sin_addr.s_addr, server->h_length);
	serv_addr.sin_port = htons(newPort);
	
	//connect function
	if(connect(nsocket, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0 ){		
		close(nsocket);
		fprintf(stderr, "error: connecting socket 2d\n");
		return -1;
	}	
	return nsocket;
}*/
	
