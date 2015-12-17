/*************************************************************************************************************************************************************************************
 *
 * Author: William George
 * Date Created: 10/31/2014
 * Date Last Modified: 11/2/2014
 * File Name: recConvert.cpp
 *
 * Overview: This program is a decimal to binary, binary to decimal conversion calculator and will give the user a menu to choose from
 * then then give the user the opporunity to enter either a binary or decimal number to convert to its decimal or binary counterpart 
 * respectively. The program will continue looping until the user decides they'd like to quit 
 *
 * Input: The first input the user will be asked for is a choice based on the menu, they will be given the opporunity to choose
 *	1 or 2 to access the conversion caluators or 3 to quit.
 *
 *	The second input will either be a binary or decimal number based on the user choice from the previous menu.
 *	The user will be able to enter any valid non-negative binary or decimal number.
 *
 * 		Input Examples: 15
 *				1010
 *
 * Output: The program will first output a menu from which the user can choose which coverter they would like to use. 
 *	
 *	When the user selects the calculator the menu will then inform the user of their choice then ask for their input
 *	after the user enters their input the program will take the number and convert it to either binary or decimal then
 *	output their original number in both its decimal and binary forms.
 *
 *		Output Examples: 15 in binary is 1111
 *				1010 in decimal is 10
 *
 *
 * **********************************************************************************************************************************************************************************/

#include <iostream>
#include <string>
#include <algorithm>
#include <cmath>
#include <cstdlib>
//preprocess directives

using namespace std;

int toDec (string bin);
int toBin (int num);
int getChoice();
bool isDec(string num);
bool isBin(string num);
void displayMenu();
//set functions and parameters

int decNum;
//set global variable for the decNum
string binary;
//set global variable for the binary number

int main()
//start main
{
	int choice;
	int dec;
	string decimal;
	// set local variables for choice input, decimal input and decimal conversion

	do
	{
		displayMenu();										
		// From text book page 353, displays main menu		
		choice = getChoice();									
		// From text book page 353, gets choice of 1,2,3 from the getChoice function
		dec = 0;
		// set dec to zero for each iteration of loop
		decNum = 0;
		//reset decNum to zero for each loop iteration	
		binary = ' ';
		//reset binary for each loop iteration

		switch (choice)
		//tells program what to do based on user input for choice
		{
			case 1: { 
			// user entered 1 meaning they'd like to convert decimal to binary
					cout << "Please enter a decimal number you would like to convert to binary" << endl;
					cin >> decimal;
					// string input decimal number				
	
					while (isDec(decimal) == false)
					// loop runs isDec function to check if input is valid, if not re-loop 
					{
						cout << "Please enter a valid number: ";
						cin.clear();
						cin.ignore(100, '\n');
						cin >> decimal;
					}
				
					dec = atoi(decimal.c_str());
					//changes decimal to integer and assigns new int to dec
					toBin(dec);
					//calls toBin function to change dec to binary				
					reverse(binary.begin(), binary.end());
					//reverses binary string so the output is correct
					cout << endl;

					cout << decimal <<" in binary is "<< binary << endl << endl;
					
					cout << "Press enter to continue" << endl << endl;
					
					cin.get();
					//clear buffer
                			cin.get();
					//waits for user to press enter
					break;
					//break from case
				}
			case 2:	{
			//user chose 2 meaning they'd like to onvert binary to decimal
					cout << "Please enter the binary number you would like to convert to decimal" << endl;
					cin >> binary;
					//assigns user input to binary variable

					while(isBin(binary) == false)
					//calls isBin function to validate input as binary, if not it loops until a valid input is entered
					{
					 	cout << "Please enter a binary number: ";
                                                cin.clear();
                                                cin.ignore(100, '\n');
                                                cin >> binary;					
						//user reinput
					}	
				
					toDec (binary);
					//calls to decimal function
					cout << endl;				
					cout << binary << " in decimal is " << decNum << endl << endl;
					cout << "Press enter to continue" << endl << endl;
					cin.get();
					//clear buffer
					cin.get();
					//responds to user pressing enter										   
					break;
					//break from case
				}
			case 3: { 
					cout << "Thank you for using my calculator" << endl;
					//Thank you message to user
				}
		}
	}
	while (choice != 3);
	//continue loop until user input is 3

return 0;
//end program
}
/*************************************************************************************************************************************************************************
 *
 *	Entry: None
 *
 *	Exit: None
 *
 *	Purpose: This function just displays the menu which will give the user choices for input
 *
 *
 * ***********************************************************************************************************************************************************************/


