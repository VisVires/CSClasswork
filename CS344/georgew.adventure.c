#include <unistd.h>
#include <sys/types.h>
#include <string.h>
#include <sys/stat.h>
#include <stdio.h>
#include <dirent.h>
#include <time.h>
#include <stdlib.h>
#include <fcntl.h>
#include <assert.h>

#define ROOMS 7
#define ROOMNAMES 10
#define MAXLENGTH 256

struct Room {
	int index;
	int numConnects;
	char name[MAXLENGTH];
	char connects[ROOMS][MAXLENGTH];
	char type[MAXLENGTH];
}; 



void outputPrompt(struct Room map[ROOMS], int current);
int findStart(struct Room map[ROOMS]);
int findFinish(struct Room map[ROOMS]);
void endingPrompt(int path[], struct Room map[ROOMS],  int currentLength);
int moveRooms(char *next, struct Room map[ROOMS]);
int isValidRoom(char *next, struct Room map[ROOMS], int current);

int main(){	
   	int status; //file_descriptor;	//hold directory/filenames
	int roomCount = 0;		//room counter
	char dirName[20];		//hold directory name
	srand(time(NULL));		//set seed
	int usedRooms[ROOMS];
	unsigned char is_used[ROOMNAMES] = { 0 };
	int ir, irn;
	//char *roomName;
	char *roomNames[ROOMNAMES] = {"Weight_Room","Cardio_Room","Group_Exercise",
			"BasketBall_Court","RacquetBall_Court","Swimming_Pool",
			"Showers","Mens_Room","Womens_Room","Tennis_Court"};		//various room names
	char *roomTypes[3] = {"START_ROOM","MID_ROOM","END_ROOM"};			//room types
	int usedType[3] = { 0 }; 							//checks if start room, mid room, or end room has been assigned
	char *rType;									//room types
	int connections[ROOMS][ROOMS] = { 0 };						//multidimensional array to graph  connections
	struct Room map[ROOMS];								//array to hold each room used in program
	
	//get pid
	int pid = getpid();
	//set up appropriate directory name
	sprintf(dirName, "georgew.rooms.%d", pid);
	//set name to directory
	const char *roomdir = dirName;
    	status = mkdir(roomdir, S_IRWXU | S_IRWXG | S_IROTH);
    	
	//open directory
    	DIR *dir;
	struct dirent *dirDirent;
    	dir = opendir(roomdir);
    	
	//verify directory was created
	if (dir == NULL){
 		printf("Directory Doesn't Exist %s\n", roomdir);
		exit(1);
    	}
	
	//create array to store 7 unique random ints from 1-10 using 
	//the Robert Floyd algorithm for room names
	//Jon Bentley's Programming Pearls
	ir = 0;
	for (irn = ROOMNAMES - ROOMS; irn < ROOMNAMES && ir < ROOMS; ++irn){
		int r = rand() % (irn + 1);
		if (is_used[r])
			r = irn;
		assert(!is_used[r]);
		usedRooms[ir++] = r;
		is_used[r] = 1;	
	}
	/**************************************************************************
 	* ********************CREATE ROOMS AND PLACE IN FILES**********************
 	* ************************************************************************/
	while (roomCount < ROOMS){
		//assert(newRoom != NULL);		
		char roomFile[100];
		int t, c, count, i, j;
		//struct Room *newRoom;
		int type = 0;
		//char *connect;
		int numConnects;
		//name each file
		sprintf(roomFile, "%s/fileNum%d.txt", roomdir, roomCount);
		//open files
		FILE *newFile = fopen(roomFile, "w+");
		//set room names	
		char *roomName = roomNames[usedRooms[roomCount]];
		//output room name test
		//printf("ROOM NAME: %s\n", roomName);
		fprintf(newFile,"ROOM NAME: %s\n", roomName);
		//printf("Room Count: %d\n", roomCount);
		//set room type
		while (!type){
			type = 0;
			t = rand() % 3;
			//printf("%d, Used Type: %d  \n", t ,usedType[t]);
			//check if start or end room and set to start or end room
			if ((t == 0 || t == 2) && usedType[t] == 0){
				rType = roomTypes[t];
				usedType[t] = 1;
				type = 1; 
			}
			//if start room and end room are not set yet with two rooms left
			//set whichever one not set
			else if (t == 1 && (usedType[0] == 0 || usedType[2] == 0) && roomCount >= 5){
				//if start_room not yet set
				if(usedType[0] == 0){
					rType = roomTypes[0];
					usedType[0] = 1;
					type = 1;
				}
				//if end_room not yet set	
				else if(usedType[2] == 0){
					rType = roomTypes[2];
					usedType[2] = 1;
					type = 1;
				}
			}
			//set mid rooms
			else{
				rType = roomTypes[1];
				type = 1;	
			}		 
		}
		
		//set number of conections
		c = rand() % 3 + 3;
		//printf("Number of connections: %d\n", c );
		count = 0;	
		
		//count current connections	
		for (i = 0; i < ROOMS; ++i){
			//printf("Getting Current Connections\n");
			if (connections[roomCount][i] == 1){
				count++;
			}
			//printf("Current Connections: %d ", count);
		}

		//set up connections
		while (count < c){
			int randConnect = rand() % 7;
			if (connections[roomCount][randConnect] != 1 && randConnect != roomCount){
				//printf("Add New Connection\n");
				//make connection and reciprocal connection
				connections[roomCount][randConnect] = 1;
				connections[randConnect][roomCount] = 1;
				count++;
			}
			//else if (connections[roomCount][randConnect] == 1)
				//printf("Connection Already Made\n");		
		}
		//printf("Total Connections: %d\n", count);
		//write connections, room_type to file
		int connectNum = 1;
		for(j = 0; j < ROOMS; ++j){
			if (connections[roomCount][j] == 1){
				fprintf(newFile, "CONNECTION %d: %s\n", connectNum, roomNames[usedRooms[j]]);
				//printf("CONNECTION %d: %s\n", connectNum, roomNames[usedRooms[j]]);
				connectNum++;
			}		
		}						
		//write type to file
		//printf("ROOM TYPE: %s\n", rType);		
		fprintf(newFile, "ROOM TYPE: %s\n", rType);	
		//close file
		fclose(newFile);
	

	
		/*************************************
		**READING INFO FROM FILE INTO STRUCT**
		**************************************/	
		FILE *file = fopen(roomFile, "r");
		int item = 0;
		char *connect;
		struct Room newRoom;
		char buffer[100];
		//get first line
		fgets(buffer, sizeof buffer, file);
		//get name
		//printf("%s",buffer+11);
		strncpy(newRoom.name, buffer+11, 100);
		//printf("Name: %s", newRoom.name);
		//newRoom.name = readName;
		//get connections
		//newRoom.connects = (char *)malloc((sizeof(char *) * ROOMS));
		while (fgets(buffer, sizeof buffer, file)!= NULL){
			//save connections
			if ((strncmp(buffer ,"ROOM TYPE: ", 10) != 0)){
				char *connect = malloc(sizeof(char *) * 100);
				//if(connect == NULL){
				//	perror("Error Allocating Memory for Next");
				//	exit(1);
				//}
				connect = buffer;
				//connect = buffer;
				strcpy(newRoom.connects[item], connect+14);
				//printf("Connection %d: %s", item+1, newRoom.connects[item]); 
				item++;
				//free(connect);
			}	
			//get type
			else{
				strcpy(newRoom.type, buffer+11);
			}
		}
		newRoom.numConnects = item;
		//printf("Connects %d: %s\n", 1, newRoom.connects[1]);
		//printf("Type: %s", newRoom.type);
		//printf("Name: %s", newRoom->name);
		//store finished room to map
		map[roomCount] = newRoom;
		//close file
		fclose(file);
		//printf("%s", map[roomCount]->type);
		roomCount++;
	}

	/****************************************************************
 	**************************PLAY GAME*****************************
 	* **************************************************************/ 		
	int start = findStart(map);
	int path[50];
	//const int maxLength = 50;
	int currLength = 0;
	int currentRoom = start;
	int finish = findFinish(map);	
	//printf("%s", map[start].type);
	//printf("%s", map[finish].name);
	path[currLength] = currentRoom;
	currLength++;
	while(currentRoom != finish){
		//create memory for input
		char *next = malloc(sizeof(char *));
		//check that memory was created
		if (next == NULL){
			perror("Error Allocating Memory for Next");
			exit(1);
		}
		//output prompt for new room	
		outputPrompt(map, currentRoom);
		//get input from user
		fgets(next, 100, stdin);
		//next[strcspn(next, "\n")] = 0;
		//printf("%s", next);
		//check if input is valid
		if(isValidRoom(next, map, currentRoom)){
			//move to next room
			currentRoom = moveRooms(next, map);
			//add next room to path
			path[currLength] = currentRoom;
			//increase length of path	
			currLength++;
		}
		//invalid room
		else{
			printf("\nHUH? I DON'T UNDERSTAND THAT ROOM. TRY AGAIN.\n");
		}
		//free memory from next	
		free(next);
	}
	endingPrompt(path, map, currLength);
		
	exit(0);
}

