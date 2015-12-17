/**************************************************************************************************************************************************************
 *
 * Author: William George
 * Date Created: 11/20/2014
 * Date Last Modified: 11/23/2014
 * File Name: findMode.cpp
 *
 * Overview: This program will use a function with the parameter of a vector of
 * ints that will take ints from a user until they'd like to stop then the
 * function will take the vector and return the mode(s)
 *
 * Inputs: The user will input positive numbers to be stored in the vector or 
 * they can input a -1 to stop. 
 *
 * 	Example Inputs: 1, 22 ,37 ,14, 22, 1, 12, -1
 *
 * Outputs: The program will then output the mode of the values the user input
 *
 * 	Example Output: The mode(s) of the numbers input is(are): 
 * 	1 
 * 	22 
 *
 * **********************************************************************************************************************************************************/

#include <iostream>
#include <vector>
#include <cstdlib>
#include <algorithm>

using namespace std;

vector<int> findMode(vector<int> num, int size);	//function to find the mode using the vector
bool isNum(string num); //input validation function

int main()
{
	vector<int> numbers; 	//main vector
	vector<int> modeVect; 	//vector to hold modes
	int numInput = 0; 	//variable to hold user input
	int vectSize;	//size of the vector variable
	string num;	//takes user input
	char ch;	//characted for cin.get

	cout << "This program will find the mode of a series of numbers you input\n" << endl;
	cout << "Press enter to continue" << endl;
	cin.get(ch);//gets users enter input
 

	while(numInput != -1)
	// loop until numInput = -1
        {
		system("clear");
		//clear screen
		cout <<"Enter a positive number or \"STOP\" to stop: ";
		cin >> num;
		//gather user input

		while( num != "STOP" && isNum(num) == false)
		//loop while input is not a number
       		{
                	cout << "Error: Invalid Input. Please Re-Input: ";
                	cin.clear();
                	cin.ignore(100, '\n');
			cin >> num;
   		}

		if(num != "STOP")
		{
			numInput = atoi(num.c_str());
			//change input to integer
			numbers.push_back(numInput);
			//add number input to vector
        	}
		else
		{
			numInput = -1;
			//if num = STOP set numInput to -1
		}
	}
	
	sort(numbers.begin(), numbers.end());
	//sort numbers from low to high
	vectSize = numbers.size();
	//get vector size
	
	modeVect = findMode(numbers, vectSize);
	// call mode function and set it to mode vector 

	for (int i = 0; i < modeVect.size(); i++)
	///output mode vector
	{
		cout << "The mode(s) of the set of numbers you input is " << modeVect[i];
	}		
	cout << endl;
	
return 0;
}

/**************************************************************************************************************************************************************
 *
 * Entry: This function takes the vector numbers by reference and the size of
 * the vector
 *
 * Exit: This function will return a new vector with the mode of the numbers 
 * vector
 *
 * Purpose: The purpose of this function is to find the mode of a set of numbers
 *
 * ***********************************************************************************************************************************************************/


vector<int> findMode(vector<int> num, int size)
{
	vector<int> mode;
	//set mode vector
	int counter = 1;
	//number counter to see frequency of numbers  
	int mostNums = 0;
	//variable to see the most frequent number
	int i;
	//loop variable

	for(i = 0; i < size; i++)
	{
		if(num[i] == num[i+1])
		//checks if value is equal to the next value
		{	
			counter++;
			//if so increment counter

			if (counter == mostNums)
			//if counter is equal to the most frequent variable then add to mode vector
			{
				mode.push_back(num[i]); 
			}
			else if (counter > mostNums)
			//if counter is greater than previous most frequent value
			{
				mode.clear();
				//clear mode vector
				mostNums = counter;
				//set new number as the most frequent 
				mode.push_back(num[i]);
				//add new value to mode vector at position one
			}
		}
		else
		{
			counter = 1;
			//reset counter
		}		
		
	}
	for(i = 0; i < size; i++)
	//output users original output sorted
	{
		cout << num[i] << " ";
	}
	cout << endl;

	return mode;
}

/************************************************************************************************************************************************************************************
 *
 * Entry: This function takes a string input represnting a number
 *
 * Exit: This function returns true or false based on whether the figure is a number
 *
 * Purpose: The purpose of this function is to check if the input by the user is a number
 *
 * **********************************************************************************************************************************************************************************/

 bool isNum(string numInput)
 {
        for(int i=0; i < numInput.length(); i++)
	//loop length of number input
        {
                if(!(numInput.at(i) >= '0' && numInput.at(i) <= '9'))
		//if number input is not a number then return false
                return false;
        }
        return true;
 }

