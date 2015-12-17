/******************************************************************************************
 *Author: William George
 *Date Created: 10/30/2014
 *Date Last Modified: 10/31/2014
 *File Name: refFun.cpp
 *
 *
 *Overview: The objective of this program is to take two strings and compare them to see if
 *they have the same contents. The program will check each character individually.
 *
 *Input: The user will input two strings
 *
 *		Input example: 	string1:  Donkey
 *				string2: Shrek
 *
 *Output: The program will use a simple function to return whether the two strings have 
 *the same contents. 
 *
 *		Output example:	The letter q  matches, it is at position 4
 *				The letter q does not match the letter f, so your words
 *				don't match
 *
 * **************************************************************************************/


#include <iostream>															
//Preprocess Directives
#include <string>

using namespace std;

bool stringMatch(string &str1, string &str2);							
//declare the stringMatch function and the parameters
bool goodInput(string word);

int main()											
//start main program
{
	string string1, string2;

	cout<<"Please enter your first word: "<<endl;
	cin>>string1;										
	//input first word and set it to variable string1
												
	while(goodInput(string1) == false)
	//call good input fuction to check if the word is valid
	{
		cout<<"Invalid input...please try again: ";
		cin.clear();
		cin.ignore(100, '\n');
		cin>>string1;
	}

	cout<<"Enter a second word you'd like to compare to the first: "<<endl;
	cin>>string2;										
	//input second word and set it to variable string2
	 while (goodInput(string2) == false)
        //call goodInput function to check if the word is valid
	{
                cout<<"Invalid input...please try again: ";
		cin.clear();
		cin.ignore(100, '\n');
                cin>>string1;
        }

	if (string1.length() == string2.length())						
	//check to see if the strings are equal lengths
	{											
	//if they are not equal in length they can't be equal words
											
		if(stringMatch(string1, string2) == true)					
		//call stringMatch funtion if the stringMatch function returns true then the strings match
		{
			cout<<"Your words match!"<<endl;
		}
		else
		//if stringMatch returns false then the words don't match
		{
			cout<<"Sorry your words don't match"<<endl;
		}						 				
	}
	
	else
	{
		cout<<"Sorry your words don't match"<<endl;					
	// if words length doesn't match then the words can't
	}
	
return 0;											
// end program
}
/************************************************************************************************************************************************************************************
 *	
 *	Entry: Function takes user input word
 *
 *	Exit: Function returns true or false based on whether the word has letters.
 *
 *	Purpose: Check if user input is a valid word or if it has any non-alphabetic char
 *
 *
 * **********************************************************************************************************************************************************************************/
bool goodInput(string word)
{
	for (int i = 0; i < word.length(); i++)
	//check word length
	{
		if (!(isalpha(word.at(i))))
		//make sure entire word length is alphabetic
		{
			return false;
			//if not return false
		}
	}

	return true;
	//if word is alphabetic return true
}
/************************************************************************************************************************************************************************************
 *	Entry: First string input string1 and second string inut string2
 *
 *	Exit: 	For i through the length of string2 chack if the letters match in the
 *		strings. Output whether they match or not and the position they match.
 *
 *	Purpose: Read the strings and compare the letters to see if they match/
 *
 * *************************************************************************************************************************************************************************************/


bool stringMatch(string &str1, string &str2)						
//reference string variables					
{	
	for (int i = 0; i < str2.length();i++)						
	// loop to look at each individual letter in the word 
	{						
      
		if (!(str1.at(i) == str2.at(i)))					
		//check character equality 
		{	
			return false;
			//if characters are not equal return false
		}
	}

	return true;
}