int findStart(struct Room map[ROOMS]){
	int i;
	for (i = 0; i < ROOMS; ++i){
		//printf("%s", map[i].type);
		if (strncmp(map[i].type, "START_ROOM",10) == 0){
			//printf("%s", map[i].type);
			return i;	
		}
	}		
}

int findFinish(struct Room map[ROOMS]){
	int i;
	for (i = 0; i < ROOMS; ++i){
		//printf("%s", map[i].type);
		if (strncmp(map[i].type, "END_ROOM",8) == 0){
			//printf("%s", map[i].type);
			return i;	
		}
	}		
}

//output go prompt
void outputPrompt(struct Room map[ROOMS], int current){
	printf("\nCURRENT LOCATION: %s", map[current].name);
	printf("POSSIBLE CONNECTIONS: ");
	int i = 0;
	char *output;
	strcpy(output, "");
	//output connections 
	while(i < map[current].numConnects - 1){
		strcpy(output, map[current].connects[i]);
		//remove new line char
		output[strcspn(output, "\n")] = 0;
		//printf("%s, ", map[current].connects[i]);
		printf("%s, ", output);
		i++;
	}
	//printf("%s" , output);
	printf("%s\n", map[current].connects[map[current].numConnects - 1]);	
	printf("WHERE TO?>");		
}

//send congrats message
void endingPrompt(int path[], struct Room map[ROOMS], int currentLength){
	int i;
	printf("\nYOU FOUND THE END ROOM. CONGRATULATIONS!\n");
	printf("YOU TOOK %d STEPS. YOUR PATH TO VICTORY WAS: \n", currentLength);
	//output path
	for (i = 0; i < currentLength; i++){
		printf("%s", map[path[i]].name);
	}	
}
//move to next room if valid
int moveRooms(char *next, struct Room map[ROOMS]){
	int i;
	for (i = 0; i < ROOMS; ++i){
		//printf("%s", map[i].name);
		if (strcmp(map[i].name, next) == 0){
			printf("%s", map[i].name);
			return i;	
		}
	}		
}
//check if room is valid connection
int isValidRoom(char *next, struct Room map[ROOMS], int current){
	int i;
	for (i = 0; i < ROOMS; ++i){
		//printf("%s", map[i].name);
		if (strcmp(map[current].connects[i], next) == 0){
			//printf("%s", map[i].name);
			return 1;	
		}
	}
	return 0;
}
