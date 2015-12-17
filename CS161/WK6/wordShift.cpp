/*************************************************************************************************************************************************************************************
 *
 * Author: William George
 * Date Created: 11/5/2014
 * Date Last Modified: 11/6/2014
 * File Name: wordShift.cpp 
 *
 * Overview: This purpose of this program is to use c-strings and pointer arithmetic to manipulate the string. 
 * With the program commands a user can shift a string either left or right a user sepcified number of spaces. 
 * Also the user can reverse the string. The user will then have the opportunity to manipulate the same string 
 * again until they command the program to quit.
 * 
 * Input: The user will make several inputs for this program, first they will be asked to enter a word they'd like
 * to manipulate then they will be asked to enter one of the 4 commands which will allow them to manipulate the string.
 *			Input Examples:	Enter Word: wordshift
 *					Enter Command: R2
 *					Enter Command: L2
 *					Enter Command: rev
 *					Enter Command: quit
 *
 * Output: The program will then output whatever manipulation or a good-bye message if they enter the command quit.
 *
 * 			Output Examples: Let's shift wordshift right 2 spaces
 *						ftwordshi
 *					 Let's shift ftwordshi left 2 spaces	
 *						wordshift
 *					 Let's reverse wordshift
 *					 	tfihsdrow
 *					 Thank you!
 *
 * *********************************************************************************************************************************************************************************/

#include <iostream>
#include <string.h>
#include <string>
#include <stdio.h>
#include <cstdlib>
//preprocess directives

using namespace std;

void getMenu();
//prototype for menu function
bool isNum(char num);
//function which does input validation
void rev(char *useString, int length);
//function for revering C-string
void lShift(char *useString, int length, int wShift);
//function to shift letters left and add extra letters to the end of the c-string
//calling useString pointer and using the length and user commanded shift
void rShift(char *useSting, int length, int wShift);
//function to shift letters right and add extra letters to the beginning the c-string
//calling useString pointer and using the length of the word and user commanded shift

int main()
//start main
{
	string userWord;
	//takes userWord input 
	string userCommand;
	//takes user command input
	const int SIZE = 30;
	//sets max size for c-string
	char userString[SIZE];
	//intialize user word
	char command[3];
	//sets user command c-string for shift commands
	char wordShift, ch;
	//gathers shift length
	int shift, wordLength;
	//set as distance of word shift and user inputted word length
	
	cout << "Please enter a word you would like to manipulate: " << endl;
	cin >> userWord;
	//gathers userWord as string

	strcpy (userString, userWord.c_str());
	//changes users string input to a c-string

	wordLength = strlen(userString);
	//find length of users c-string
	
	system("clear");
	//clear screen

	getMenu();
	//call function to output command menu
	
	do
	{
		cin.ignore(100,'\n');
		//clear buffer
		cout << "Enter Your command :";
		cin >> userCommand;
		//set user command input
	
		
		if(userCommand == "rev" || userCommand == "REV" || userCommand == "Rev")
		//if the user enter the rev command execute
		{
		 	cout << "Let's reverse the word: "<< userString << endl; 
			rev(userString, wordLength);
			//call reverse word function
			cout << userString << endl;
			//output new reversed user string
		}
		
		else if(userCommand.at(0) == 'L')
		//if user enters a command string that starts with upper case L
		{ 
			strcpy(command, userCommand.c_str());
			//change command into a c-string
			wordShift = command[1];
			//set the second character of the string to wordShift
			
			while (!(isNum(wordShift)))
			//use while loop to see if wordShift is a number, if not input number
                        {
                                cout << "Incorrect input, please enter how far you would like to shift the word: "<< endl;
				cin.clear();
				cin.ignore(100, '\n');
				cin >> wordShift;
                        }
			
			shift = wordShift - '0';
			//change wordShift into an integer shift
			
			cout << "Let's shift the word: " << userString <<" "<<shift << " spaces left."<< endl;
			
			lShift(userString, wordLength, shift);
			//call left shift function with arguments for the userString c-style string, the word's length and the shift inputted by the user
			cout << userString << endl;
		}
		
		else if(userCommand.at(0) == 'R')
		//if user enters a command string that starts with upper case R
		{ 
			strcpy(command, userCommand.c_str());
			//change command string to c-style string
			wordShift = command[1];
			//extra second character of command string
			
			while (!(isNum(wordShift)))
			//check whether input is numeric, if not loop until it is
			{
				cout << "Incorrect input, please enter how far you would like to shift the word: "<< endl;
				cin.clear();
				cin.ignore(100, '\n');
				cin >> wordShift;
			} 

			shift = wordShift - '0';
			//change numeric input to an integer
			cout << "Let's shift the word "<< userString <<" "<< shift <<" spaces right."<< endl;

			rShift(userString, wordLength, shift);
			//call right shift function using arguments of user c-string, c-string length and user designated shift
			cout << userString << endl;
		}
		
		else if(userCommand == "quit" || userCommand == "Quit" || userCommand == "QUIT")		
		//if user input is quit then output thank you and end program
		{
			cout << "Thank you" << endl;
		}	
		
		else	
		// if user command is not one of the four conditions output please try again
		{
			cout<< "Incorrect input, please try again" << endl;
		}		
		
	
	}
	while (!(userCommand == "quit" || userCommand == "Quit" || userCommand == "QUIT"));
	//continue loop until user enters quit in one of the three above iterations 
return 0;
}

