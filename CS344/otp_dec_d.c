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

void decrypt(char *cipher, char *plaintext, char *key, int psize);
char getCharAtPos(int pos, char letters[]);
int getLetterNum(char letter, char letters[]);
int mod(int a, int b);
void newConnection(int);
char *read_info(int socket, int size, char *input);
void send_info(int socket, int size, char *output);


void error(const char *msg)
{
	perror(msg);
	exit(2);	
}


int main(int argc, char *argv[]){
	
	int sockfd, newsocket, portNum, newPort;

	socklen_t clientLen;
	char *ciphertext = NULL;
	char *key = NULL;
	char *plaintext = NULL;	
	
	struct sockaddr_in serv_addr, cli_addr;
	int read_result, write_result;
	
	int csize = 0;
	int ksize = 0;

	if (argc < 2){
		fprintf(stderr ,"No Port Provided\n");
		exit(1);
	}
	
	//socket
	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	//if sockfd = -1
	if (sockfd < 0){
		error("error opening socket\n");
	}

	bzero((char *) &serv_addr, sizeof(serv_addr));
	
	//get port	
	if(sscanf (argv[1], "%i", &portNum) != 1){
		fprintf(stderr, "Please enter a valid integer\n");
		exit(1);
	}
	
	//set variable for serv_addr_in
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_addr.s_addr = INADDR_ANY;
	serv_addr.sin_port = htons(portNum);
	//bind
	if (bind(sockfd, (struct sockaddr* ) &serv_addr, sizeof(serv_addr)) < 0){
		error("Bind Failed\n");
	}
	
	//listen
	listen(sockfd, 5);
	clientLen = sizeof(cli_addr);
	while((newsocket = accept(sockfd, (struct sockaddr *) &cli_addr, &clientLen)) > 0){
		portNum = portNum + 5;
		newPort = portNum;
		//accept connection
		
		//if it didn't connect print error
		if(newsocket < 0){
			error("Accept 1 Failed\n");
		}
		//send type
		char type[] = "decrypt";
		write_result = send(newsocket, type, sizeof(type), 0);
		if (write_result < 0){
			error("error reading type from socket\n");
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
			_exit(0);
		}
	}
	free(plaintext);
	free(ciphertext);
	free(key);
return 0;
}
/**********************************************************************
 * Purpose: Decrypt cipher to plaintext
 * Input: ciphertext, empty plaintext, key and size of cipher
 * Output: Decrypted Plaintext
 * *******************************************************************/
void decrypt(char *text, char *plaintext, char *key, int size){
	int i, pos, kpos;	
	char letters[NUMLETTERS] = {'A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z',' '};
	for (i = 0; i < size; i++){
		//get position of cipher letter
		pos = getLetterNum(text[i], letters);
		//if (pos != -1)
			//printf("%c ", getCharAtPos(pos, letters));
		//get position of key letter
		kpos = getLetterNum(key[i], letters);
		//if (kpos != -1)
		//	printf("%d ", kpos);
		//send positions to custom modulus function
		int new = mod(pos, kpos);		
		//printf("%d \n",new);
		//printf("%d \n",new);
		//get decrypted character
		char dec = getCharAtPos(new, letters);
		//if character is valid write to plaintext
		if (pos != -1){
			plaintext[i] = dec;
			//printf("%c", dec);
			//printf("%d \n",new);
		}
	}
}
/**********************************************************************
 * Purpose: Get letter position based on char array of letters
 * Input: Letter and Char Array
 * Output: Return Postion of letter
 * *******************************************************************/
int getLetterNum(char letter, char letters[]){
	int i;
	for(i = 0; i < NUMLETTERS; i++){
		if(letters[i] == letter){
			return i;
		}
	}
	return -1;
}
/**********************************************************************
 * Purpose: Get char at pos in char array
 * Input: position and char array
 * Output: returns char at pos
 *
 * *******************************************************************/
char getCharAtPos(int pos, char letters[]){
		return letters[pos];
}

/**********************************************************************
 * Purpose: custom % function subract ints and if less than zero
 * 	return difference
 * Input: Two ints
 * Output: new position
 * *******************************************************************/

int mod(int a, int b){
	if(a - b < 0){
		//x = x + 26;
		//printf("%d", x);
		return (a - b + 27);
	}
	else{
		//printf("%d", x);
		return a - b;
	}
}

/**********************************************************************
 * Purpose: read info from network socket
 * Input: Socket fd, size of input, input char pointer
 * Output: Returns input
 * *******************************************************************/


char* read_info(int socket, int size, char *input){
	int read_result;
	int cremainder = size;
 	while((read_result = recv(socket, input, size, 0)) > 0 && (cremainder > 0)){
		//printf("Reading Key");
		//printf("r: %d\n", read_result);
		cremainder -= read_result;
		if (read_result < 0){error("error reading input from socket\n");}
	}
	return input;
}

/**********************************************************************
 * Purpose: Send info to socket fd
 * Input: socket fd, size of output, char pointer with output
 * Output: None
 * *******************************************************************/

void send_info(int socket, int size, char *output){
	int write_result;
	int cremainder = size;
	while((write_result = send(socket, output, size, 0)) > 0 && (cremainder > 0)){
		cremainder -= write_result;
		if (write_result < 0){error("error writing cipher to socket\n");}
	}
}


/**********************************************************************
 * Purpose: Create new connection for forked process with client
 * 	and use to send and receive info
 * Input: New Port Number
 * Output: None
 *
 * *******************************************************************/

void newConnection(int portNum){
	
	char *plaintext = NULL;
	char *key = NULL;
	char *ciphertext = NULL;
	int csize = 0;
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
	//set serv_addr_in variables
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
		error("Bind 2 Failed d\n");
	}
	
	//listen
	//printf("Listening\n");
	listen(socket2, 5);
	clilen = sizeof(cli_addr);
	
	//printf("Accepting\n");
	socket3 = accept(socket2, (struct sockaddr *)&cli_addr, &clilen);
	if (socket3 < 0){
		close(socket3);
		error("error on Accept 2\n");
		//return -1;
	}
	//get ciphertext size
 	read_result = recv(socket3, &csize, sizeof(csize), 0);		
	if (read_result < 0){
		error("error reading cipher text size from socket 2\n");
	}
	csize = ntohl(csize);
	//printf("%d\n", csize);
 	
	//get ciphertext
	ciphertext = malloc((csize + 1) * sizeof(*ciphertext));
 	ciphertext = read_info(socket3, csize, ciphertext);
	
	//get key size
	read_result = recv(socket3, &ksize, sizeof(ksize), 0);		
	if (read_result < 0){
		error("error reading key size from socket 2\n");
	}
	ksize = ntohl(ksize);
	
	//get key
 	key = malloc((ksize + 1) * sizeof(*key));
	key = read_info(socket3, ksize, key);
	
	//decrypt file
	plaintext = malloc((csize + 1) * sizeof(*plaintext));
	decrypt(ciphertext, plaintext, key, csize);
	
	//send plaintext back
	send_info(socket3, csize, plaintext);
	
	close(socket2);
	close(socket3);
	
}
