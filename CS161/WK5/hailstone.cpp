/********************************************************************************************************************************************************************************************
 * Author: William George
 * Date Created: 10/30/2014 
 * Date Last Modified: 11/1/2014
 * File Name: hailstone.cpp
 *
 * Overview: 	This program uses a recursive function to calculate the number of steps it
 *  		take for a user inputed number to reach 1 by a hailstone sequence. The
 *		hailstone sequence divides the number by two if even, if odd the sequence
 *		multiplies by 3 and adds one to get the next integer.
 *
 *
 * Input: 	User will input a value to be count down from.
 *
 *
 * Output:	The program will then output the number of steps it takes to countdown
 *		from the user number and reach 1.
 *
 * *************************************************************************************************************************************************************************************************************************************************************************/

#include <iostream>
#include <string>
#include <cstdlib>
//preprocess directive is iostream

using namespace std;

void hail(int x, int &counter);
//set parameters for the hailstone function
bool isNum(string num);
//sets parameter for input validation function


int counter;
// global variable counter for counting the number of function calls or steps for the hailstone sequence

int main()
{
	string startNum;
	//original user input
	int sNum;
	// sNum = the starting number to count down from
	
	cout << "Please enter a number greater than 0 you would like to count down from: ";
	cin >> startNum;
	// gathers user input for starting number	
	while(!(isNum(startNum)))
	//calls isNum validation function and checks to see if input is valid...if not it will loop until valid number is entered
	{
		cout << "Please enter a valid number: ";
		cin.clear();
		cin.ignore(100, '\n');
		cin >> startNum;
	}
	
	sNum = atoi(startNum.c_str());
	//converts string to int
		
	hail(sNum, counter);
	// call hail stone sequence function

	cout << "It took " << counter << " steps to reach 1 from " << sNum <<" using the hailstone sequence"<<endl; 

	return 0;
	//end program
}
/******************************************************************************************************************************************************************************************** *		
 * 	Entry: This function takes the user inputed number
 *
 *	Exit: The output for this function is the steps used and the resulting number based on the previous calculation
 *
 *	Purpose: The purpose of this function is to perform the hailstone sequence where if a number is odd multiply it by 3 
 *		and add one and if it is even divide the number by 3 eventually reaching the base case of the number equalling 1.
 *
 * ****************************************************************************************************************************************************************************************/

void hail (int x, int &counter) 
{

		if (x == 1)
		//base case
		{
			cout<<"Finally on step "<<counter<<" the number is "<<x<<"."<<endl;
			return;
		}
		else if ( x % 2 == 0)
		//if number is even divide it by two
		{
			cout<<"On step "<<counter<<" the number is "<<x<<"."<<endl;
			hail((x / 2), ++counter);
		}
		else
		//if number is odd multiply it by 3 and add 1
		{
			cout<<"On step "<<counter<<" the number is "<<x<<"."<<endl;
			hail((x * 3 + 1), ++counter);
		}
}

/*******************************************************************************************************************************************************************************************
 *	
 *	Entry: Function takes users string input
 *
 *	Exit: Function returns either true or false based on the contents of the string input
 *
 *	Purpose: The purpose of this function is to check the users string input to see if it is a valid positive number
 *		if the string does not start with zero and is all number characters then the function will return true
 *		otherwise it will return false
 *
 * *************************************************************************************************************************************************************************************/


bool isNum(string num)
{
	if (num.at(0) == '0')
	///checks to see if number starts with zero, if it does it is invalid
		return false;
	
        for(int i=0; i<num.length(); i++)
	//checks length of string to see if characters are all number bettween 0 and 9, if not they are invalid
        {
                if(!(num.at(i) >= '0' && num.at(i) <= '9'))
                return false;
        }
        return true;
	//if number is valid function returns true
}

