/*************************************************************************************************************************************************************
 *
 * Author: William George
 * Date Created: 11/5/2014
 * Date Last Modified: 11/6/2014
 * File Name: arrayAdd.cpp
 *
 * Overview : The purpose of this program is to take two groups of 
 * values from a user and store each in an individual array. The program 
 * will first ask the user to enter the amount of numbers they would like 
 * in each array. Then the program will send the two arrays along with the 
 * user inputs to a function which will add the numbers based on their position 
 * in each array. Then it will store the sum in a third empty array. The program 
 * uses pointers to reference each array.  
 *
 *
 * Input : The user will first input the size of each group then will inpur the values 
 * for each group.
 *
 *	Input Examples: How many numbers would you like in each group: 2
 *		Group1	Please enter value number 1 :1
 *			Please enter value number 2 :2
 *		Group2 	Please enter value number 1 :1
 *			Please enter value number 2 :2
 *
 * Output : The program will then output the sum of the values in each respective position.
 *		
 *	Output Examples:The sum of the values at position 1 is 2
 *			The sum of the values at position 2 is 4
 *
 *
 * **********************************************************************************************************************************************************/

#include <iostream>
#include <string>
#include <cstdlib>
//preprocess directives

using namespace std;

void arraySum(int *arrayOne, int *arrayTwo, int *arrayThree,int length);
//set prototype for arraySum program, parameters are pointers to arrays and passing length by value
bool isNum(string num);
//input validation function prototype

int main()
{
	string arraySizeInput, numInput;
	//strings for input validation
	int arraySize = 0;
	//initialize array size
	const int SIZE = 50;
	//max array size
	int array1[SIZE];
	int array2[SIZE];
	int array3[SIZE];
	//set 3 arrays
	int *arrayOne, *arrayTwo, *arrayThree;
	//set pointers
	cout << "This program will take a group of values then add it to another group" << endl;
	cout << "How many values would you like to add from each group? ";
	cin >> arraySizeInput;
 
	while (isNum(arraySizeInput) == false)
	// loop runs isDec function to check if input is valid, if not re-loop
	{
		cout << "Please enter a valid number: ";
        	cin.clear();
        	cin.ignore(100, '\n');
        	cin >> arraySizeInput;
	}

	arraySize = atoi(arraySizeInput.c_str());
	//change to integer value
	cout << endl << "Now let's fill the first group" << endl;	

	for(int index = 0; index < arraySize; index++)
	//loop to take strings for first groups of numbers
	{
		int number = 0;
		cout << "Please enter value number " << index+1 << ": ";
		cin >> numInput;

		 while (isNum(numInput) == false)
                //validate user input
		{
			cout << "Please enter a valid number: ";
        		cin.clear();
        		cin.ignore(100, '\n');
       			cin >> numInput;
		}
		number = atoi(numInput.c_str());
		//change each string to an integer
		array1[index] = number;
		//place each integer in the array
        }                           
	arrayOne = array1;
	//set pointer = to array one	

	cout << endl <<"Now lets fill the second group "<< endl;
	 for(int index = 0; index < arraySize; index++)
	//loop takes string values for the second group
        {
		int number = 0;
                cout << "Please enter value number "<< index+1 << ": ";
                cin >> numInput;
		//takes number input

                 while (isNum(numInput) == false)
                //loop checks number with input validation function
		{
                        cout << "Please enter a valid number: ";
                        cin.clear();
                        cin.ignore(100, '\n');
                        cin >> numInput;
                }
                number = atoi(numInput.c_str());
		//changes number to c-string
                array2[index] = number;
		//adds integer to array
        }
	arrayTwo = array2;
	//sets array2 to pointer
	arrayThree = array3;
	//sets array3 to pointer

	arraySum(array1, array2, array3, arraySize);
	//call to array sum function using arrays as parameters and arratsize
	cout << endl;
	
	for(int index = 0; index < arraySize; index++)
	//output the result coming from third array where stored sums are
	{	
		cout << "The sum of the numbers in position " << index +1 <<" is " << array3[index] << endl;
	}
	cout<<endl;
return 0;
}
/***********************************************************************************************************************************************************************************
 *
 *	Entry: This function takes a (hopefully) numeric string input from the user.
 *
 *	Exit: This function returns either true or false based on whether the entire
 *	input is numeric or not
 *
 *
 *	Purpose: The purpose of this function is input validation for numeric inputs
 *
 * *******************************************************************************************************************************************************************************/

bool isNum(string numInput)
 {
        for(int i=0; i < numInput.length(); i++)
	//loop to check if string input is numeric
        {
                if(!(numInput.at(i) >= '0' && numInput.at(i) <= '9'))
                return false;
        }
        return true;
 }

/*********************************************************************************************************************************************************************************
 *
 *	Entry: This function takes three identically sized arrays via pointers from main, 
 *	two of which were filled out by the user and the third being empty. It also takes 
 *	the size of the arrays.
 *
 *	Exit: This function returns the sum of the two arrays which is stored to the third
 *	array. 
 *	
 *	Purpose: The purpose of this function is to add the values of two arrays together
 *	based on the corresponding position from each array, then store those values in a 
 *	third array.
 *
 * ******************************************************************************************************************************************************************************/

void arraySum(int *arrayOne , int *arrayTwo, int *arrayThree, int length)
{
	for (int counter = 0; counter < length; counter++)
	//loop uses pointers to go through each position of array and add array1 to array2 then store the result in array3. Then increment to next position
	{
		*arrayThree = (*arrayOne + *arrayTwo);
		*arrayOne++;
		*arrayTwo++;
		*arrayThree++;
	}
}
