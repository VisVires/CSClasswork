/**************************************************************************************************************************************************************
 *
 * Author: William George
 * Date Created: 11/12/2014
 * Date Last Modified: 11/16/2014 
 * File Name: sameSum.cpp
 *
 * Overview: This program creates a 2D array up to 10 numbers per side, then adds up 
 * the user inputed rows and columns, as well as the diagonals to see if they are all 
 * the same. The program will then output a message indicating whether the sums match
 *
 *
 * Input(s): This program will take two user inputs. First it will take an input for the 
 * size of the sides of the array. Then it will take an input asking for each row of the 
 * array with each number input seperated by a single space. 
 *
 *
 * Output(s): This program will output each row the user inputs to validate the users input
 * It will then output the completed sqaure, all of the sums and finally whether the sums match 
 *
 *
 * ************************************************************************************************************************************************************/

#include <iostream>
#include <iomanip>
#include <cstring>
#include <string>
#include <cstdlib>

using namespace std;

const int NUM_COLS = 10;
const int NUM_ROWS = 10;
//declare max size of arrays

bool isNum(string num);
//prototype for function with purpose of validating user input

bool sameSum(int const square[][NUM_COLS], int rows);
//prototype for function with purpose of finding whether rows/columns and diagonals have the same sum

int main()
{
	int square[NUM_ROWS][NUM_COLS];
	//
	int row[NUM_COLS];
	string numRowsInput;
	int numRows = 0;
	int numSpaces = 0;
	int length;
	char next, reEnter;


	cout << "This program will accept numbers to place in a square, then calculate if the";
	cout << " sums of the rows, columns, and main diagonal of the square are equal." << endl;
	//tells user purpose of application	

	cout <<	"Your square can have a maximum of 10 numbers per side.";
	cout << "\n\nHow many rows would you like your square to have? ";
	cin >> numRowsInput;
	//gathers user input on size of square
	
	while (isNum(numRowsInput) == false)
	//calls input validation function
	{
		cout << "That is not a number, please try again: ";
		cin.clear();
		cin.ignore(100, '\n');
		cin >> numRowsInput;
	}
	
	numRows = atoi(numRowsInput.c_str());
	//change input from string to int
	
	while (numRows > 10)
	//makes sure user row is not more than max array size
	{
		cout << "Sorry your square can only have a maximum of 10 numbers per side\n";	
		cout << "Please enter a number less than or equal to 10: ";
		cin >> numRowsInput;
		//user re-input
		
		while (isNum(numRowsInput) == false)
        	{
                	cout << "That is not a number, please try again: ";
                	cin.clear();
                	cin.ignore(100, '\n');
                	cin >> numRowsInput;
        	}	

        	numRows = atoi(numRowsInput.c_str());
		//change input from string to int
	}

	cin.ignore(100 ,'\n');
	//clear buffer
	
	for (int row = 0; row < numRows; row++)
	//cycles through column elements of square
	{
	 	do
	 	{	
			system("clear");
			//  clear screen
			cout << "Row "<< row+1 <<": Please enter " << numRows << " numbers seperated by a single space: ";
			
			for (int col = 0; col < numRows; col++)
			//takes user input for each row
			{
				cin >> square[row][col];
			}

			cout << "\n\nYou entered: ";
			for (int col = 0; col < numRows; col++)	
			//outputs user input for each row
			{
				cout << square[row][col] << " ";
			}
	                cout << "for Row " << row+1 << "\n\n";
		
			cin.ignore(100,'\n');
			//clear buffer
			
			cout << "Is this correct? Press N to enter again or any other letter to continue ";
		 	cin >> reEnter;
			//gives user opportunity to re-input values with input of N or n
		}
		while(reEnter == 'n' || reEnter == 'N');
 	}

	cout << "Here is your square: " << endl;
	{
		for (int row = 0; row < numRows; row++)
		//output completed square
		{	
			for (int col = 0; col < numRows; col++)
			{
				cout << square[row][col] << " ";
			}
			cout << endl;
		}
	}  

	if(sameSum(square, numRows))
	//run same sum function using new 2d array and number of rows
	 	cout << "The sums match" << endl;
	else
		cout << "The sums don't match!" << endl;

return 0;
}

