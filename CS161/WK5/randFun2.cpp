/*************************************************************************************************************************************************************************************
 *
 *Author: William George
 *Date Created: 10/30/2014
 *Date Last Modified: 10/31/2014
 *File Name: randFun.cpp
 *
 *Overview: The purpose of this program is to take the inputs for low and high value from the user then give the user a random number within that range passing the value by reference
 *
 *
 *Input: User will input the low and high values to set the range for their number.  
 *
 *		Input examples: high number: 3501
 *				low number: 102
 *
 *
 *Output: The program will either output a random number based on the users range or will output some error message if the user did not input a valid value.
 *
 *
 * 		Output Example: Your random number is 1032
 *
 * *****************************************************************************************************************************************************************************************************************************************************************************/


#include <iostream>
#include <ctime>
#include <cstdlib>

using namespace std;

void rand_int(const int &min, const int &max, int &val);
//sets parameters for the rand_int function

int main()
{
	int lowNum, highNum, randNum; 
	//set variables
	
	cout<<"Enter the low value for your range: ";
	
	while(!(cin>>lowNum))		
	//set low number and check to see if input is a number
	{
		cout<<"That is not a valid input, please try again: ";
		cin.clear();
		cin.ignore(100, '\n');

	}
	
	while(lowNum < 0)		
	//validate input is greater than zero
	{
		cout<<"Please enter a value that is greater than 0: ";
		
		while(!(cin>>lowNum))	
		//validate reinputs to make sure they are valid numbers
        	{
                	cout<<"That is not a valid input, please try again: ";
                	cin.clear();
                	cin.ignore(100, '\n');
        	}	
	}
	
	cout<<"Enter the high value for your range: ";						
        
	while(!(cin>>highNum))		
	//set high number and check to make sure it is a number 
        {
                cout<<"That is not a valid input, please try again: ";
                cin.clear();
                cin.ignore(100, '\n');

        }
        
	while(highNum <= lowNum)	
	//validates input is larger than than low number input
        {
                cout<<"Please enter a value that is greater than your minimum value: ";

                while(!(cin>>highNum))	
		//validates re-input is a number
                {
                        cout<<"That is not a valid input, please try again: ";
                        cin.clear();
                        cin.ignore(100, '\n');
                }
        }
	cout<<"Your number will be between "<<lowNum<<" and " <<highNum<<endl;			
	//output range

	rand_int(lowNum, highNum, randNum);							
	//calls function rand_int and uses arguments low and high number
	
	cout<<"Your random number is: "<<randNum<<endl;						
	//output random number passed by reference.

return 0;
}

/************************************************************************************************************************************************************************************
 *
 *	Entry: This function takes the minimum value input by the user and the maximum passed by reference
 *
 *	Exit: This function outputs a random number passed by reference within the range of the minimum to the maximum values
 *
 *	Purpose: This take the user's range and outputs a random number based on that range
 *
 *
 * **********************************************************************************************************************************************************************************/

void rand_int(const int &min,const int &max, int &val)
{
	unsigned seed; 										
	int range;
	
	seed = time(0);										
	//sets seed based on time
	srand(seed);										
	//sets srand
	
	range = max - min;									
	//calculate range

	val = rand()% range + min;								
	//uses range and grabs a pseudorandom number from the range using the minimum value

}	 
