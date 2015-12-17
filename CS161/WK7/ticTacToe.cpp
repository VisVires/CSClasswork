/*************************************************************************************************************************************************************************************
 *
 * Author: William George
 * Date Created: 11/15/2014
 * Date Last Modified: 11/16/2014
 * File Name: ticTacToe.cpp
 *
 * Overview: This program is a Tic Tac Toe game where the user can enter with the command line the number 
 * of games they would like to play then give each player alternating guesses until each game is either 
 * completed or won. The program will then keep counters on how many time each player has won, eventually 
 * ending when an overall winner has been named.
 *
 *
 * Input(s): The first input will be the command line input where the user can name the number of games 
 * they'd like to play. The second input is first players input on the game board. The user will have to input two 
 * values on a single line seperated by a space and a function will save them to an array from which the coordinates 
 * will be read then either and X or an O will appear at the new position the user designated location on the game 
 * board
 *
 * 		Input Example: 	0 1
 * 				1 2
 * 				
 *
 * Output(s): The program will first output the number of games to be played.
 * 		
 * 		Example: "You will be playing 3 Games"
 *
 *	The second group of outputs will be the game board with the user selections. So say the input examples above were for user X and O respectively
 *
 *		Example:	 0 1 2 
 *				0. X .
 *				1. . O
 *				2. . .
 *
 *	Finally the program will output whether a user won or lost and whether they are the overall winner. 
 *
 * **********************************************************************************************************************************************************************************/

#include <iostream>
#include <cstdlib>

using namespace std;

const int NUM_COLS = 4;
const int NUM_ROWS = 4;
//sets max size of tic tac toe board

void newBoard(char game[][NUM_COLS], int numRows);
//function that makes a fresh game board 
void playerX(char game[][NUM_COLS], int numRows);
//player X turn function
void playerO(char game[][NUM_COLS], int numRows);
//player Y turn function
bool winner(char game[][NUM_COLS], int numRows);
//function to check if user won
//bool winnerO(char game[][NUM_COLS], int numRows);

bool isNum(int numInput);
//validates number input
//
int main(int argc, char * argv[])
{
	int numGames = 0;
	//games counter
	int totalNumGames;
	//variable with purpose of checking overall winner
	char gameBoard[NUM_ROWS][NUM_COLS];
	//sets gameBoard function
	int numTurns;
	//counter to check if board is fillled	
	int pO_wins = 0;
	//player O win counter
	int pX_wins = 0;
	//player X win counterr
	char ch;
	//character for taking enter command for new game	

	system("clear");
	//clear screen
	if (argc == 1)
	//if no command line input for number of games, play one
	{
		numGames = 1;
		cout << "You will play one game for all the marbles\n" << endl;
	}
	else
	//set numGames based on commmand line input
	{
		numGames = atoi(argv[1]);
		cout << "You will be playing " << numGames <<" games.\n" << endl;	
	}

	totalNumGames = numGames;
	//set total number of games 

	cout << endl;	
	
	while (numGames != 0)
	//while numGames is not zero play new game
	{
		cout << "Game On!" << endl;
		newBoard(gameBoard, NUM_ROWS);
		//call new game with gameBoard and NUM_Rows as arguments
		
		if (numGames%2 == 0)
		//if num games is even player X starts
		{	
			numTurns = 0;
			while (numTurns != 9)
			//counts number of turns remaining
			{
				playerX(gameBoard, NUM_ROWS);
				//runs player X turn function
				if (winner(gameBoard, NUM_ROWS))
				//function to check if player X won, if so leave while loop and increment player X win counter
				{
					pX_wins++;
					break; 
				}
				cin.ignore(100, '\n');
				//clear buffer
				numTurns++;
				//increment number of turns	
				
				if (numTurns == 9)
				//if game board full, leave game
                                {  
				      break;
				}
				playerO(gameBoard, NUM_ROWS);
				//runs player O function
				if (winner(gameBoard, NUM_ROWS))
				//function to check if player O won if so leave game loop				
                     		{
					pO_wins++;
                   			break;
                   		}

				cin.ignore(100, '\n');
				//clear buffer	
				numTurns++;
				//increment turns
			}
		}
		
		else 
		{	
			numTurns = 0;
			while (numTurns !=9)
			//counts number of turns remaining
			{
				playerO(gameBoard, NUM_ROWS);
				//player O turn function		
				if (winner(gameBoard, NUM_ROWS))
				//checck if O won
                       		{
                     			pO_wins++;
					break;
                    		}	
				cin.ignore(100, '\n');
				numTurns++;
				//increment turns
		
				if (numTurns == 9)
				// check if game board is full
				{	
					break;
				}
				playerX(gameBoard, NUM_ROWS);
				//player X turn function
				if (winner(gameBoard, NUM_ROWS))
				// check if X won
                     		{
                        		pX_wins++;
					break;
                    		}
				cin.ignore(100, '\n');
				numTurns++;
				//increment turns
			}
		}
		if (numTurns == 9)
		//output tie game if game board is full
		{
			cout << "TIE GAME\n" << endl;
		}
		cout << "The current record is...\n" << endl;
		//output counters for each player wins after game
		cout << "Player X: "<< pX_wins <<" wins\n" << endl;
		cout << "Player O: "<< pO_wins <<" wins\n" << endl;

		if (pX_wins > totalNumGames/2)
		//checks if overall winner and leaves games if winner is declared
		{
			cout << "Player X is the overall winner!!\n" << endl;
			return(0);
		}  
		else if (pO_wins > totalNumGames/2)
		{
			cout << "Player O is the overall winner!!\n" << endl;
			return(0);
		}
		cout << "Press enter for next game" <<endl;
		cin.get(ch);
		cin.get(ch);
		//waits for user input to output new game board
		system("clear");
		numGames--;
		//decrements num games
	}
}

