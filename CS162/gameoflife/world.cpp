#include <cstdlib>
#include "world.h"
#include <iostream>
using std::cout;
using std::cin;
using std::endl;

/*
 * Constructor
 */

World::World()
{
    	for (int i = 0; i < MAXROW; i++)
	//build parent array with dead cells for columns 1-80 and rows 1-22
  	{
    		for (int j = 0; j < MAXCOL; j++)
        	{
			if (i < 81 && j > -1)
			{
        	    		world[i][j] = '.';
			}
			else 
			{
				world[i][j] = ' ';
			}
	        }
 	}
	
	for (int i = 0; i < MAXROW; i++)
	//build temp array
	{
		for (int j = 0; j < MAXCOL; j++)
		{
			if ( i < 81 && j > -1)
			{
	            		otherWorld[i][j] = '.';
			}
			else
			{
				otherWorld[i][j] = ' ';
			}
	        }
	}

}

/********************************************************************************************************************************************
 *
 * 	Purpose: Function takes user input subtracts one and stores it to x
 *	Input: Takes a user input xCoord
 *	Output: stores to private variable x
 *
 ********************************************************************************************************************************************/

void World::setX(int xCoord)
{
    x = xCoord - 1;
}

/*****************************************************************************************************************************************
 *
 *	Purpose: Function takes user input, subtracts one and stores it to y
 *	Input: Takes a user input yCoord
 *	Output: stores to private variable y
 *	
 *****************************************************************************************************************************************/


void World::setY(int yCoord)
{
    y = yCoord - 1;
}

/******************************************************************************************************************************************
 *
 *	Purpose: Prints current iteration of the array
 *	Input: None
 *	Output: Prints current iteration of array
 *
 ******************************************************************************************************************************************/

void World::outputWorld()
{
	system("clear");
	//clear screen
		
    	for (int i= 0; i < 22; i++)
	//output cells for 80x22 array
    	{
            	for (int j = 0; j < 80; j++)
            	{
                	cout << world[i][j];
            	}
            	cout << endl;
    	}
}

/*************************************************************************************************************************************
 *
 *	Purpose: Copies the current cell to a cell in a new array of an identical size
 *	Input: Takes two ints representing the coordinates of a specific cell
 *	Output: None
 *
 * ************************************************************************************************************************************/

void World::copyCell(int row, int col)
{
    otherWorld[row][col] = world[row][col];
}

/************************************************************************************************************************************
 *
 *	Purpose: adds simple fixed oscillator/blinker to graph
 *	Input: Uses X and Y coordinates input by user
 *	Output: Prints fixed oscillator to grid
 *
 * **********************************************************************************************************************************/

void World::addBlinker()
{
    world[y][x] = life;
    world[y][x+1] = life;
    world[y][x+2] = life;
}

/*******************************************************************************************************************************
 *
 *	Purpose: Adds Glider to graph
 *	Input: Uses X and Y Coordinates input by user
 *	Output: Prints glider to grid
 *
 * ******************************************************************************************************************************/


void World::addGlider()
{
    world[y][x] = life;
    world[y+1][x+1] = life;
    world[y+1][x+2] = life;
    world[y][x+2] = life;
    world[y-1][x+2] = life;
}

/***********************************************************************************************************************************
 *
 *	Purpose: Adds Toad to grid
 *	Input: Uses X and Y coordinates input by user
 *	Output: Prints Toad to grid
 *
 *******************************************************************************************************************************/

void World::addToad()
{
    world[y][x] = life;
    world[y][x+1] = life;
    world[y][x+2] = life;
    world[y-1][x+1] = life;
    world[y-1][x+2] = life;
    world[y-1][x+3] = life;
}

/*********************************************************************************************************************************
 *
 *	Purpose: Adds Glider Gun to graph
 *	Input: Uses X and Y coordinate input by user
 *	Output: Prints Glider Gun to graph
 *
 **********************************************************************************************************************************/

void World::addGun()
{
    world[y][x] = life;
    world[y][x+1] = life;
    world[y+1][x] = life;
    world[y+1][x+1] = life;

    world[y-1][x+34] = life;
    world[y-2][x+34] = life;
    world[y-2][x+35] = life;
    world[y-1][x+35] = life;

    world[y][x+10] = life;
    world[y+1][x+10] = life;
    world[y+2][x+10] = life;
    world[y+3][x+11] = life;
    world[y+4][x+12] = life;
    world[y+4][x+13] = life;
    world[y-1][x+11] = life;
    world[y-2][x+12] = life;
    world[y-2][x+13] = life;

    world[y-1][x+15] = life;
    world[y+1][x+14] = life;
    world[y+3][x+15] = life;
    world[y][x+16] = life;
    world[y+1][x+16] = life;
    world[y+2][x+16] = life;
    world[y+1][x+17] = life;

    world[y-2][x+20] = life;
    world[y-1][x+20] = life;
    world[y][x+20] = life;
    world[y-2][x+21] = life;
    world[y-1][x+21] = life;
    world[y][x+21] = life;
    world[y-3][x+22] = life;
    world[y+1][x+22] = life;
    world[y-4][x+24] = life;
    world[y-3][x+24] = life;
    world[y+1][x+24] = life;
    world[y+2][x+24] = life;
}

