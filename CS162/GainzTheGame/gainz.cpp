/********************************************************************************************************

Author: William George
Date Created: 3/10/2015
Date Last Modified: 3/17/2015
File Name: gainz.cpp

Overview: This is a text based game where the user was in an earthquake and their mom was trapped under a 
pillar, the goal is to acquire the adequate amount of gainz in order to save their mother from the pillar
by lifting weights and eating, also the user must watch out for cardio as they will lose their gainz with
too much. The user will have 8 minutes to complete the mission.

************************************************************************************************************/

#include "room.h"
#include "maze.h"
#include "meatHead.h"
#include <iostream>
using std::cout;
using std::cin;
using std::endl;
#include <ctime>

int main()
{
	//build dynamic maze
	Maze *maze = new Maze();
	//set seed
	srand(time(NULL));			
	
	//clear screen
	system("clear");

	//construct maze
	maze->buildMaze();
	//move player through enviroment
	maze->movePlayer();
	
	//clear dynamic memory
	delete maze;
	
	return 0;
}