/***********************************************************************************************************************************************************************************
 *
 *	Entry: This function takes the previously defined 2D array with the numbers of rows and columns
 *
 *	Exit : This function doesn't return anything but it does update the array to the standard blank board 
 *
 *	Purpose: The purpose of this function is to output a new game board with coordinates and empty spaces
 *
 *
 * *********************************************************************************************************************************************************************************/

void newBoard(char game[][NUM_COLS], int numRows)
{
	int cols, rows; 
	//integers for columns and rows
	char no = '.';
	///sets empty cell value
	
	for (rows = 0; rows < NUM_ROWS; rows++)
	//cycles through each row
	{	
		for (cols = 0; cols < NUM_COLS; cols++) 
		//cycles through each column	
			if(rows == 0 && cols == 0)
			//sets empty space
			{
				game[rows][cols] = ' ';
			}
			else if (rows == 0)
			//sets column identifiers
			{		 
				game[rows][1] = '0';
				game[rows][2] = '1';
				game[rows][3] = '2'; 
			}
			else if (cols == 0)
			//sets row identifiers
			{
				game[1][cols] = '0';
				game[2][cols] = '1';
				game[3][cols] = '2';
				
			}
			else
			//fills rest of array
			{
				game[rows][cols] = no;
			}
	}

	for (rows = 0; rows < NUM_ROWS; rows++)
	//output new board
        {
                for (cols = 0; cols < NUM_COLS; cols++)
		{
			cout << game[rows][cols] << " ";
		}
		cout << endl;
	}
}

/************************************************************************************************************************************************************************************
 *
 *	Entry: This function takes the current iteration of the game board and the number of rows 
 *
 *	Exit : This function outputs a new game board with the user choices 
 *
 *	Purpose: The purpose of this function is to take the input from the user then place an X on the game board
 *
 *
 * **********************************************************************************************************************************************************************************/

void playerX(char game[][NUM_COLS], int numRows)
{
	int xIn, yIn, row, col, coord;
	//integers for coordinate input and output
	int NUM_CHOICE = 2;
	int choice[NUM_CHOICE];
	//sets array to hold coordinate inputs

		cout << "Player X: Please enter your move." << endl;
	
                for(int i = 0; i < NUM_CHOICE; i++)
		//adds user input to array
                {
                        cin >> coord;
			//user coordinate input
			while(isNum(coord) == false)
			//validates coordinate input within range
                        {
                                cout << "Please enter a valid coordinate" << endl;
                                cin.clear();
                                cin.ignore(100, '\n');
				cin >> coord;
                        }
                        choice[i] = coord;
			//adds to choice array
                }

                xIn = choice[0];
                yIn = choice[1];
		//sets inputs to new variables

        	while (game[xIn+1][yIn+1] == 'X' ||  game[xIn+1][yIn+1] == 'O')
		// if there is an X or O alreadt in user space ask for user re-input
		{
			cin.clear();
			cin.ignore(100, '\n');
			cout << "There is already a selection in that space" << endl;
			for(int i = 0; i < NUM_CHOICE; i++)
                	{
				cin >> coord;
                        	while(isNum(coord) == false)
                        	{
                                	cout << "Please enter a valid coordinate" << endl;
                                	cin.clear();
                                	cin.ignore(100, '\n');
                                	cin >> coord;
                        	}
                        	choice[i] = coord;
                	}
		
                	xIn = choice[0];
                	yIn = choice[1]; 
		
		}

	        game[xIn+1][yIn+1] = 'X';
		//sets coordinate input as X

                for (row = 0; row < NUM_ROWS; row++)
		//output updated board
                {
                        for(col = 0; col < NUM_COLS; col++)
                        {
                                cout << game[row][col] << " ";
			}
			cout << endl;
		}	
}	