/***************************************************************************************************************************************
 *
 *	Purpose: Counts a cells neighbors
 *	Input: Takes x and y coordinates of each cell
 *	Output: None
 *
 ***************************************************************************************************************************************/

int World::countNeighbors(int row, int col)
{
    	int neighbors = 0;		//counter for neighbor cells	

    	if (world[row-1][col] == life)
        	neighbors++;
    	if (world[row-1][col-1] == life)
        	neighbors++;
    	if (world[row-1][col+1] == life)
        	neighbors++;
    	if (world[row][col+1] == life)
        	neighbors++;
    	if (world[row][col-1] == life)
        	neighbors++;
    	if (world[row+1][col+1] == life)
        	neighbors++;
    	if (world[row+1][col] == life)
        	neighbors++;
    	if (world[row+1][col-1] == life)
        	neighbors++;

    return neighbors;
}
/***************************************************************************************************************************************
 *
 * Purpose: This function counts a cells surrounding edge cells
 *
 * In: This function takes specific coordinates from a cell
 *
 * Out: Returns the total number of edge cells a cell is touching
 *
 * ************************************************************************************************************************************/

int World::countEdge(int row, int col)
{
	int edgeCells = 0;
	//counter for edge cells

	if (world[row-1][col] == ' ')
        	edgeCells++;
    	if (world[row-1][col-1] == ' ')
        	edgeCells++;
    	if (world[row-1][col+1] == ' ')
        	edgeCells++;
    	if (world[row][col+1] == ' ')
        	edgeCells++;
    	if (world[row][col-1] == ' ')
        	edgeCells++;
    	if (world[row+1][col+1] == ' ')
        	edgeCells++;
    	if (world[row+1][col] == ' ')
        	edgeCells++;
    	if (world[row+1][col-1] == ' ')
        	edgeCells++;

    return edgeCells;
}

/**************************************************************************************************************************************
 *
 *	Purpose: This function reads the row and column for a specific cell as well as the
 *	number of live neighbors and edge cells
 *
 *	Input: This function uses the row and col as well as the number of live neighbors for a
 *	specific cell and the number of edge cells
 *
 *	Output: This function stores the new values to a second temporary array 
 *
 ***************************************************************************************************************************************/

void World::lifeOrDeath(int row, int col, int neighbors, int edge)
{
    	if (world[row][col] == '8')
	//if cell is live
    	{
        	if (neighbors == 0 || neighbors == 1)
		//if 0 or 1 live neighbors die of loneliness
            		otherWorld[row][col] = '.';
			//save to temp array

        	if (neighbors > 3)
		//if more than 3 die of overcrowding
            		otherWorld[row][col] = '.';
		
		if(edge > 7)
		//if more than 7 edge cells around cell becomes an edge cell
			otherWorld[row][col] = ' ';
			 
    	}

    	else if (world[row][col] == '.')
	//if cell is dead
    	{
        	if (neighbors == 3)
		//cell has exactly 3 live neighbors it is changed to live
            		otherWorld[row][col] = '8';
    	}

	
}

/*************************************************************************************************************************************
 *
 *	Purpose: This function copies the cells of one array to another then performs the
 *	life algorithm
 *	Input: None
 *	Output: The otherWorld array is changed to the next generation
 *
 ***************************************************************************************************************************************/

void World::copyWorld()
{
	int neighbors, edge;		//variables to hold number of live neighbor and edge cells

    	for(int row = 0; row < MAXROW; row++)
    	{
        	for(int col = 0; col < MAXCOL; col++)
        	{
        	        copyCell( row, col);		
			//copy cells to otherArray
			neighbors = countNeighbors( row, col);	
			//get number of live neighbor cells
			edge = countEdge(row, col);		
			//count number of neighboring edge cells
			lifeOrDeath( row, col, neighbors, edge);	
			//run life algorithm on each cell
        	}
    	}
}

/****************************************************************************************************************************************
 *
 *	Purpose: Function copies current cell in temp array to current array
 *	In: None
 *	Out: otherWorld array is copied to the world array
 *	
 *****************************************************************************************************************************************/

void World::updateWorld()
{

    	for (int row = 0; row < MAXROW; row++)
    	{
            	for (int col = 0; col < MAXCOL; col++)
            	{	
        		world[row][col] = otherWorld[row][col];
			//copy temp array to visible array    
		}
	}
}