void displayMenu()
//similar code on page 353 of text
{
	system("clear");
	//clear screen
	cout << "\n Please enter the corresponding number choice to select from the Menu \n\n";
	cout << "1. Convert Decimal to Binary" << endl;
	cout << "2. Convert Binary to Decimal" << endl;
	cout << "3. Quit Program" << endl << endl; 
}

/***********************************************************************************************************************************************************************
 *
 *	Entry: None
 *
 *	Exit: Returns user choice based on the menu choices in the displayMenu() function
 *
 *	Purpose: The purpose of ths function is to get and validate the users choice from the menu described in
 *	displayMenu()
 *
 *
 * *********************************************************************************************************************************************************************/

int getChoice()												
//similar code on page 353 of text
{
	string fchoice;
	int choice;
	//sets variable that will hold user choice
	cin >> fchoice;
	while(isDec(fchoice) == false)
	{
		
		cout << "Please select a number from the menu: ";
		cin.clear();
		cin.ignore(100 , '\n');
		cin >> fchoice;
		
	}
	choice = atoi(fchoice.c_str());
	while (!(( choice == 1) || (choice == 2) || (choice == 3)))
	//validates choice as the number 1,2 or 3 
	{
		cout << "Please select a number from the menu: ";
		cin >> choice;
	}
	return choice;
	//returns user input
}

/***********************************************************************************************************************************************************************
 *
 *	Entry: This function takes the decimal number input by the user 
 *
 *	Exit: This function converts the decimal input to a binary number and returns the binary number to main
 *
 *	Purpose: The purpose of this function is to convert a decimal number input by the user and 
 *	convert it to its binary form
 *	
 * *********************************************************************************************************************************************************************/


int toBin(int num)
{
        int remain;
	//sets variable to hold the remainder

        if (num > 0)
	//sets base condition, if the number == 0 then it cannot be broken down further it's binary value is 0
        {
                remain = num % 2;
		//sets the variable remain to 1 if the number is odd and 0 if even
                if (remain == 0)
		//if even add a zero to binary number
                        binary = binary + '0';
                else if (remain == 1)
		//if odd add a one to binary number
                        binary = binary + '1';

                num /= 2;
		//divide user input by two
                toBin(num);
		//run function again...until base condition is reached
        }
}

/***********************************************************************************************************************************************************************
 *
 *	Entry: This function takes the binary value input by the user
 *
 *	Exit: This function sends the decimal equivalent to the binary back to main
 *
 *	Purpose: The purpose of this function is to take a binary number input by the user and convert it to decimal format, 
 *	then return it to the main function
 *
 * **********************************************************************************************************************************************************************/

int toDec(string bi)
{
        int length;
	//sets the variable to calcuate the binary string length

        length = bi.length();
	//sets variable length equal to the binary string length

        if(length == 0)
	//if there are no more letters then function will return the final number
                return decNum;
        if (bi.at(0) == '1')
	//if the string at the first position is a 1 then the function will add 2 raised to the length minus one
                decNum = decNum + ( pow ( 2 , length-1 ));
        else
	//if string at first position is 0 then decNum will stay the same
                decNum = decNum;

        bi.erase(0,1);
	//erases a character from the beginning of the string
        toDec(bi);
	//calls function again to evaluate new shorter string
}

/*******************************************************************************************************************************************************************************************
 *  
 *	Entry: 	Function takes users string input
 *    
 *	Exit: 	Function returns either true or false based on the contents of the string input
 *      
 *	Purpose:The purpose of this function is to check the users string input to see if it is a valid positive number
 *           	if the string does not start with zero and is all number characters then the function will return true
 *             	otherwise it will return false
 *         
 *************************************************************************************************************************************************************************************/

bool isDec(string num)										
//code from week 4 lecture
{

	for(int i=0; i < num.length(); i++)
	//checks length of string to make sure it only has characters between 0 and 9
	{
		if(!(num.at(i) >= '0' && num.at(i) <= '9'))
		{		
			return false;
		}
	
	}
	return true;
	//if string has all numbers then return true string is valid
}

/*******************************************************************************************************************************************************************************************
 *  
 *	Entry: Function takes users string input
 *   
 *	Exit: Function returns either true or false based on the contents of the string input
 *     
 *	Purpose: The purpose of this function is to check the users string input to see if it is a valid binary number
 *               all '0' and '1' characters then the function will return true, otherwise it will return false
 *
 * *************************************************************************************************************************************************************************************/


bool isBin(string num)
//code from week 4 lecture
{
	for(int i=0; i < num.length(); i++)
	//checks length of string to make sure it only has characters 0 and 1
        {
                if((num.at(i) != '0' && num.at(i) != '1'))
                	return false;
        }
        return true;
	//if string is binary then return true
}

