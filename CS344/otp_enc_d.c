//server code
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

#define NUMLETTERS 27

void encrypt(char *plain, char *cipher, char *key, int psize);
void newConnection(int portNum);
int getLetterNum(char let, char letters[]);
char getCharAtPos(int pos, char letters[]);
int mod(int a, int b);

char *read_info(int socket, int size, char *input);
void send_info(int socket, int size, char *output);

//error fuction
void error(const char *msg)
{
	perror(msg);
	exit(2);	
}

int main(int argc, char *argv[]){

	int sockfd, newsocket, portNum, newPort;
	int psize = 0;
	int ksize = 0;

	socklen_t clientLen;
	char *plaintext = NULL;
	char *key = NULL;
	char *cipher = NULL;

	struct sockaddr_in serv_addr, cli_addr;
	int read_result, write_result;

	if (argc < 2){
		fprintf(stderr, "No Port Provided\n");
		exit(1);
	}
	//socket
	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	//if sockfd = -1
	if (sockfd < 0){
		error("error opening socket 1\n");
	}

	bzero((char *) &serv_addr, sizeof(serv_addr));
	
	if(sscanf (argv[1], "%i", &portNum) != 1){
		fprintf(stderr ,"Please enter a valid integer");
		exit(1);
	}
	
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_addr.s_addr = INADDR_ANY;
	serv_addr.sin_port = htons(portNum);
	
	//bind
	if (bind(sockfd, (struct sockaddr* ) &serv_addr, sizeof(serv_addr)) < 0){
		error("Bind 1 Failed\n");
	}
	
	//listen
	listen(sockfd, 5);
	clientLen = sizeof(cli_addr);
	
	while((newsocket = accept(sockfd, (struct sockaddr *) &cli_addr, &clientLen)) > 0){
		portNum = portNum + 5;
		newPort = portNum;
		//accept connection
		//if it didn't connect print error
		;	
		
		if(newsocket < 0){
			error("Accept 1 Failed\n");
		}
		
		//send type
		char type[] = "encrypt";
		write_result = send(newsocket, type, sizeof(type), 0);
		if (write_result < 0){
			error("error reading encrypt type from socket\n");
		}

		//create fork and child
		pid_t cpid = fork();
		if(cpid < 0){
			error("Error on fork\n");
		}	
		if(cpid == 0){
			//printf("In child\n");		
			//in child
			int convertPort = htonl(newPort);
			write_result = send(newsocket, &convertPort, sizeof(convertPort), 0);
			if (write_result < 0){
				error("error reading new port from socket\n");
			}
			//printf("New Port Sent: %d\n", newPort);	
			//tell kernel i'm willing to reuse port
			int yes = 1;
			if(setsockopt(newsocket, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(yes)) ==-1)
				error("setsockopt");


			close(newsocket);
			newConnection(portNum);
		}
	}	
	free(cipher);	

return 0;
}


/**********************************************************************
 * Purpose: Encrypts plaintext to cipher text
 * Input: Pointers to text array, empty cipher array, key and size of
 * 	  plaintext
 * Output: Updates cipher to encrypted version of plaintext
 * *******************************************************************/

void encrypt(char *text, char *cipher, char *key, int size){
	int i, pos, kpos;	
	char letters[NUMLETTERS] = {'A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z',' '};
	//encrypt
	for (i = 0; i < size; i++){
		//get letter position
		pos = getLetterNum(text[i], letters);
		//key key position			
		kpos = getLetterNum(key[i], letters);
		//send to modulus function
		int new = mod(pos, kpos);
		//get encrypted character
		char enc = getCharAtPos(new, letters);
		//if pos is valid write letter to cipher and advance
		if (pos != -1){
			cipher[i] = enc;
		}						
	}
}


/**********************************************************************
 * Purpose: Get number corresponding to letter based on character array
 * Input: Letter and Character Array
 * Output: Integer represeting position
 * *******************************************************************/

int getLetterNum(char let, char letters[]){
	int i;
	for(i = 0; i < NUMLETTERS; i++){
		if(letters[i] == let){
			return i;
		}
	}
	return -1;
}


