/*************************************************************************************************************************************************************
 *
 * Author: William George
 * Date Created: 11/04/2014
 * Date Last Modified: 11/6/2014
 * File Name: stringMix.cpp
 *
 * Overview: This program takes one c-style string from a user, then rearranges the letters randomly then outputs the new random word
 * while keeping the original word the same. The program also allows the user to randomly sort the word multiple times.
 *
 * Input: The program will take a word input from the user and save to a c-style string
 *		Input Example: Please enter a word: word
 *
 * Output: The program will then output the word with randomly sorted letters:
 * 		Output Example: rodw
 *
 *	The program will also ask the user to rearrange the original word again 
 *
 *
 * ***********************************************************************************************************************************************************/

#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <string.h>
//sets preprocess directives

using namespace std;

void reArrange(char *firstWord,char *secondWord,int wordLength);
//prototype for function that will take word input in c-style string and the length of the input

int main()
{
 	const int SIZE = 30;
	//max word size
	char fWord[SIZE];
	//sets first c-style string
	char sWord[SIZE];
	//initialize second c-style string
	int wordLength = 0;
	//integer to hold variable for the length of the word input
	char again;
	//variable that holds whether user would like to play again
	char *word1 = fWord;
	char *word2 = sWord;

	cout << "This program will take a word and rearrange the letters for you " << endl;
	cout << "Please enter your word: ";
	cin >> fWord; 
	//take in user word input

	cout << "You entered " << fWord << endl;
	wordLength = strlen(fWord);
	//check c-style string length
	
	do
	{
		reArrange(word1, word2, wordLength);
		//call function to rearrange word using the two arrays and the word length
		cout <<"The word: " << word1 << " rearranged is " << word2 << endl;
			
		cout << "Enter Y to rearrange again :";
		//output sorted words
		
		cin >> again;
		//gathers user input if user would like to go again
	}	
	while (again == 'y' || again == 'Y');
	//rearrange word input again
	
return 0;
}

/*******************************************************************************************************************************************************************************************
 *
 *	Entry: This function takes c-style strings, one empty and the other having a user inputed word, and the words length.
 *
 *	Exit: This function then outputs a randomly sorted word based on the users original entry. 
 *	The new word is stored in the second empty array
 *
 *	Purpose: The purpose of this function is to take the characters from one array move them to a second array then sort
 *	them randomly. Giving a mixed up version of the original word back to the user along with their original word.
 *
 *
 * **************************************************************************************************************************************************************************************/

void reArrange(char *firstWord, char *secondWord, int wordLength)
{
	unsigned seed;
	seed = time(0);
	//sets seed to time
	srand(seed);
	//calls function srand
	int letter1;
	//sets first letter as int
	int letter2;
	//sets second letter as int
	char temp;
	//temporar variable
	

	for (int i = 0; i < wordLength; i++)
	//loop makes second c-string equal to first c-string
	{
		secondWord[i] = firstWord[i];
	}

	for (int i = 0; i < wordLength; i++)
	//loops through the entire word length once
	{
			letter1 = rand()% wordLength;
			//sets first letter to a random integer
			letter2 = rand()% wordLength;
			//sets second letter to a random integer
			temp = secondWord[letter1];
			//stores a random position on the first word to letter 1
			secondWord[letter1] = secondWord[letter2];
			//store second word letter at random position to another random position
			secondWord[letter2] = temp;	
			//store letter at first position to second position
	}
	
	return;	
}	
