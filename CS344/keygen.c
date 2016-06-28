#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ctype.h>

int main(int argc, char *argv[]){
//check if there is a keylength
	if (argc != 2){
		printf("Please enter a length of the key file\n");
		exit(1);
	}
	else{
		int i = 0;
		srand(time(NULL));
		char letters[27] = {'A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z',' '};
		//turn argv[1] to an int
		int keyLength;
		if(sscanf (argv[1], "%i", &keyLength) != 1){
			printf("Please enter a valid integer");
			exit(1);
		}
		//continue until you create a key of keyLength letters
		while(i < keyLength){
			//get an int 
			int r = rand() % 27;
			//output letters
			printf("%c", letters[r]);
			i++;
		} 
		//add newline character 
		printf("\n");		
	}
return 0;
}