/**********************************************************************
 * Purpose: Get character represented at position of char array O(1)
 * Input: Position and Char Array
 * Output: Returns Char that represents keyed position
 * *******************************************************************/

char getCharAtPos(int pos, char letters[]){
		return letters[pos];
}

/**********************************************************************
 * Purpose: Calculate Modulus of addition in range 
 * Input: Two Ints
 * Output: Final Mod Position
 * *******************************************************************/

int mod(int a, int b){
	if(a + b > 26){
		return (a + b - 27);
	}
	else
		return a + b;
}

/**********************************************************************
 * Purpose: Read info from client
 * Input: Socket position, input size and input array
 * Output: Returns input
 * *******************************************************************/


char* read_info(int nsocket, int size, char *input){
	int read_result;
	int cremainder = size;
	//get input from client
 	while((read_result = recv(nsocket, input, size, 0)) > 0 && (cremainder > 0)){
		//printf("Reading Key");
		//printf("r: %d\n", read_result);
		cremainder -= read_result;
		if (read_result < 0){error("error reading plaintext or key from socket\n");}
	}
	return input;
}


/**********************************************************************
 * Purpose: Write output to client
 * Input: Socket File Descriptor, output size, pointer to output
 * Output: None, sends output to client
 * *******************************************************************/

void send_info(int nsocket, int size, char *output){
	int write_result;
	int cremainder = size;
	while((write_result = send(nsocket, output, size, 0)) > 0 && (cremainder > 0)){
		cremainder -= write_result;
		if (write_result < 0){error("error writing cipher to socket\n");}
	}
}

/**********************************************************************
 * Purpose: Create new connection with forked process
 * Input: New Port Number
 * Output: None
 * *******************************************************************/

void newConnection(int portNum){
	
	char *plaintext = NULL;
	char *key = NULL;
	char *cipher = NULL;
	int psize = 0;
	int ksize = 0;


	int socket2, socket3, read_result, write_result;
	socklen_t clilen;
	struct sockaddr_in serv_addr, cli_addr;
	int n;
	//printf("In Function\n");
	socket2 = socket(AF_INET, SOCK_STREAM, 0);
	if(socket2 < 0){
		error("error opening new socket\n");
	}	

	bzero((char *) &serv_addr, sizeof(serv_addr));
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_addr.s_addr = INADDR_ANY;
	serv_addr.sin_port = htons(portNum);
	
	//tell kernel i'm willing to reuse port
	int yes = 1;
	if(setsockopt(socket2, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(yes)) ==-1)
		error("setsockopt");

	//printf("Binding\n");
	//bind
	if (bind(socket2, (struct sockaddr* ) &serv_addr, sizeof(serv_addr)) < 0){
		perror("Bind 2 Failed e\n");
		exit(1);
	}
	
	//listen
	//printf("Listening\n");
	listen(socket2, 5);
	clilen = sizeof(cli_addr);

	//printf("Accepting\n");
	socket3 = accept(socket2, (struct sockaddr *)&cli_addr, &clilen);
	if (socket3 < 0){
		error("error on Accept 2\n");
	}
	//printf("Accepted\n");
 	//get size
	read_result = recv(socket3, &psize, sizeof(psize), 0);		
	if (read_result < 0){
		error("error reading plaintext size from socket 2\n");
	}
	psize = ntohl(psize);
	//printf("%d\n", psize);
 	
	//get plaintext from client
	plaintext = malloc((psize + 1) * sizeof(*plaintext));
 	plaintext = read_info(socket3, psize, plaintext);
	
	//get key size from client
	read_result = recv(socket3, &ksize, sizeof(ksize), 0);		
	if (read_result < 0){
		error("error reading key size from socket 2\n");
	}
	ksize = ntohl(ksize);
 	
	//get key from client
	key = malloc((ksize + 1) * sizeof(*key));
	key = read_info(socket3, ksize, key);
	
	//allocate cipher
	cipher = malloc((psize + 1) * sizeof(*cipher));
		
	//encrypt file
	encrypt(plaintext, cipher, key, psize);
	
		
	//write back cipher to client	
	send_info(socket3, psize, cipher);
	
	close(socket2);
	close(socket3);	
	_exit(0);
}
