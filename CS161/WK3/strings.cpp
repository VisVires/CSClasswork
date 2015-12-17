
/****************************************************************************************************************************************************************
 *Author : William George
 *Date Created: 10/13/2014
 *Date Last Modified: !0/13/2014
 *File Name: strings.cpp
 *
 *Overview: The purpose of this program is to take a string input from the user then return that string input letter by letter,
    both forwards and backwards as well as count the characters in the string statement using for loops and the at function
 *
 *Input:The user input some sort of string phrase or word such as : "Seattle Seahawks!" or "I like hamburgers"
 *
 *Output: The program will then read the string back to the user both forwards and backwards then output the number of letters in the statement. Outputs will be like the 
following: "Seattle Seahawks", "skwahaeS elttaeS" and "Your input had 15 letters. 
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *****************************************************************************************************************************************************************/

#include<iostream>
#include<string> 										//Header file needed for string characters
#include<cctype>


using namespace std;


int main()
{
	string userString;									//defines the userString value
	int numLetters = 0;									//intitalizes the number of letters to zero
	



	cout<<"Please Enter a word you would like me to read back to you backwards:"<<endl;     //user prompt to input the phrase or word of their choosing
	cin>>userString; 	                                                               //captures the content of the string the user input and stores it to userString
        cout<<"Your word is spelled:"<<endl;



        for(int i = 0;i < userString.length();i++)                                              //outputs the users phrase letter by letter including spaces
        {
                cout<<userString.at(i)<<endl;
        }




        cout<<"Your word backwards is spelled:" <<endl;




        for(int i = userString.length()-1; i >= 0; i--)						//outputs the users phrase letter by letter backwards including spaces.
                                                            	        	                //I got this code from stackoverflow.com/questions/13185736/loop-to-print-string-backwards
	{
		cout<<userString.at(i)<<endl;							 //counts the number of characters in the word                                                                                                                                 
		if(isalpha(userString.at(i)))                                                   //code can be used to determine if a character at position is alphabetic
		{
			numLetters = numLetters + 1; 						//adds to the number of letters counter
		}
        }



	cout<<"Your phrase has "<<numLetters<<" letters."<<endl; 
	
	cin.ignore();										//resets cin
        numLetters = 0;										//resets the number of letters at zero for the next run through                                                                
                                                                                              
	cout<<"Now please Enter a phrase you would like me to read back to you backwards:"<<endl;	//user prompt to input the phrase or word of their choosing

	

	getline(cin,userString);								//captures the content of the string the user input and stores it to userString
	cout<<"Your phrase is spelled:"<<endl;
	
	for(int i = 0;i < userString.length();i++)						//outputs the users phrase letter by letter including spaces
	{
		cout<<userString.at(i)<<endl;							
	}
	




	cout<<"Your phrase backwards is spelled:" <<endl;
	
	for(int i = userString.length()-1; i >= 0; i--)
												//outputs the users phrase letter by letter backwards including spaces.	
												//I got this code from stackoverflow.com/questions/13185736/loop-to-print-string-backwards
	{
		cout<<userString.at(i)<<endl;
		if(isalpha(userString.at(i)))							//code can be used to determine if a character  at position i is alphabetic
		{	
			numLetters = numLetters + 1;						//adds to the number of letters counter
		}
	}



	cout<<"Your phrase has "<<numLetters<<" letters."<<endl;				//outputs number of letters in phrase
return 0;
}