/************************************************************************************************************************************************************************************
 *
 * 	Entry :This function takes the current game board along with the number of rows
 *
 *	Exit : This function outputs a new game board with Player O's selection
 *
 *	Purpose: The purpose of this function is to take the users input then place an O at the 
 *	user's designated coordinates and output a new game board with the updated data
 *
 *
 * *********************************************************************************************************************************************************************************/

void playerO(char game[][NUM_COLS], int numRows)
{
        int xIn, yIn, row, col, coord;
	//sets variables for getting user coordinates
        int NUM_CHOICE = 2;
        int choice[NUM_CHOICE];
	//array to hold user coordinates

                cout << "Player O: Please enter your move." << endl;

                for(int i = 0; i < NUM_CHOICE; i++)
		//fills coordinate array
                {
                        cin >> coord;
			while(isNum(coord) == false)
			//validates user inputs as valid coordinates
			{
				cout << "Please enter a valid coordinate" << endl;
				cin.clear();
				cin.ignore(100, '\n');
				cin >> coord;
			}
                        choice[i] = coord;
                }
		
		xIn = choice[0];
                yIn = choice[1];
		//fills coordinate variables 
		
		while (game[xIn+1][yIn+1] == 'X' ||  game[xIn+1][yIn+1] == 'O')
		//checks if space is filled, if so ask for re-input
                {
                      	cin.clear();
			cin.ignore(100, '\n');
			cout << "There is already a selection in that space" << endl;
                   	for(int i = 0; i < NUM_CHOICE; i++)
               		{
             			cin >> coord;
                    		while(isNum(coord) == false)
                  		{
                          		cout << "Please enter a valid coordinate" << endl;
                        		cin.clear();
                   			cin.ignore(100, '\n');
                       			cin >> coord;
                		}
                 		choice[i] = coord;
                      	}

    			xIn = choice[0];
           		yIn = choice[1];
                }
	
                game[xIn+1][yIn+1] = 'O';
		//adds O to game array

                for (row = 0; row < NUM_ROWS; row++)
		//output new game array
                {
                        for(col = 0; col < NUM_COLS; col++)
                        {
                                cout << game[row][col] << " ";
                        }
                        cout << endl;
		}
}

/************************************************************************************************************************************************************************************
 *
 *	Entry: This function takes the parameters of the game board and the number of rows.
 *
 *	Exit: This function returns either true or false based on the status of the game board
 *
 *	Purpose: The purpose of this function is to check to see if all the values in the columns,
 *	rows or diagonals match then give a message saying the player whose values matche won 
 *
 *
 * *********************************************************************************************************************************************************************************/

bool winner(char game[][NUM_COLS], int numRows)
{
	int row, col;

	for (row = 0; row < NUM_ROWS; row++)
	//cycles through rows to see if columns match
	{
		if(game[row][1] == 'X' && game[row][2] == 'X' && game[row][3] == 'X')
		{
			cout << "Player X wins!" <<endl;
			return true;
		}
		else if(game[row][1] == 'O' && game[row][2] == 'O' && game[row][3] == 'O')
                {
                        cout << "Player O wins!" <<endl;
                        return true;
                }

	}
	for (col = 0; col < NUM_COLS; col++)
	//cycles through columns to see if rows match
        {
                if(game[1][col] == 'X' && game[2][col] == 'X' && game[3][col] == 'X')
                {
                        cout << "Player X wins!" <<endl;
                        return true;
                }
		else if(game[1][col] == 'O' && game[2][col] == 'O' && game[3][col] == 'O')
                {
                        cout << "Player O wins!" <<endl;
                        return true;
                }

        }

	if (game[1][1] == 'X' && game[2][2] == 'X' && game[3][3] == 'X')
	//checks to see if right diagonal matches
	{
		cout << "Player X wins!" <<endl;
		return true;
	}
	else if (game[1][1] == 'O' && game[2][2] == 'O' && game[3][3] == 'O')
        {
                cout << "Player O wins!" <<endl;
                return true;
        }
	
	if (game[1][3] == 'X' && game[2][2] == 'X' && game[3][1] == 'X')
	//checks to see if left diagonal matches
        {
                cout << "Player X wins!" <<endl;
		return true;
        }
	else if (game[1][3] == 'O' && game[2][2] == 'O' && game[3][1] == 'O')
        {
                cout << "Player O wins!" <<endl;
                return true;
        }

	return false; 
}

/************************************************************************************************************************************************************************************
 *
 *
 *	Entry: This function takes the parameter of a users numeric input
 *
 *	Exit: This function returns either true or false based on whether the input is valid
 *
 *	Purpose: The purpose of this function is to check if the user input is a valid coordinate,
 *	either 0,1,or 2 then return true if it is or false if it is not.
 *
 *
 *
 * *********************************************************************************************************************************************************************************/
 
bool isNum(int numInput)
{
        
        if((numInput != 0 && numInput != 1 && numInput != 2))
	//checks if user input is 0,1 or 2 if neither return false
        {
	        return false;
        }
	return true;
}

