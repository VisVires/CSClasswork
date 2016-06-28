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

#define NUMLETTERS 27

int validChar(char let);
void read_info(int csocket, int psize, char *cipher);	
void send_info(int csocket, int ksize, char *key, int psize, char* plaintext);

//error fuction
void error(const char *msg)
{
	perror(msg);
	exit(2);	
}



int main(int argc, char* argv[]){

	int csocket, nsocket, portNum, write_result, read_result ,j;
	struct sockaddr_in serv_addr, serv_addr2;
	struct hostent *server;

	char *cipher;// = NULL;
	

	//check number of arguments
	if(argc < 3){
		fprintf(stderr, "Not enough arguments\n");
		exit(1);
	}

	//set up buffer
	char *plaintext = NULL;
	size_t psize = 0;
	//open plaintext
	FILE *fpp = fopen(argv[1], "r");
	//go to end
	fseek(fpp, 0, SEEK_END);
	//get size
	psize = ftell(fpp);
	//go back to beginning
	rewind(fpp);
	//allocate the buffer
	plaintext = malloc((psize + 1) * sizeof(*plaintext));
	//read file into the buffer
	fread(plaintext, psize, 1, fpp);
	//check if valid
	//plaintext[strcspn(plaintext, "\r\n")] = 0;	
	for(j = 0; j < psize; j++){
		if(!validChar(plaintext[j])){
			fprintf(stderr, "error: input contains bad characters\n");
			exit(1);
		}
	}
	fclose(fpp);


	//get key from file
	char *key = NULL;
	size_t ksize = 0;
	//open keyfile
	FILE *fpk = fopen(argv[2], "r");
	//go to end
	fseek(fpk, 0, SEEK_END);
	//get size
	ksize = ftell(fpk);
	//check that key is larger than file
	if(ksize < psize){
		fprintf(stderr, "Error: key \"%s\" is too short\n", argv[2]);
		exit(1);
	}
	//go back to beginning
	fseek(fpk, SEEK_SET, 0);
	//allocate the buffer
	key = malloc((ksize + 1) * sizeof(*key));
	//read file into the buffer
	//size_t nread;
	fread(key, ksize, 1, fpk);
	//printf("Num of bytes: %d\n", read_bytes);
	//printf("%s\n" ,key);
	fclose(fpk);	
	
	
	//get port number
	if(sscanf (argv[3], "%i", &portNum) != 1){
		fprintf(stderr, "Please enter a valid integer\n");
		exit(1);
	}
	
	//open socket
	csocket = socket(AF_INET, SOCK_STREAM, 0);
	
	//check if socket is valid
	if(csocket < 0)
		error("error: opening socket\n");
	
	//set host server
	server = gethostbyname("localhost");
	if(server == NULL){
		error("Host Doesn't Exist\n");
	}
	
	//clear serv_addr
	bzero((char *) &serv_addr, sizeof(serv_addr));
	
	//fill serv_addr struct
	serv_addr.sin_family = AF_INET;
	bcopy((char *)server->h_addr, (char *)&serv_addr.sin_addr.s_addr, server->h_length);
	serv_addr.sin_port = htons(portNum);
	
	//connect function
	if(connect(csocket, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0 )
		error("error: connecting socket 1\n");
	
	//check if valid connection
	char type[] = "encrypt";
	char rType[10];
	read_result = recv(csocket, rType, sizeof(rType), 0);
	if (read_result < 0){
		error("error reading type encrypt from socket\n");
	}
	if(strcmp(type, rType) != 0){
		fprintf(stderr, "Cannot connect to decrypt program\n");
		exit(1);
	}


	int newPort;
	read_result = recv(csocket, &newPort, sizeof(newPort), 0);
	if (read_result < 0){
		error("error reading new port number from socket\n");
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

	//printf("Connecting");	
	//connect function
	if(connect(nsocket, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0 )
		error("error: connecting socket 2e\n");

	//printf("New Socket connected at Port Num: %d", newPort);
	
	//send plaintext and key to client
	send_info(nsocket, ksize, key, psize, plaintext);
	
	//get returned cipher
	cipher = malloc((psize + 1) * sizeof(*cipher));
	
	//read cipher from client
	read_info(nsocket, psize, cipher);	
	
	//printf("reading result");
	fprintf(stdout, "%s\n", cipher);

	close(nsocket);
	free(key);
	free(plaintext);
	free(cipher); 
return 0;
}


/**********************************************************************
 * Purpose: Check if characters in plaintext are valid for encryption
 * Input: The letter
 * Output: Bool for valid or invalid
 * *******************************************************************/

int validChar(char let){
	int i;
	//define valid letters
	char letters[NUMLETTERS] = {'A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z',' '};
	//check validity
	for(i = 0; i < NUMLETTERS; i++){
		if(letters[i] == let || let == '\n'){			
			return 1;
		}
	}
	return 0;
}

/**********************************************************************
 *Purpose: Get cipher from otp_enc_d.c
 *Input: Socket File Descriptor, Plaintext Size and Pointer to Cipher
 *Output: None	
 * *******************************************************************/


void read_info(int nsocket, int psize, char *cipher){

	int read_result;	
	//get returned cipher
	int cremainder = psize;
	//cipher = malloc((psize + 1) * sizeof(*cipher));
	//get cipher
	while(((read_result = recv(nsocket, cipher, psize, 0)) > 0 && cremainder > 0)){	
		cremainder -= read_result;
		if (read_result < 0){error("Error reading cipher from socket\n");}
	}
}

/**********************************************************************
 * Purpose: Send Plaintext and Key to otp_enc_d.c to calculate cipher
 * Input: Socket FD, key size, key, plaintext size, plaintext
 * Output: Outputs to otp_enc_d.c
 * *******************************************************************/


void send_info(int nsocket, int ksize, char *key, int psize, char* plaintext){
	
	int write_result;
	int cPsize = htonl(psize);
	//send plaintexr size
	write_result = send(nsocket, &cPsize, sizeof(cPsize), 0);
	if (write_result < 0){error("Error writing to plaintext size to socket\n");}
	//send plaintext
	plaintext[strcspn(plaintext, "\r\n")] = 0;	
	
	int premainder = psize;
	//send plaintext
	while(((write_result = send(nsocket, plaintext, psize, 0)) > 0 && premainder > 0)){	
		//printf("w: %d\n", write_result);
		premainder -= write_result;
		if (write_result < 0){error("Error writing plaintext to socket\n");}
	}
	//send size of key
	//printf("%d\n", ksize);
	int cKsize = htonl(ksize);
	//send key size
	write_result = send(nsocket, &cKsize, sizeof(cKsize), 0);
	if (write_result < 0){error("Error writing key size to socket\n");}
	
	//send key
	//strip newline
	//printf("%s\n", key);
	key[strcspn(key, "\r\n")] = 0;
	int kremainder = ksize;
	//send key
	while(((write_result = send(nsocket, key, ksize, 0)) > 0 && kremainder > 0)){	
		//printf("remainder: %d\n", kremainder);
		//printf("w: %d\n", write_result);
		kremainder -= write_result;
		//printf("remainder: %d\n", kremainder);
		if (write_result < 0){error("Error writing key to socket\n");}
	}
}
