/****************************************************************************************************************************
 *
 * Author: William George
 * Date Created: 1/12/2014
 * Date Last Modified: 1/17/2014
 * File Name: gameOfLife.cpp
 *
 * Purpose: This program simulates Conway's Game of Life where based on the rules of the 
 * game and it's neighboring  cells a cell can either live or die from one generation to
 * the next.
 *
 * Input: The user will first input the they'd like to place on the grid and then the x 
 * and y coordinates for the shape. The the user can input the number of generations they'd
 * like too iterate. Finallly the user will have the ability to either continue running 
 * the simulation or to quit
 *
 * Output: First the program will output the instructions and a grid with the users 
 * chosen shape. Then it will output the generations along with prompts to either continue 
 * or stop the simulation.
 *
 *
 * *******************************************************************************************************************************/

#include <iostream>
using std::endl;
using std::cout;
using std::cin;
using std::string;

#include <string>
#include <cstdlib>
#include "world.cpp"

void getInstructions();
void getMenu();
int getChoice();
bool isValidNum(string num);

int main()
{
    	char again;		//char input to repeat simulation
	char c;			//char input for cin.get

    	getInstructions();	//call getInstructions function

    	do
	//loop iterates as long as user enter Y or y to repeat simulation
    	{
        	World world;				//intialize world object
        	int choice; 				//sets  user input for shape
		int xCoord, yCoord; 			//user inputed coordinates
		string totGenerations, x, y;			//user input for number of iterations
		int tGen;				//validated input for num of generations

        	getMenu();				//call getMenu function
        	choice = getChoice();			//get user choice

        	cout << "At what coordinates would you like the shape to be placed?" << endl;
        	cout << "Please enter a column between 1 and 80: ";
        	cin >> x;
		while(!(isValidNum(x)))
		//validate x input
                {
                        cout << "Invalid Input, please enter a row between 1 and 22: ";
                        cin.clear();
                        cin.ignore(100, '\n');
                        cin >> x;
                }
		
		xCoord = atoi(x.c_str());
		//convert string to int	
	
		while (xCoord > 80 || xCoord < 1)
		//validate x input	
		{
			cout << "ERROR: Please enter a number between 1 and 80: ";
			cin.clear();
			cin.ignore(100, '\n');
			cin >> xCoord;
		}
        	world.setX(xCoord);			
		//set x coordinate

        	cout << "Please enter a row between 1 and 22: ";
        	cin >> y;
		while(!(isValidNum(y)))
		//validate y input
		{		
			cout << "Invalid Input, please enter a row between 1 and 22: ";
			cin.clear();
			cin.ignore(100, '\n');
			cin >> y;
		}

		yCoord = atoi(y.c_str());
		//convert string to int
		
		while (yCoord > 22 || yCoord < 1)
                //validate y input
                {
                        cout << "ERROR: Please enter a number between 1 and 22: ";
                        cin.clear();
                        cin.ignore(100, '\n');
                        cin >> yCoord;
                };
        	world.setY(yCoord);
		//set y coordinate


        	switch(choice)
        	{
            		case 1: world.addBlinker();
			//add blinker to world object
                	break;

            		case 2: world.addGlider();
			//add glider to world object
                	break;

            		case 3: world.addToad();
			//add toad to world object
                	break;

           		case 4: world.addGun();
			//add gun to world object
                	break;
        	}

        	world.outputWorld();
		//output first iteration of world object
		
		do
		//loop until user gives stop command = -1 
		{	
			int generations = 0; 		//reset generation counter

        		cout << "Enter the number generations would you like to iterate or -1 to quit ";
        		cin >> totGenerations;					
        		//user input for num of iterations
			if (!(totGenerations == "-1"))
			{
        			while(!(isValidNum(totGenerations)))
				//validates user input
				{
					cout << "Please enter a valid number: ";
               		              	cin.clear();
                        		cin.ignore(100, '\n');
                        		cin >> totGenerations;
                		}
			}
			
			tGen = atoi(totGenerations.c_str()); 
			
			do
			//loop until generation counter = user inputed generations	
        		{
            			cout << "Press Enter to Advance a Generation";
				cin.get(c);
				//allows user to control each generation

				world.copyWorld();
				//copies current world to second array
				world.updateWorld();
				//updates current world 
            			world.outputWorld();
				//outputs updated world
            			generations++;
				//advance counter
        		}
        		while(tGen > generations);
		}
		while(tGen != -1);
		//stop command

        	cout << "Would you like to run another simulation? Y/N: ";
        	cin >> again;
		//user input to run simulation with new shape
    	}
    	while (again == 'Y' || again == 'y');
    return 0;
}

/********************************************************************************************************************************
 * 
 * Purpose: Output the rules for Conways Game of Life
 *
 * Input: None
 *
 * Out: Outputs the instructions for the game of life
 *
 ********************************************************************************************************************************/

void getInstructions()
{
    	system("clear");
    	char c;
    	cout << "Welcome to \"The Game of Life\"\n" << endl;
    	cout << "This cellular automaton uses an array in which cell is occupied by an organism" << endl;
    	cout << "that is either dead or alive. The state of the organism is determined by the following rules: \n" << endl;
    	cout << "1. If the organism has either one or zero neighbors, it dies of loneliness" << endl;
    	cout << "2. If the organism has more than three neighbors, it dies of overcrowding" << endl;
    	cout << "3. If an empty cell has exactly three living neighbors a new organism is born in the cell" << endl;
    	cout << "4. Births and Deaths are instantaneous at the start of each generation\n\n" << endl;

    	cout << "PRESS ENTER TO CONTINUE" << endl;

    	cin.get(c);
}

/******************************************************************************************************************************
 *
 * Purpose: Output a menu from which the users can choose 
 *
 * Input: None
 *
 * Output: Outputs a menu of options
 *
 ******************************************************************************************************************************/

void getMenu()
{
    	system("clear");
    	cout << "Please enter the corresponding number for the shape you'd like to use: " << endl;
    	cout << "1. FIXED SIMPLE OSCILLATOR" << endl;
    	cout << "2. GLIDER" << endl;
    	cout << "3. TOAD" << endl;
    	cout << "4. GLIDER GUN" << endl;
}

/******************************************************************************************
 *
 * Purpose: Get, validate and return users choice from menu of shapes
 *
 * Input: none
 *
 * Output: returns user choice to main
 *
 *****************************************************************************************/

int getChoice()
{
    	int userChoice;
    	cin >> userChoice;
    	while (userChoice < 1 || userChoice > 4)
    	{
        	cout << "Please input valid choice: ";
		cin.clear();
		cin.ignore(100, '\n');
        	cin >> userChoice;
    	}
    	return userChoice;
}

/******************************************************************************************
 *
 * Purpose: Validate user number input as being a number
 *
 * Input: String input
 *
 * Output: False if all numbers are not digits, True if it is a valid number
 *
 * **************************************************************************************/

bool isValidNum(string num)
{
	for(int i = 0; i < num.length(); i++)
	{
		if(!(num.at(i) >= '0' && num.at(i) <= '9'))
		return false;
	}
	return true;
}
