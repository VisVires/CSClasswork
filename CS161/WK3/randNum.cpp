/*************************************************************************************************************************************************************************************
 *Author: William Geoorge
 *Date Created: 10/13/2014
 *Date Last Modified: 10/13/2014
 *File Name: randNum.cpp
 *
 *Overview: A simple program that prints random numbers using a loop, the psuedorandom numbers are chosen based on an algorithm that uses time.
 *
 *Input: No input needed
 *
 *Output: This program uses a loop to give out 10 random numbers between one and 1000
 *
 *Sample Output:	65			
 *			565
 *			486
 *			654
 *			79
 *			688
 *			982
 *			372
 *			15
 * 			872
 * **************************************************************************************/
#include<iostream>
#include<ctime> // header needed to use time
#include<cstdlib> // header needed to use srand and rand
#include<cstdio> //header needed to use NULL
using namespace std;

int main()
{
	int randomNumber; //declares the variable
	srand(time(NULL));//sets the seed for the alogrithm as the time
	for (int x=0; x < 10; ++x)	//loop runs 10 times to give 10 numbers
	{
		randomNumber = rand()%1000+1; //finds a random number between 1 and 1000
		cout<<randomNumber<<endl; //outputs the random number
	}

return 0;//end program
}
