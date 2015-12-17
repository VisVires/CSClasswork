/******************************************************************************
 * Author: William George
 *Date Created: 10/14/2014
 *Date Last Modified: 10/14/2014
 *File Name: loop.cpp
 *
 *
 *Overview: The purpose of this program is to compare two user inputs to one another. My program uses a loop to decide whether each input has similar letters and if they do have letters in common then the program will output those letters.
 *
 *
 *Input: Here the user inputs two phrases they'd like to compare, these phrases can be one or more words and the program compares the characters in the first phrase to those in the second.
 *
 *Input examples:	input one : "fish stick" 
 *			input two:  "fire truck"
 *Output:
 *For the output the program looks at the two line then compares them letter by letter along the entire length of the word then returns the numbers that are identical.
 *
 *Output examples:	Output: "fi tck" 
If a letter is capitalized it will not return the letter, because they are not equal.  
 *
 *
 *
 *`
 ****************************************************************************/
#include <iostream> // header file for input/output
#include <string>	//header file needed for strings

using namespace std;

int main()
{
	string string1, string2; //declare the strings
	 

	cout<<"Please input a phrase you would like to compare: ";
	getline(cin, string1);				// captures user input for string 1
	cout<<"Input a second phrase to compare to the first: ";
	getline(cin,string2);				// captures user input for string 2
	
	cout<<"Your phrases have the following characters in common: ";
	for(int x = 0; x < string2.length(); x++)	//tells the program to go the length of string 2 letter by letter until the end of the string
	{
		for (int i = 0; i < string1.length(); i++)	//tells the program for every time they go down the length of string two they must go down the entire length of string one as well
			{
				if (string1.at(i) == string2.at(x))//compares the values of string one to those of string two to see if they are equivalent
				{	
					cout<<string1.at(i);	//if the letter is in both strings then the program will output the letter
				}
			}	
	}
	cout<<endl;		//ends the line
return 0;			// end program
}		
