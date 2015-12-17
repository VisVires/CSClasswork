/************************************************************************************************************************************************************************************
 *
 * Author: William George
 * Date Created: 11/4/2014
 * Date Last Modified: 11/6/2014
 * File Name: grades.cpp
 *
 * Overview: This program takes the users input as grades on a quiz from 0 to 5. Then it sorts each 
 * of these grades into it's respective cell in an array. There the array is incremented to show the 
 * number of times that grade was input. The program then outputs a written histogram showing the  
 * frequency of each grade.
 *
 * Input: The progam asks the user to input a grade between 0 and 5. 
 *
 *		Input Example: Enter a grade between 0 and 5 or enter -1 to quit: 	1
 *											2
 *											2
 *											4
 *											5
 *											2
 *
 * Output: The program will then output the frequency of each grade
 *		
 *		Output example: 	0 grade(s) of 0
 *					1 grade(s) of 1
 *					3 grade(s) of 2
 *					0 grade(s) of 3
 *					1 grade(s) of 4
 *					1 grade(s) of 5
 *
 *
 **********************************************************************************************************************************************************************************/

#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <string>
//preprocess directives

using namespace std;

bool isGrade(int num);
//prototype function to validate numeric inputs

int main()
{
	const int SIZE = 6;
	//sets max array size at 6
	int gradeArray[SIZE] = {0};
	//initializes each element of the array at 0
	int grade = 0; 
	//sets each grade at zero

	cout << "Enter a grade between 0 and 5 or enter -1 to quit: ";
	cin >> grade;	
	while (!(isGrade(grade)))
	//calls function to validate grade as numeric
	{
		cout << "Invalid Grade, please re-input: ";
		cin.clear();
		cin.ignore(100, '\n');
		cin >> grade;
	}

	while(grade != -1)
	//loops unless exit condition of -1 is input
	{
                switch(grade)
		//increments each section of the array based on inputs from user
                {
                        case 0: gradeArray [0]++;
                                break;
 			case 1: gradeArray [1]++;
                                break;
 			case 2: gradeArray [2]++;
                                break;
 			case 3: gradeArray [3]++;
                                break;
 			case 4: gradeArray [4]++;
                                break;
 			case 5: gradeArray [5]++;
                                break;   
		}
		cout << "Enter a grade between 0 and 5 or enter -1 to quit: ";
		cin >> grade;
		
		while (!(isGrade(grade)))
		//calls function to validate grade as numeric between -1 and 5
        	{
                	cout << "Invalid Grade, please re-input: ";
                	cin.clear();
                	cin.ignore(100, '\n');
                	cin >> grade;
        	}
		
	}
	cout <<"\n\n\n\n\n";
	
	for (int index = 0; index < SIZE; index++)
	//outputs written histogram of frequency of each grade
	{	
		cout << gradeArray[index] <<" grade(s) of "<<index << endl;
	}
	
	cout <<"\n\n\n\n\n";
	return 0;
}
/*************************************************************************************************************************************************************************************
 *
 *	Entry: Function will take the number input from the unit
 *
 *	Exit: Function will return true or false based on whether the number falls in the appropriate range
 *
 *	Purpose: The purpose of this function is to make sure the user input falls withing the range of the
 *	grades possible.
 *
 *
 * *********************************************************************************************************************************************************************************/

bool isGrade(int numInput)
{
       
       	if(!( numInput >= -1 && numInput <= 5))
	//validates grade input as being between -1 and 5
   	{
		return false;
     	}
        return true;
}

