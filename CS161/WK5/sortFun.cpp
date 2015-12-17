/*************************************************************************************************************************************************************************************
 *
 *Author: William George
 *Date Created: 10/30/2014
 *Date Last Modified: 11/2/2014
 *File Name: sortFun.cpp
 *
 *Overview: The purpose of this program is to take three values from a user,valiadate and save them to a variable,
 *then sort the values from smallest to largest. The program will then output the values in order from smallest to largest, 
 *changing the location of each variable based on it's size.
 *
 *Input: The user will input three integer values
 *
 *	Input example:	65
 *			27
 *			138
 *
 *Output: The function will then rearrange the values so that they are in order from 
 *	smallest to largest.
 *
 *	Output example:	27
 *			65
 *			138
 *
 *
 * **********************************************************************************************************************************************************************************/

#include <iostream>
#include <string>
#include <cstdlib>
//preprocess directive

using namespace std;

bool isNum (string num);
void sortNum (int &low, int &mid, int &high);
//set parameters for function sortNum

int main()
{
	string loNum, medNum, hiNum;
	int lNum, hNum, mNum;
	// set variables for low, medium and high numbers
	
	cout<<"Enter your first number: "<<endl;
	cin>>loNum;
	while(!(isNum(loNum)))
        //calls isNum validation function and checks to see if input is valid...if not it will loop until valid number is entered
     	{
       		cout << "Please enter a valid number: ";
      		cin.clear();
          	cin.ignore(100, '\n');
            	cin >> loNum;
        }
        
        lNum = atoi(loNum.c_str());
	//change input number string to int

	cout<<"Enter your second number: "<<endl;
	cin>>medNum;
	//input second number
 	while(!(isNum(medNum)))
        //calls isNum validation function and checks to see if input is valid...if not it will loop until valid number is entered
        {
        	cout << "Please enter a valid number: ";
      		cin.clear();
       		cin.ignore(100, '\n');
        	cin >> medNum;
        }
	mNum = atoi(medNum.c_str());
        //change input number string to int
        
	cout<<"Enter your third number: "<<endl;
	cin>>hiNum;
	//input third number
 	while(!(isNum(hiNum)))
        //calls isNum validation function and checks to see if input is valid...if not it will loop until valid number is entered
        {
        	cout << "Please enter a valid number: ";
        	cin.clear();
        	cin.ignore(100, '\n');
       		cin >> hiNum;
        }
        
  	hNum = atoi(hiNum.c_str());
       	//change input number string to int
        //
	sortNum(lNum, mNum, hNum);
	// call sortNum function with the arguments of the numbers just entered
	
	cout<<"The lowest number is "<<lNum<<endl;
	// output new low number

	cout<<"The middle number is "<<mNum<<endl;
	// output new middle number
	
	cout<<"The highest number is "<<hNum<<endl;
	// output new high number
	
return 0;
}

/******************************************************************************************************************************************************************************************
 *
 *	Entry : This function takes the user inputted integer values as variables lowNum, midNum and highNum		
 * 	
 *
 * 	Exit :	Function sorts the values so they are smallest to largest by reassigning the values to different variables
 *
 *	
 *	Purpose : The purpose of this function is to take the three variables referred to by reference and reassign the user 
 *		inputted values based on their size.
 *
 *
******************************************************************************************************************************************************************************************/

void sortNum (int &lowNum, int &midNum, int &highNum)
{
	int temp; 				
	//set temporary int variable

	if (lowNum > highNum)
	//check if the lowest number is higher than the highest
	{
		temp = lowNum;
		lowNum = highNum;
		highNum = temp;
		//swap numbers 
	}
	
	if (midNum > highNum)
	//check if middle number is higher than the highest
	{
		temp = midNum;
		midNum = highNum;
		highNum = temp;
		//swap numbers
	}
	if (midNum < lowNum)
	//check if low number is higher than the middle number
        {
                temp = lowNum;
                lowNum = midNum;
                midNum = temp;
		//swap numbers
        }

}

/*******************************************************************************************************************************************************************************************
 *  
 *	Entry: Function takes users string input
 *    
 *   	Exit: Function returns either true or false based on the contents of the string input
 *      
 *	Purpose: The purpose of this function is to check the users string input to see if it is a valid positive number
 *  		if the string does not start with zero and is all number characters then the function will return true
 *            	otherwise it will return false
 *
 ***********************************************************************************************************************************************************************************/


bool isNum(string num)
{
        if (num.at(0) == '0')
        //checks to see if number starts with zero, if it does it is invalid
        	 return false;
        //
        for(int i=0; i<num.length(); i++)
        //checks length of string to see if characters are all number bettween 0 and 9, if not they are invalid
        {
              if(!(num.at(i) >= '0' && num.at(i) <= '9'))
        		return false;
        }
        return true;
        //if number is valid function returns true
 }
        
        