/************************************************************************************************************************************************************************************
 *
 *	Entry : This function takes a string input from the user and makes sure that input 
 *	is a number
 *
 *
 *	Exit : This function returns true or false based on whether the string input is 
 *	a numeric value
 *
 *
 *	Purpose : The purpose of this function is to validate the users string input 
 *	as a numeric input	
 *
 *
 *
 * *********************************************************************************************************************************************************************************/

bool isNum(string numInput)
 {
        for(int i=0; i < numInput.length(); i++)
	//checks string for number inputs
        {
                if(!(numInput.at(i) >= '0' && numInput.at(i) <= '9'))
                return false;
        }
        return true;
 }

/************************************************************************************************************************************************************************************
 *
 * 	Entry: Function takes the parameters of a 2d array and the number of rows in said array, 
 * 	the number of columns will = number of rows.
 *
 *	Exit: Function will output true or false based on whether users input rows and columns 
 *	and main diagonals all sum to equal values
 *
 *	Purpose: This function takes the inputs by the user after they've been placed in an array
 *	and captures the sum of each row, column and diagonal. If all have the same sum the function
 *	will return true. Otherwise it will return false.
 *
 *
 * ********************************************************************************************************************************************************************************/

bool sameSum(const int array[NUM_ROWS][NUM_COLS],int rows)
{
	int col, row, sum, rDiagSum, lDiagSum;
	//integers to increment loops and increment for sums
	int cols = rows;
	//set cols and rows as equal
	int sumRows[NUM_ROWS];
	//array to hold sums of rows
	int sumCols[NUM_COLS];
	//array to hold sums of columns
	
	for (row = 0; row < rows; row++)
	//add sums of rows
	{
		sum = 0;
		//initialize sum variable
		for (col = 0; col < cols; col++)
		{	
			sum += array[row][col];
		}
		sumRows[row] = sum;
	}
	cout << "The sums of the rows are.." << endl;
	
	for (row = 0; row < rows; row++ )
	//output sums of rows
	{
		cout << "Row " << row+1 << ": " << sumRows[row] << endl;
 	}

	
	for ( col = 0; col < cols; col++)
	//add sums of columns
	{
		sum = 0;
		//initialize sum variable
		for( row = 0; row < rows; row++ )
		{
			sum += array[row][col];
		}
		 sumCols[col] = sum;
	} 
	 
	cout << "The sums of the columns are.." << endl;
  	for ( col = 0; col < cols; col++)
        //output sums of columns
	{
                cout << "Column " << col + 1 <<": "<< sumCols[col] << endl;
        }
  	
	
	rDiagSum = 0;
	//initialize right diagonal
	for(row = 0 , col = 0; row < rows; row++)
        //find sum of right diagonal
	{
        	rDiagSum += array[row][col];
		col++;        
        }
	cout << "The sum of the right diagonal is " << rDiagSum << endl;
	
	
	lDiagSum = 0;
	//initialize left diagonal
	for(int r = 0, col = rows -1; r < rows; r++)
	//find sum of left diagonal
	{
		lDiagSum += array[r][col];
		col--;
	}
	cout << "The sum of the left diagonal is " << lDiagSum << endl;
	
	
	for(row = 0; row < rows; row++)
	//loop through rows
	{
		for (col= 0; col < cols; col++)
		//loop through columns
		{
			if ((sumRows[row] != sumCols[col]))
			//checks if each of the sums are equal
			{
				cout <<"They are not equal!"<<endl;
				return false;
			}
			else if (sumRows[row] != rDiagSum || sumCols[col] != rDiagSum)
			//checks to see if the sums of the columns or rows match that of the right diagonal sum
			{
				cout <<"The right diagonal doesn't match!" << endl;
				return false;
			}
			 else if (sumRows[row] != lDiagSum || sumCols[col] != lDiagSum)
			//checks to see if the sums of the columns or rows match that of the left diagonal sum
                        {
                                cout <<"The left diagonal doesn't match!" << endl;
                                return false;
                        }

		}
	}		
return true;	
//if all sums match return true
} 





	

