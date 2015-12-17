/************************************************************************************************************************************************************************************
 *
 * Author: William George
 * Date Created: 11/3/2014
 * Date Last Modified: 11/6/2014
 * File Name: evenOdd.cpp
 *
 * Overview: This program takes numbers input by a user and the number of numbers the user will
 *  input. The program then takes that array and send it to a function which will calculate the
 *  sum of the even numbers and the sum of the odd numbers then find the difference
 *  between the two.
 *
 * Input: The user will have to input the number of values they'd like to use then input the values:	
 *
 *	Input examples: How many numbers would you like to use: 5
 *			Enter value 1: 1 
 *			Enter value 2: 2
 *			Enter value 3: 1
 *			Enter Value 4; 2
 *			Enter value 5: 1
 * Output: Once the user has input all of their values the function will calculate the sum and return it
 *  to main.
 *
 *	Output Example: The difference between your even and odd values is: 1
 *
 *
 *
 *
 *
 * *********************************************************************************************************************************************************************************/

#include <iostream>
#include <string>
#include <cstdlib>
//preprocess directives

using namespace std;

bool isNum(string num);
//function for input validation
int evenOddDiff(int nums[], int uSize);
//function to sort and calculate even and odd sums using the array and the size of the array as parameters
int main()
{
	string userSize;
	//inputed size of the array, string for input validation
	string number;
	int num;
	int numSize = 0;
	//converted user input 
	const int SIZE = 100;
	//sets maximum array size
	int numArray[SIZE];
	//intializes number array
	int result;
	//variable that will hold the result of the difference

	cout << "This program will take a group of number you select, sum all of the even values,\n sum all of the odd values then find the difference\n" << endl;

	cout << "How many numbers would you like to use? ";
	cin >> userSize;

	while(!(isNum(userSize)))
	//call isNum user validation function until number is valid
	{
		cout << "Invalid input, please try again: ";
		cin.clear();	
		cin.ignore(100, '\n');
		cin >> userSize;
	}

	numSize = atoi(userSize.c_str());
	//change string to integer
	
	cout << "Please enter "<< numSize <<" numbers" <<endl;
	
	for(int index = 0; index < numSize; index++)
	//adds numbers to the array
	{
		cout << "Enter value "<<index + 1<<": ";
		cin >> number;
		while (isNum(number) == false)
		{
			cout << "That is not a number, try again: "; 
			cin.clear();
			cin.ignore(100, '\n');
			cin >> number;
		}
		num = atoi(number.c_str());
		numArray[index] = num;
	}
	

	cout <<"The numbers you entered are: ";
	
	for(int c = 0; c < numSize; c++)
	//outputs user entry for array
	{
		cout << numArray[c] << " ";
	}
	

	result = evenOddDiff(numArray, numSize);	
	//calls evenOddDiff function with arguments of array and array size thensets difference returned as the result
	
	cout << endl <<"The difference between the even and odd values is: "<< result << endl;

return 0;
//end program
}

/**************************************************************************************************************************************************************************************
 *	
 *	Entry: This function takes a numeric string input from the user
 *
 *	Exit: This function outputs whether the string input is numeric or not
 *
 *	Purpose: The purpose of this function is to validate the user input as numeric
 *
 * *********************************************************************************************************************************************************************************/


bool isNum(string numInput)
{
        for(int i=0; i < numInput.length(); i++)
	//checks length of string to make sure all characters are numbers 
	{
		if(!(numInput.at(i) >= '0' && numInput.at(i) <= '9'))
		return false;
     	}
    	return true;
}

/***********************************************************************************************************************************************************************************
 *
 *	Entry: This function takes the arguments for the numbers input by the user as well as 
 *	the amount of numbers they entered.
 *
 *	Exit: This function will output the difference of the sums of the even and odd integers
 *
 *	Purpose: The purpose of this function is to sort the even and odd numbers then find the
 *	difference in the sums 
 *
 * *******************************************************************************************************************************************************************************/


int evenOddDiff(int nums[], int uSize)
{
	int evenSum = 0;
	int oddSum = 0;
	//initialize sum variables and set to 0
	int diff;
	//variable to store difference

	for (int x = 0; x < uSize ; x++)
	//loops through array to seperate even and odd inputs
	{	
		if (nums[x]%2 == 0)
		//if even 
			evenSum = evenSum + nums[x];
			//add number to total evens
		else
		//if odd
			oddSum = oddSum + nums[x];
			//add number to total odds
	}
	
	diff = evenSum - oddSum;
	//find differnce between even and odd sums
	return diff;
}

