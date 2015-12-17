/*************************************************************************************************************************************************************************************
 *
 * Author: William George
 * Date Created: 11/15/2014
 * Date Last Modified: 11/16/2014
 * File Name: symArrays.cpp
 *
 * Overview: This program takes 3 command line inputs from the user each for the size of the 
 * array inputs. Then the user can input the values to fill the arrays using a single line input 
 * with each value seperated by a single space.
 *
 *
 * Input(s): This program takes two inputs from the user. First it will take the command line
 * input from the user when they call the program. 
 * 	Example Input: symArrays 3 4 5
 *
 * The second input will be the input for each array with each value seperated by a space.
 * 	Example Input :	1 2 1
 * 			2 4 4 2
 * 			1 5 5 3 1 
 *
 * Outputs: The program will then output whether the arrays are symmetrical
 *	Example Output: Array 1 is symmetrical
 *			Array 2 is symmetrical
 *			No Match! 5 does not equal 3
 *
 *
 *
 *
 * **********************************************************************************************************************************************************************************/

#include <iostream>
#include <cstdlib>
#include <string>

using namespace std;

bool sym(const int *array, int arrSize);
//function to analyze user input to see if array is symmetrical

int main(int argc, char * argv[])
{
	int array1size = 0;
	int array2size = 0;
	int array3size = 0;
	//initalize array sizes
	
	int index;
	//loop variable

	array1size = atoi(argv[1]);
        array2size = atoi(argv[2]);
        array3size = atoi(argv[3]);
	// sets the three array size variables to command line inputs

	int *array1 = new int[array1size];
	int *array2 = new int[array2size];
	int *array3 = new int[array3size];
	//initalize 3  dynamic arrays based on command line input size

	if(argc != 4)
	//validates the command line input
	//exit if command line is incorrect
	{
		cout <<"Please enter the size of your 3 arrays"<<endl;
		exit(1);
	}

	cout << "You chose arrays with "<< array1size <<" "<< array2size <<" "<<array3size << " values." <<endl;
	//output array sizes

	cout << "Please enter "<<array1size<< " values for array 1 each seperated by a single space: "; 	
	
	for (index = 0; index < array1size; index++)
	//fill array 1
	{
		cin >> array1[index];
	}
	cout << endl;
	
	cout << "You entered: ";
	for (index = 0; index < array1size; index++)
	//outputs the first array input
        {
                cout << array1[index] << " ";
        }
	cout << endl;
	cin.ignore(100,'\n');
	//clear buffer


	cout << "Please enter "<<array2size<< " values for array 2 each seperated by a single space: ";
       
	for (index = 0; index < array2size; index++)
	// fill array 2
        {
                cin >> array2[index];
        }
	cout << endl;

        cout << "You entered: ";
        for (index = 0; index < array2size; index++)
        //outputs array 2 input
	{
                cout << array2[index] << " ";
        }
	cout << endl;
	cin.ignore(100, '\n');
	//clear buffer


	cout << "Please enter "<<array3size<< " values for array 3 each seperated by a single space: ";
        for (index = 0; index < array3size; index++)
	//fill array 3
        {
                cin >> array3[index];
        }
	cout << endl;

        cout << "You entered: ";
        for (index = 0; index < array3size; index++)
	//output array 3 input
        {
                cout << array3[index] << " ";
        }
	cout << endl;
	cin.ignore(100, '\n');
	//clear buffer

	if (sym(array1, array1size))
	//call symmetrical array function for array 1 using arguments array 1 and array 1 size
	{	
		cout << "Array one is symmetrical\n " << endl;
	}
	
	if (sym(array2, array2size))
	//call symmetrical array function for array 2 using arguments array 2 and array 2 size
	{
		cout << "Array two is symmetrical\n " << endl;
	}
	
	if (sym(array3, array3size))
	//call symmetrical array function for array 3 using arguments array 3 and array 3 size
	{	
		cout << "Array three is symmetrical\n " << endl;
	}

	delete [] array1;
	delete [] array2;
	delete [] array3;
	// clear the heap and delete memory used for arrays
	
return 0;
}

/************************************************************************************************************************************************************************************
 *
 *	Entry : This function takes the parameters of a pointer to the user designated array and 
 *	the array size
 *
 *	Exit  : This function outputs either true or false based on whether the array values are symmetrical
 *
 *
 *	Purpose: The purpose of this function is to move from the outsides of the string input inwards to see 
 *	if the values match. Then output true or false based on whether or not they match. 
 *
 ************************************************************************************************************************************************************************************/

bool sym(const int *array, int arrSize) 
{
	int i, j;
	//declare integers for loops
	for (i = 0, j = arrSize - 1; i < (arrSize/2) ; i++, j--)
	//initialize variables one variable starts at the beginning the other at the end increments one and decrements the other
	{
		if (array[i] != array[j])
		//checks for equality
		{
			cout << "No Match! " << array[i] << " doesn't equal "<<array[j]<<endl;			
			return false;
			//if no match return false
		}
	}
return true;
}
