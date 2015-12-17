/******************************************************************************************************************************************************************************************
*Author: William George
*Date Created: 10/8/2014
*Date Last Modified: 10/12/2014 
*Filename: arcade.cpp
*
*Overview: The purpose of this application is to take the user input for number of coupons then tell the user how many candy bars worth 10 coupons and gum balls worth 3 they can purchase. This program has the purpose of helping the programmer understand some of the math logic in programming.
*
*Input: User inputs the number of coupons they won
*
*Output: the program outputs a warning if the input is invalid then outputs the number of candy bars and gum balls they can get as well as tell the user if they have left over tickets

*
*
*
*
*
*
*
*
*
*
******************************************************************************************************************************************************************************************/

#include<iostream>
using namespace std;

int main()//initialize program
{

int couponsLeft = 0,//defines user variables
    totalCandyBars,
    totalGumBalls,
    couponsRemaining;
const int candyBars = 10,//10 coupons for a candy bar
	  gumBalls = 3;//3 coupons for a gum balls
		
cout<<"How many coupons did you win? ";//asks user how many coupons they won


while(!(cin >> couponsLeft))//validates user input to make sure it is a number and not a character
{
	cin.clear();//clears input if not a number
	cin.ignore(1,'/n');//clears line
	cout<<"Please enter a valid number ";//asks user to reinput # of coupons
}

while(!(couponsLeft >= 0))//makes sure the user has input a valid number greater than zero
{
	cout<<"Please enter a valid number: ";
	cin>>couponsLeft;
}
totalCandyBars = couponsLeft/candyBars;//calcualtes how many candy bars the user can get
totalGumBalls = (couponsLeft%candyBars)/gumBalls;//takes the remainder from the previous equation and calcualtes how many gum balls the user can get
couponsRemaining = couponsLeft - ((totalGumBalls * gumBalls) + (totalCandyBars *candyBars));//finds the remainder

cout<<"With "<<couponsLeft<<" you can get "<<totalCandyBars<<" Candy Bars and "<<totalGumBalls<<" Gum Balls and have "<<couponsRemaining<<" coupons left"<<endl;//output to tell user wht they can get with x number of coupons

return 0;
}//end program
