#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <time.h>
#include <sys/types.h>
#include <signal.h>
#include <unistd.h>
#include <errno.h>
#include <fcntl.h>

#define MAX_ARGS 512
#define MAX_CHARS 2048

int waitMethod(pid_t childPid);
int bProcess(pid_t resultPid, int *bpids, int bpidSize, int input, int output, int infd, int outfd, char *commands[], int *status);
int fProcess(pid_t resultPid, int input, int output, int infd, int outfd, char *commands[], int *status, struct sigaction *actN);
static int getInput(char *buff, size_t sz);
void prompt(int *bpids, int bpidSize, int status);
void changeDir(char *commands[]);
void exitFxn();
int getTermInfo(int status);


int main(){

int infd = 0;
int outfd = 0;
char *bg = "&";
char *in = "<";
char *out = ">";
char *leave = "exit";
char *stat = "status";
static int status;
char *change = "cd";
int exitShell = 0;
int forkCount = 0;
int args,i;
char **commands;
struct sigaction actN;
actN.sa_handler = SIG_IGN; 
//set signal handler
sigaction(SIGINT, &actN, NULL);

//create array to hold background pids
int *bpids;
int bpidSize = 0;
const int bpidCount = 1000;
bpids = malloc(sizeof(int) * bpidCount);
//check if valid
if(!bpids){
	perror("Error allocating memory");
	abort();
}
//set atexit fxn
atexit(exitFxn);
//continue until exit statement
while(!exitShell && forkCount < 100){
	char *input_file, *output_file;			//file names
	char buff[MAX_CHARS];				//buffer for user input
	int validInput = 1;				
	int j;			
	int input = 0;					//bool for input symbol
	int output = 0;					//boolean for output symbol
	int invalid = 0;				//boolean for valid file
	//create array for commands
	commands = malloc(sizeof(char *) * (MAX_ARGS + 1));
	if(!commands){
		perror("Error allocating memory");
		abort();
	}
	
	int background = 0;				//set boolean for background
	size_t sz = sizeof(buff);			//set size of buffer
	

	//prompt user and get valid input
	while(validInput == 1){	
		prompt(bpids, bpidSize, status);
		validInput = getInput(buff, sz);
		//printf("%s", buff);	
	}	
	
	//save command to character array
	char *token = strtok(buff, " ");
	i = 0;
	//continue until buffer is empty and not == 512 Args
	while (token != NULL && i != MAX_ARGS - 1){
		//printf("[%s]\n", token);
		//strip any \n
		token[strcspn(token, "\r\n")] = 0;
		//check if argument is an input and get file name
		if(strcmp(token, in) == 0){
			//set input to true
			input = 1;
			token = strtok(NULL, " ");
			//check if input file is specified
			if (token != NULL && (strcmp(token, out) != 0 && strcmp(token,bg) != 0)){
				input_file = token;
				//strip trailing newLine for first item
				input_file[strcspn(input_file, "\r\n")] = 0;
				//set input file number
				infd = open(input_file, O_RDONLY);
				if(infd < 0){
					printf("Cannot open %s for input\n", input_file);
					fflush(stdout);
					status = 1;
					invalid = 1;
				}
				if (token != NULL)
					token = strtok(NULL, " ");
			}
		}
		//check if argument is an output and get file name
		else if(strcmp(token, out) == 0){
			//set output to true
			output = 1;
			token = strtok(NULL, " ");
			//check if output file is specified
			if(token != NULL && (strcmp(token, out) != 0 && strcmp(token, bg) != 0)){
				output_file = token;
				//strip trailing newLine
				output_file[strcspn(output_file, "\r\n")] = 0;
				//set up output file
				outfd = open(output_file, O_CREAT | O_WRONLY | O_TRUNC, 0644);
				if(outfd < 0){
					//perror(input_file);
					printf("Cannot open %s for input\n", input_file);
					fflush(stdout);
					status = 1;
					invalid = 1;
				}
				if (token != NULL)
					token = strtok(NULL, " ");
			}
		}
		//check if argument is a background arg and set background to 1
		else if(strcmp(token, bg) == 0){
			background = 1;
			break;
		}
		//place arg in arg array
		else{ 
			//allocate memory for each command and place into array
			commands[i] = malloc(strlen(token + 1));
			strcpy(commands[i], token);	
			token = strtok(NULL, " ");
			i++;
		}
	}

	
		//set number of args to number of entries into array
		args = i;
		//error check for background
		/*if(background){
			printf("something is happening in the back yo!!");
		}*/

		//strip trailing newLine for first item
		commands[0][strcspn(commands[0], "\r\n")] = 0;
	
		//check input for special characters and choose appropriate fxn
		if (strcmp(commands[0], change) == 0){
			changeDir(commands);		
		}
		//check if status command
		else if (strcmp(commands[0], stat) == 0){
			if(status == 0 || status == 1){
				printf("exit value %d\n", status);
				fflush(stdout);
			}	
			else{
				printf("terminated by signal %d\n", status);	
				fflush(stdout);
			}
		}
		//check if exit command	
		else if (strcmp(commands[0], leave) == 0){
			int k;
			exitShell = 1;	
		}
		//not predefined run value through fork dup exec
		else{
			//if file descriptor is valid continue
			if(invalid == 0){
				for (i = 0; i < args; i++) {
					//strip newLine characters		
					commands[i][strcspn(commands[i], "\r\n")] = 0;
					//printf("%s ", commands[i]);
				}
				//add NULL terminator to array
				i++;
				commands[i] = NULL;

				//fork parent process and send to either foreground or background
				pid_t resultPid = fork();
				forkCount++;
				if (background){
					//if no specified input file send to dev/null
					if(input && !infd){
						infd = open("/dev/null", O_RDONLY);
					}
					//if no specified output send to dev/null
					if(output && !outfd){
						outfd = open("dev/null", O_WRONLY);
					}
					//send to background process and get number of running background processes
					bpidSize = bProcess(resultPid, bpids, bpidSize, input, output, infd, outfd, commands, &status);
				}
				//in foreground
				else{
					//if input file doesn't exist
					if(infd < 0){
						input = 0;
					}
					//if output file doesn't exits
					if(outfd < 0){
						output = 0;
					}
					//send to foreground process function	
					status = fProcess(resultPid, input, output, infd, outfd, commands, &status, &actN);
				
					//reset handler in parent
					actN.sa_handler = SIG_IGN;
					sigaction(SIGINT, &actN, NULL);
				}
			}//end if
		}//end else
}//end while

//free allocated memory
if(commands != NULL){
	free(commands);	
}
//free bpids
if (bpids != NULL){
	free(bpids);
}

return 0;
}

