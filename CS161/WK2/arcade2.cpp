/********************************************************************************************************************************************************************************************
 *Author: William George
 *Date Created: 10/8/2014
 *Date last Modified: 10/12/2014
 *File name: aracade2.cpp
 *
 *Overview: The purpose of this program is to take the user input then use loops to determine how many candy bars and how many gum balls they can purchase.
 *
 *Input: user inputs the number of coupons they have
 *
 *Output: the program outputs the number of candy bars and gum balls they can get with the coupons they have...prioritizing the candy bars
 *
 *
 *
 *
 *
 * *****************************************************************************************************************************************************************************************/#include<iostream>
using namespace std;

int main()//start program
{
int gumBalls = 0,// defines # of gum balls and candy bars at 0 and defines the cuoponsLeft as an integer
    candyBar = 0,
    couponsLeft;

cout<<"How many coupons did you win? ";//output
cin>>couponsLeft;//input # of coupon wons

while(couponsLeft>=10)//if there are more than 10 coupons ---> get a candy bar...add candy bar to candy bar counter and take 10 coupons away
	{		
		candyBar = candyBar + 1;
		couponsLeft = couponsLeft - 10;
	}	

while(couponsLeft < 10 && couponsLeft > 2)//if there are less than 10 coupons remainining then buy gum balls. 
	{
		gumBalls = gumBalls + 1;//add one to gum ball counter
		couponsLeft = couponsLeft - 3;//take 3 coupons away from remainder
	}
cout<<"You have "<<candyBar<<" candy bars and "<<gumBalls<<" gum balls and "<<couponsLeft<<" coupons left"<<endl;//output # of coupons left, the # of gum balls and the # of candy bars that can be purchased
return 0;
}//end program
