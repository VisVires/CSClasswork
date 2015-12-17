#include "room.h"
#include "maze.h"
#include <chrono>
#include <ctime>
#include <iomanip>
#include <iostream>
using std::cin;
using std::cout;
using std::endl;
#include <string>

/**********************************************************************************
Purpose: Constructor
***********************************************************************************/
Maze::Maze()
{
	//create dynamic pointers
	meathead = new MeatHead();
	startRoom = new StartRoom("Start");
	bombRoom = new EndRoom("Mom!");

	spagRoom = new FoodRoom("Spaghetti");
	steakRoom = new FoodRoom("Steak");
	shakeRoom = new FoodRoom("Protein Shake");
	sushiRoom = new FoodRoom("Sushi");
	wingRoom = new FoodRoom("Wings");

	ellipRoom = new WeightRoom("Elliptical");
	deadRoom = new WeightRoom("Deadlift");
	squatRoom = new WeightRoom("Squats");
	farmRoom = new WeightRoom("Farmers Carry");
	runRoom = new WeightRoom("Treadmill");

	forkRoom = new PuzzleRoom("Fork");
	knifeRoom = new PuzzleRoom("Knife");
	napRoom = new PuzzleRoom("Napkin");
	blendRoom = new PuzzleRoom("Blender");
	chopRoom = new PuzzleRoom("Chopsticks");

}

/**********************************************************************************
 Purpose: Destructor
***********************************************************************************/
Maze::~Maze()
{
	//deallocate dynamic memory
	delete meathead;
	delete startRoom;
	delete bombRoom;
	delete spagRoom;
	delete steakRoom;
	delete shakeRoom;
	delete sushiRoom;
	delete wingRoom;
	delete ellipRoom;
	delete deadRoom;
	delete squatRoom;
	delete farmRoom;
	delete runRoom;
	delete forkRoom;
	delete knifeRoom;
	delete napRoom;
	delete blendRoom;
	delete chopRoom;
}

/**********************************************************************************
Purpose: Get room variable type
***********************************************************************************/
std::string Maze::getRoom()
{
	return player->getType();
}

/**********************************************************************************
Purpose: Construct Enviroment
***********************************************************************************/
void Maze::buildMaze()
{
	startRoom->east = spagRoom;
	spagRoom->east = forkRoom;
	spagRoom->south = blendRoom;
	
	steakRoom->west = chopRoom;
	
	shakeRoom->east = bombRoom;
	shakeRoom->north = steakRoom;
	
	sushiRoom->west = blendRoom;
	
	wingRoom->north = sushiRoom;
	wingRoom->west = ellipRoom;


	ellipRoom->east = wingRoom;
	ellipRoom->south = farmRoom;
	
	deadRoom->south = shakeRoom;
	
	squatRoom->north = spagRoom;
	squatRoom->west = napRoom;
	
	farmRoom->west = knifeRoom;
	farmRoom->east = chopRoom;

	runRoom->south = steakRoom;
	runRoom->north = napRoom;

	forkRoom->east = squatRoom;
	forkRoom->south = sushiRoom;

	knifeRoom->east = deadRoom;
	
	napRoom->west = sushiRoom;
	napRoom->south = runRoom;
	napRoom->north = squatRoom;
	
	blendRoom->south = ellipRoom;
	
	chopRoom->north = wingRoom;
	chopRoom->west = farmRoom;

	bombRoom->north = runRoom;

	player = startRoom;
}

/***********************************************************************************

Purpose: Output menu for movement and get validated user input then initiate movement
In: None
Out: Moves player pointer to user chosen position

***********************************************************************************/
void Maze::traverseRooms()
{	
	player->getMenu();					//output room menu
	int choice = player->getChoice();	//get validated user choice
	char ch;							//wait for user input

	switch (choice)
	{
		case 1: cout << "You chose to travel North" << endl;
			//if list does not travel this direction
			if (player->north == NULL)
			{
				cout << "Door is blocked, try another" << endl;
				traverseRooms();
			}
			//move north
			else
			{
				player = player->north;
			}
			break;

		case 2: cout << "You chose to travel East" << endl;
			if (player->east == NULL)
			{
				cout << "Door is blocked, try another" << endl;
				traverseRooms();
			}
			//move east
			else
			{
				player = player->east;
			}
			break;

		case 3: cout << "You chose to travel South" << endl;
			if (player->south == NULL)
			{
				cout << "Door is blocked, try another" << endl;
				traverseRooms();
			}
			//move south
			else
			{
				player = player->south;
			}
			break;

		case 4: cout << "You chose to travel West" << endl;
			if (player->west == NULL)
			{
				cout << "Door is blocked, try another" << endl;
				traverseRooms();
			}
			//move west
			else
			{
				player = player->west;
			}
			break;
	}
	cin.get(ch);
}

/************************************************************************************

Purpose: Move player along map and intiate room tasks as well as keep time and keep
track of gains
In: None
Out: Runs player along game map until they acheive goal

************************************************************************************/
void Maze::movePlayer()
{
	double minutesPlayed;					//represents time elapsed
	//initiate time keeping objects
	std::chrono::time_point<std::chrono::system_clock> start, end;
	//set start point for game
	start = std::chrono::system_clock::now();

	//while not in last room move through enviroment
	while(player->getType() != "Mom!" && minutesPlayed < 8)
	{
			//output time played
			cout << "Time Elapsed: " << std::fixed << std::setprecision(2) << minutesPlayed;
			cout << " minutes" << endl;

			//output gainz
			cout << "Total Gainz: " << meathead->getGainz() << endl << endl;
			
			//perform room specific task
			player->roomTask(meathead);
			//move to next room
			traverseRooms();
			
			//set end time
			end = std::chrono::system_clock::now();
			//find time elapsed
			std::chrono::duration<double>elapsed_seconds = end - start;
			
			//convert time elapsed to minutes
			minutesPlayed = elapsed_seconds.count() / 60;
			
			//clear screen
			system("clear");	

			/*
			If player in the room with the pillar check if they've made enough gainz
			if not continue to next room
			*/
			if (player->getType() == "Mom!" && minutesPlayed < 8)
			{
				/*
				if player hasn't made goal number of gainz continue in game
				*/
				cout << "There's your " << player->getType() << endl;
				if (meathead->getGainz() < 100)
				{
					cout << "You haven't made enough gainz! Get to lifting fool!" << endl;
					traverseRooms();
				}
				else
				{
					player->roomTask(meathead);
				}
			}
	}

	/* 
	If player takes too much time end game
	*/
	if (minutesPlayed > 8)
	{
		cout << "You took too much time! You're too weak to save your Mom, "<< endl;
		cout << "so your little sister had to help. Do you even lift bro?" << endl;
		cout << "GAME OVER" << endl;
	}
}
