/******************************************************************************
 *Author: William George
 *Date Created: 10/13/2014
 *Date Last Modified: 10/13/2014
 *File Name: name.cpp
 *
 *Overview: This program takes a user's name entered First Middle Last then reads the
 *name back to them last, first, middle initial. If the person only enters two names then
 *the program will read last, first back to them.
 *
 *Input: User enters their name in the format First space Middle space Last
 *	Input example: John Edward Smith
 *	Input errors: The program is built so that a person can only enter two or three
 *	names, if they use one or more than three then they will be asked to reinput
 *
 *Output: The program prompts the user to enter their name, reads the user name 
then rearranges it to last, first, middle initial
 * if there is no middle name then it just returns last, first
 * 
 *	Output Example: Smith, John E.
 *		or	Smith, John
 *	If there is an input error the program asks the user to please enter their
 *	full name.
 *
 *****************************************************************************/
#include<iostream> 										//header required to use cin and cout
#include<string> 										//header required to use string

using namespace std;

int main()
{		
	string fullName, first_name, last_name, middle_name; 					//declares name variables
	char spaceOne; 										//defines the character for the first space
	char spaceTwo; 										//defines the character for the second space
	char mInitial; 										//defines the middle initial
	int numSpaces = 0; 									//intiates the numSpaces variable
		
	cout<<"Please enter your full name in the format First Middle Last "<<endl; 
												//prompt to enter user name in correct format
	
	getline(cin,fullName);									//captures user input and stores it as fullName

	for (int i = 0; i < fullName.length(); ++i)
												//calculates the number of spaces in the length of the full name variable
	
		{	
			if (fullName[i] == ' ')							//If the full name has a space then add to
												//the numSpaces counter
				++numSpaces;	 
		}	
	if(numSpaces == 1)
	{											//If num spaces is 1 then read to the first space and set that value as
												//first name then take the rest (minus the space) and set it to last name

		spaceOne = fullName.find(' ');							//find the space and store it to spaceOne

		first_name = fullName.substr(0, spaceOne);					//read up to space one and store as first_name
	
		last_name = fullName.substr(spaceOne+1, string::npos);				//read the rest minus the space and store as last_name

		cout<<last_name+ ", " +first_name<<endl;					//output name last, first
	}
	else if(numSpaces == 2)
        {											//If there are more than two spaces use this conditional statement

                spaceOne = fullName.find(' ');							//sets the first space

                first_name = fullName.substr(0, spaceOne);					//defines first name

		spaceTwo = fullName.rfind(' ');							//finds the last space from the end of the
												//string
		middle_name = fullName.substr(spaceOne+1, spaceTwo);				//finds and defines the middle_name as the one between spaces

		last_name = fullName.substr(spaceTwo+1, string::npos); 				//reads the last name from the second space

		mInitial = middle_name[0];							//takes the first character of the middle_name and stores it as the middle initial
		mInitial = toupper(mInitial);
		
		cout<<last_name +", "+first_name+" "+mInitial+"."<<endl; 			//outputs last, first middle initial
	}
	else
	{
		cout<<"Please try again"<<endl; 						//asks user to try again if input did not have one or two spaces
		
	}
return 0;											//end
}
