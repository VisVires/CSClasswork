/******************************************************************************************
 *Author: William George
 *Date Created: 10/13/2014
 *Date Last Modified: 10/13/2014
 *File Name: randNum2.cpp
 *
 *
 *Overview: The purpose of this program is to give a random number inside the range desired for the user. The user will set the low 
 *threshold and then the high threshold and the program will give them a number based on their entry after validating their original input.
 *
 *
 *Input: The user inputs a low and high number to set their range for their random number.  *
 *
 *Input Examples: 	Low Value: 2, 300, 32000 
 *			High Value:8, 660, 35320	
 *
 *Output: After the user input the program will either tell the user the input was invalid or it will tell the user what their range is and what 
 *their number is based on that range.
 *
 *Output Examples:	User Value: 5, 532, 34561 
 *			
 *			
 *
 *
 * **************************************************************************************/



#include<iostream>	//include header for input/output
#include<cstdlib>	//include header for srand & rand
#include<ctime>		//include header for time

using namespace std;

int main()
{
	int lowNum, highNum, range_size = 0, userNum;						//sets the minimum and maximum numbers for range and the size of the range 
										 
	unsigned seed;										//defines the seed as unsigned
	
	

	seed = time(0);										//sets seed equal to time
	srand(seed);										//initializes random number generator
	
	
	cout<<"Input a positive number that will be the lowest in your range of numbers: ";	//output asking user to input a minimum value for range
												//user input minimum value
	

	while(!(cin>>lowNum))									//while loop verifies number is not a character
	{											
			cout<<"That is not an integer, please try again: ";			//asks user to input again
			cin.clear();								//clears buffer
			cin.ignore(100,'\n');							//ignores the rest of the line till the next line
													//user re-input value 
	}
	

	
	while(lowNum < 0)									//makes sure startng number is a positive value
	{
			cout<<"That number is negative, please input a positive value: ";
			while(!(cin>>lowNum))							//checks that possible second input is an integer and not a character
       			{
                        	cout<<"That is not an integer, please try again: ";
                        	cin.clear();
                        	cin.ignore(100,'\n');
        		}

	} 
	 if (cin.get() != '\n')									//if more exist than just the end of the line then end the program 
	{										
			cin.ignore(100,'\n');
			cout<< "Start again "<<endl;;
			exit(0);
	}


	cout<<"Input a second number that will be at the top of your range: ";			//asks for maximum value
	

									
	while(!(cin>>highNum))									//validates that user input is a number and not a character
	{
			cout<<"That is not an integer, please try again: ";			//tells user to try again
                        cin.clear();
                        cin.ignore(100,'\n');
	}
	



	while(highNum < lowNum || highNum == lowNum)						//loop makes sure user maximum is higher than user minimum
	{
			cout<<"The number at the top of your range really should be greater than the one at the bottom. Try a higher number: ";
									

			while(!(cin>>highNum))							//validates user re-input as an integer and not a character
        		{
                        	cout<<"That is not an integer, please try again: ";		//tells user to enter a valid number
                        	cin.clear();							// clear buffer
                        	cin.ignore(100,'\n');						//ignore next 100 characters or till next line               			
			}
	}
	 if (cin.get() != '\n')									//if more exist than just the end of the line then end the program
        {
                        cin.ignore(100,'\n');
                        cout<< "Start again "<<endl;;
                        exit(0);
        }

	
	cout<<"Your number will be bettween "<<lowNum<<" and "<<highNum<<endl;			//tells user the range their number will be in
		
	
	range_size = highNum - lowNum;								//finds the range and stores the size

	
	userNum = rand()%range_size + lowNum;							//uses range size and the low number to choose a random number from
	cout<<"Your number is "<<userNum<<". This number was randomly generated based on the current time and your range, please use for whatever you see fit."<<endl;
												//outputs random number inside user range
	
return 0;											//end program
}