//output user prompt and if background function has executed
void prompt(int *bpids, int bpidSize, int status){
	int i, exitStatus;
	for(i = 0; i < bpidSize; i++){
		//printf("Background Processes: %d\n", bpids[i]);	
		if (waitpid(bpids[i], &status, WNOHANG) != 0 && bpids[i] != -1){
				printf("background pid %d is done: ", bpids[i]);
				bpids[i] = -1;
			//if valid exit
			if (WIFEXITED(status)){
				exitStatus = WEXITSTATUS(status);	
				printf("exit value %d\n", exitStatus);
			}
			//if terminated by signal
			else if (WIFSIGNALED(status)){
				exitStatus = status;
				//exitStatus = WTERMSIG(status);
				printf("terminated by signal %d\n", exitStatus);
			}
		}
	}
	fflush(stdout);
	printf(": ");
	fflush(stdout);
}

//get user input and check if blank or if comment
static int getInput(char *buff, size_t sz){
	
	char comment = '#';

	//get input from stdin
	fgets(buff, sz, stdin);
	
	//check if input is empty
	if(buff[0] == '\0' || buff[0] == '\n'){ 
		//printf("No Input");	
		return 1;
	}

	//check if input is a comment
	if(buff[0] == comment){
		//printf("comment");	
		return 1;	
	}

	//strip of '\n' and replace with null char
	if(buff[strlen(buff-1)] == '\n')
		buff[strlen(buff-1)] = '\0';
	return 0;	
}

//run background process
int bProcess(pid_t resultPid, int *bpids, int bpidSize, int input, int output, int infd, int outfd, char *commands[], int *status){
	int fdin, fdout;// statusi;
	//in child
	if(resultPid == 0){	
		//if input file
		if(input){
			fdin = dup2(infd, 0);
			if (fdin == -1){
				perror("dup2");
				*status = 1;
			} 
		}
		//if output file
		if (output){
			outfd = dup2(outfd, 1);
			if(fdout == -1){
				perror("dup2");	
				*status = 1;
			} 
		}
		//exec commands
		execvp(commands[0], commands);
		//if it gets here it is invalid
		perror("execvp");
		*status = 1;
		return bpidSize; 
	}
	//in parent	
	else if (resultPid > 0){
		bpids[bpidSize] = resultPid;
		bpidSize++;		
		printf("background pid is %d\n", resultPid);
	}
	//invalid fork
	else{
		printf("Epic failed fork\n");
		perror("fork()\n");
	}
	return bpidSize;
}

int fProcess(pid_t resultPid, int input, int output, int infd, int outfd, char *commands[], int *status, struct sigaction *actN){
	int fdin, fdout;
	if(resultPid == 0){
		//printf("In child");
		///if input file redirect stdin to file descriptor
		if(input){
			fdin = dup2(infd, 0);
			if (fdin == -1){
				perror("dup2");
				*status = 1;
			} 
		} 
		//if output file redirect stout to file descriptor
		if (output){
			fdout = dup2(outfd, 1);
			if(fdout == -1){
				perror("dup2");	
				*status = 1;
			} 
		}
		actN->sa_handler = SIG_DFL; 
		sigaction(SIGINT, actN, NULL);


		execvp(commands[0], commands);
		//if it gets this far it's invalid
		perror(commands[0]);
		exit(1);
	}
	//in parent
	else if (resultPid > 0){
		//run wait for child to complete
		*status = waitMethod(resultPid);
	}
	else{
		printf("Epic failed fork\n");
		perror("fork()\n");
	}
	return *status;
}
//wait method for child returns status
int waitMethod(pid_t childPid){
	int status, exitstatus;
	pid_t cpid = wait(&status);

	if(cpid == -1){
		perror("Wait Failed");
		status = 1;
		return status; 
	}

	if (WIFEXITED(status)){
		exitstatus = WEXITSTATUS(status);
	}
	else if (WIFSIGNALED(status)){
		exitstatus = WTERMSIG(status);
		printf("terminated by signal %d\n", exitstatus);
	}
	return exitstatus;
}
//cd function to change directories
void changeDir(char *commands[]){
	//printf("change\n");
	if (commands[1] != NULL){
		//printf("%s", commands[1]);
		commands[1][strcspn(commands[1], "\r\n")] = 0;
		char *path = commands[1];
		chdir(path);
	}
	else{
		chdir(getenv("HOME"));
	}	
}


//exit function for call once exit occurs
void exitFxn(){

}
