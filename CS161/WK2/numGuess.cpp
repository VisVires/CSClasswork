/*************************************************************************************************************************************************************************************
Author: William George
Date Created: 10/8/2014
Last Modification Date: 10/12/2014
File Name: numGuess.cpp

Overview: The purpose of this program is to ask a first user for a number and start a guessing game with a second user to guess that number. If the user guesses correctly the program will inform them and allow them to play again. If not then the program will give the second user five guesses to guess corectly and will adjust the range to fit the user's guess. After five guesses the program will tell the user the value and the difference between the value and the last guess made.  

Input(s): First User inputs the Secret Number
Second User inputs his/her guess and has five oppotunities to do so. Also they can input Y or y to play again

Output:
This program outputs a  prtompt asking each user for their number, then outputs the number of guesses left, the range in which to make the guess and the difference between the guess and the secret number. It also outputs a prompt to ask if the user would like to play again.


*************************************************************************************************************************************************************************************/
#include<iostream>
#include<cmath>
using namespace std;

int main()
{
int secretNumber = 0, //defines variables
    userGuess,
    difference,
    numOfGuess,
    lowNumber,
    highNumber;	
char again;

do
{
	
	cout<<"Player One: Please choose a number from 1 to 5000: ";//User 1 prompt for secret number to be stored
	
	while(!(cin>>secretNumber))//while the number is a valid number and not a character carry out the command. If not clear the input and try again
	{
		cin.clear();//clear input
		cin.ignore(1,'/n');//ignore to new line
		cout<<"Please enter a valid number from 1 to 5000: ";//please re-enter number
	}
	
	while(secretNumber > 5000 ||  secretNumber < 1)//defines the range and makes sure user number is within the originally set range
	{
		cout<<"Please enter a number from 1 to 5000: ";//tells user to input a value within the correct range
		cin>>secretNumber;//input number
	}
	numOfGuess = 5;//defines number of guesses
	lowNumber = 1;///defines starting low value
	highNumber = 5000;//defines starting high value

	cout<<"Player Two: Please guess the number from " <<lowNumber<<" and "<<highNumber<<":";//prompt for user 2 guess
	
	while(!(numOfGuess==0))//makes sure user 2 still has remaining guesses using while loop
	{
		cin>>userGuess;//if their are guesses left then guess, if not do not
		
		/*****while(!(cin>>userGuess));//this error checking did not work for whatever reason. I left it in still because I'd like to know why it didn't work this time. Pretend the other cin>>userGuess above is not there if you'd like to test it. This ignores the guess if it is not a number
		{	
			cin.clear();
               		cin.ignore(100,'/n');
               		cout<<"Please enter a valid number from "<<lowNumber<<" to "<<highNumber<<":";
       		}*****/

		
		numOfGuess = numOfGuess -1;//changes counter for numOfGuesses
		
		if(userGuess == secretNumber)//if user guess correct do this

		{
			cout<<"Congratulations you got it right!"<<endl;
			break;
		}
		
		else if(userGuess > secretNumber)//if # is too high tell user and reset range with new values and inform them how many guesses are left
		{
			cout<<userGuess<<" is too freaking high!"<<endl;			
			cout<<"You have "<<numOfGuess<<" guesses remaining "<<endl;
			highNumber = userGuess;
 			if(numOfGuess != 0)//tells the user the range remaining but only if they have guesses remaining
                       {
                               cout<<"Please enter a number between "<<lowNumber<<" and "<<userGuess<<":";
                       }
                       else
                       {
                               break;//if the user has no guesses remaining break from the loop
                       }

		}
		else//if user guess is too low tell user and tell user how many guesses are left
		{
			cout<<userGuess<<" is too low!"<<endl;
			cout<<"You have "<<numOfGuess<<" guesses remaining "<<endl;
			lowNumber = userGuess;
			if(numOfGuess != 0)//if guesses are not zero output new range
			{
				cout<<"Please enter a number between "<<userGuess<<" and "<<highNumber<<":"<<endl;
			}
			else
			{
				break;//break from loop
			}
		}
	
		 
	}
	
	if(numOfGuess == 0)//if guesses left = 0 then find the difference between the last guess and the secret number
	{
		difference = secretNumber - userGuess;
		if (difference <= 0)//if the number is negative then change it to a positive. I could have used the abs function here too but it wasn't working properly
		{
			difference = difference * -1;
		}	
		cout<<"You're all out of guesses! The number was "<<secretNumber<<". You were "<<difference<<" away!"<<endl;//tell user the number of guesses is 0 and the difference between the last guess and the secret number 
	}		
	cout<<"Type 'Y' to play again "<<endl;//asks user if they want to play again
	cin>>again; //page 261 in the book...defines user input
}
while (again == 'Y' || again == 'y');//end of do while loop...tells user to enter y to play again...any other input means quit
return 0;
}