/*******************************************************************************************************************************************************************************
 *
 *	Entry: None
 *
 *	Exit: This program outputs a menu with choices for commands by the user
 *
 *	Purpose: The purpose of this function is to output a menu outlining 
 *	commands for the user
 *
 * ******************************************************************************************************************************************************************************/


void getMenu()
{
	cout << "To reverse the word enter: rev\n\n";
	cout << "To shift the word left enter \"Lx\" where x \n is the number of spaces you would like to shift the word.\n\n";
	cout << "To shift the word left enter \"Rx\" where x \n is the number of spaces you would like to shift the word.\n\n";
	cout << "To quit enter \"quit\"\n\n";

}

/*********************************************************************************************************************************************************************************
 *
 *	Entry: This function takes a character based number input from a user
 *
 *	Exit: This function outputs true or false based on whether the input was 
 *	numeric or not.
 *
 *	Purpose: The purpose of this function is input validation for numeric inputs
 *	by the user
 *
 * *******************************************************************************************************************************************************************************/



bool isNum(char numInput)
{
	if(!( numInput >= '0' && numInput <= '9'))
	//checks to see if character is numeric
	{
        	return false;
	}
	return true;
}

/******************************************************************************************************************************************************************************
 *
 *	Entry: This function takes a c-string input from the user, and the length of the string
 *
 *	Exit: The function reverses the string and saves it to the same c-string using pointers
 *
 *	Purpose: The purpose of this function is to take a word from a user then reverse using 
 *	pointer arithmetic 
 *
 * ****************************************************************************************************************************************************************************/

void rev(char *useString , int length)
{
	char *begin, *end, temp;
	//sets three pointers to hold certain positions in the c-string
	begin = useString;
	//sets begin to beginning of c-string
	end = useString;
	//sets end to beginning of c-string
	
	for (int index = 0; index < length - 1; index++)
	//loop moves end pointer to the end of the c-string minus the null character
	{
		end++;
	}

	for (int i = 0; i < length/2; i++)
	//loop switches the characters of the string from the outsides in
	{
		temp = *end;
		//store last character in temp
		*end = *begin;
		//move first character to last character
		*begin = temp;
		//move last character to first character
		
		begin++;
		//increment begin pointer right in string
		end--;
		//decrement end pointer left in string
	}
}

/**************************************************************************************************************************************************************
 *
 *	Entry: This function takes a c-string input from the user, the length of the string and 
 *	the degree of shift based on the users command
 *
 *	Exit: This function shifts the string right the number of spaces the user specified
 *
 *	Purpose: This functions purpose is to take a string then shift each character right a user 
 *	specified amount adding any overflowing values off the end of the string to the beginnng of 
 *	the string.
 *
 *
 * **********************************************************************************************************************************************************/


void rShift(char *useString, int length, int wShift)
{
	char temp;
	//set holder variables
	int index, i;
	//set loop variables

	for (i = 0; i < wShift; i++)
        //loop to shift word user specified amount
	{
                temp = *(useString + (length - 1));
		//set last character to temp variable
                
		for(index = (length-1); index > 0; index--)
		//loops to move each character 1 space right
                {
                        *(useString + index) = *(useString + index - 1);
                }

                *(useString + 0) = temp;
		//moves end character to beginning character
        }

}
/*************************************************************************************************************************************************************
 *
 *	Entry: This function takes a c-string input from the user, the length of the string and the 
 *	degree of shift based on the user command
 *
 *	Exit: This function shifts the string left the user specifed amount based on the command
 *
 *	Purpose: The purpose of this function is to take a user string then use pointer arithmetic
 *	to shift each character left the user specifed amount adding any overflowing values to the 
 *	end of the string
 *
 * *********************************************************************************************************************************************************/



void lShift(char *useString, int length, int wShift)
{
        char temp;
	//set holder variables
        int i, index;
	//set loop variables
 	
	for (i = 0; i < wShift; i++)
        //loop to shift word user specified amount
        {
		temp = *(useString + 0);
		//set first  character to temp variable

		for(index = 0; index < (length-1); index++)
		//loops to move each character 1 space left
		{			
			*(useString + index) = *(useString + index + 1);	
		}

		*(useString + index) = temp;
		//moves beginning character to last position
		
   	}	
}

