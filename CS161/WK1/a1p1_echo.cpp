/********************************************************************************Author:		William George
*Date Created:		10/2/2014
*Last Modification Date:10/2/2014	
*File Name: 		echo.cpp
*Overview: 	
		This program prompts for a user input reads the input and determines whether it is in the range of 1 to 9999
*Inout:		
*		The input will be an integer between 0 and 10000
*Output		
*		The output will be "Please Enter Integer to be printed" 
*		followed by the user input, then followed by either a comment saying "YOur number is not between 0 and 10000" followed by "Your number is: " or if it is in the range
*		the user will get the output "Your number is "user input" "
*
*
* ***************************************************************************/

#include<iostream> //include input output stream
using namespace std;
int main()//initialize program
{
	int input_value; //a variable that will hold a value of type int or whole number
	input_value = 1;//sets the input_value to 1
	cout<<"Please Enter a whole number bettween 0 and 10000 to be Printed: ";//tells user to input value
	cin>>input_value; //get number from user

	while ((input_value < 1 || input_value > 9999))//tells the user to enter a value between 0 and 10000, formula found in text book program 5-3
			
				{
				cout<<"Your number is not between 0 and 10000"<<endl;//tells user their input is invalid
			
				break;//ends loop
				}
			
	
	cout<<"Your number is: "<<input_value<<endl;//tells user what their input was
  	
	return 0;//return
}//end program

