/***************************************************************************************************************************************************************
 *
 *Author: William George
 *Date Created: 10/30/2014
 *Date Last Modified: 10/31/2014
 *File Name: recFun.cpp
 *
 *	Overview:	The purpose of this program is to take a user input x and return the number in the fibonacci sequence that corresponds to said number.
 *
 *
 *
 *	Input:		This program takes an positive integer input from a user which will correspond to a specific location within the fibonacci sequence
 *			Input example: 5
 *
 *
 *	Output:		The program will first ask for a number that represents a number within the fibonacci sequence. It will then return the number
 *			it corresponds to in the sequence.
 *			Output example: " The 5th number in the fibonacci sequence is 3
 *
 *
 * *************************************************************************************************************************************************************/

#include <iostream>
#include <string>
#include <cstdlib>
// preprocess directives

using namespace std;

int fib(int fibLoc);
// set parameters for fib function
bool isNum(string x);
// input validation function

int main()
{
	string input;
	int lNum; 
	// set variable for user input
	int fibNum;	
	//set return variable for fibonacci number

	cout << "Which number in the Fibonacci sequence would you like to know? ";
	
	cin >> input;
	
	 while((isNum(input) == false))
	{
                cout << "Please enter a valid number: ";
                cin.clear();
                cin.ignore(100, '\n');
                cin >> input;
        }

        lNum = atoi(input.c_str());

	//input user selection	

	fibNum = fib(lNum);
	// call fibonacci function with argument of user inputted number

	cout<<"The "<<lNum<<"th number in the Fibonacci sequence is "<<fibNum<<"."<<endl; 
	// output number at selected position in fib number

	return 0;
}

/******************************************************************************************************************************************************************************************
 *
 * 	Entry:		Function takes the user inputted value		 
 *	
 *	Exit :		Function returns the calcualtion for corresponding number in the fibonacci sequence
 *
 *	Purpose:	The purpose of this function is to take a number then use it to set the position in the fibonacci sequence it will calculate what the fibonacci number is based on the users input. Fibonacci function starts at 0.
 *
 * ***********************************************************************************************************************************************************************************/

int fib(int fibLoc)
{

	if (fibLoc == 0)
	//base case, if location is zero the number is also 0
		return 0;
	else if (fibLoc == 1)
	//second base case if location is one then the fib number is 1
		return 1;
	else
		return fib(fibLoc - 1) + fib ( fibLoc - 2);
	//in every other case the fib number = num -1 + num - 2
}
/*********************************************************************************************************************************************************************************
 *
 *	 Entry: Function takes users string input
 *
 *	 Exit: Function returns either true or false based on the contents of the string input
 *	 
 *	 Purpose: The purpose of this function is to check the users string input to see if 
 *	 it is a valid positive number if the string does not start with zero and is all number 
 *	 characters then the function will return true, otherwise it will return false
 *
 * *********************************************************************************************************************************************************************************/

bool isNum(string numInput)
{
	for(int i=0; i < numInput.length(); i++)
	//looks through letters to make sure numbers are all digits if not return false
	{
    		if(!(numInput.at(i) >= '0' && numInput.at(i) <= '9'))
  		return false;
	}
        return true;
}
