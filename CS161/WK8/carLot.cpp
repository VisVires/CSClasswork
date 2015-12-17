/*************************************************************************************************************************************************************************************
 *
 * Author: William George
 * Date Created: 11/20/2014
 * Date Last Modified: 11/23/2014
 * File Name: carLot.cpp
 *
 * Overview: This program allows a user to enter the information for a new car on a car
 * lot including the make, model, year, the date it was purchased, the price of purchase,
 * and if it was sold the date is was sold, and the sale price. It will also list all cars
 * that have been pruchased and not sold and the total profit for sales for the month.
 *
 * Input: First the user will input an integer for their choice based on the choice
 * function, then they will be able to enter the car information if they chose to add an
 * entry
 *
 * Output: The program will first output a menu prompting the user to choose a number.
 * Then depending on that input the program will output prompts to add information about a 
 * car or it will list either all the cars that have been purchased but not sold, or the 
 * total profits of the car lot. 
 *
 * *********************************************************************************************************************************************************************************/

#include <iostream>
#include <iomanip>
#include <string>
#include <cstdlib>
#include <vector>

using namespace std;

struct Date
{
	int day;
	int month;
	int year;

	Date()
	{
		day = 0;
		month = 0;
		year = 0;
	}
};
//set and intialie date struct
struct Car
{
	string make;
	string model;
	int year;
	Date datePurchased;
	double purchasePrice;
	bool isSold;
	Date dateSold;
	double salePrice;
};
//set car struct

void displayMenu();//function to show menu
int getChoice();//function to get user choice
void addEntry(vector<Car>& cars);//function to add an entry to parent vector
void listInventory(vector<Car>& cars);//function to list current inventory
void monthProfit(vector<Car>& cars);//function to calculate sales
bool dayValid(int day, int month);//function to check validity of date input
bool yearValid(int year);//function to check validitiy of year input

int main()
{
	vector<Car> carsInfo;
	//set vector to hold car info
	int choice;
	//variable to hold users choice
	char ch;
	//variable to get enter from user

	do
	//loop until user enters 4
	{
		displayMenu();
		//show menu
		choice = getChoice();
		//use getChoice to validate and get user choice

		switch(choice)
		{
			case 1: addEntry(carsInfo);
				//call add entry function
				cout << "Press enter to return to menu" << endl;
				cin.get(ch);
				cin.get(ch);
				//wait for user to press enter
				break;

			case 2: listInventory(carsInfo);
				//call list inventory function
				cout << "Press enter to return to menu" << endl;
				cin.get(ch);
				cin.get(ch);
				//wait for user to press enter
				break;
			
			case 3: monthProfit(carsInfo);
				//call month profits function
				cout << "Press enter to return to menu" << endl;
				cin.get(ch);
				cin.get(ch);
				//wait for user to press enter
				break;

			case 4:	cout << "Thank you, Good-Bye" << endl;
				//leave if user enters 4
		}
	}
	while (choice != 4); 
return 0;
}
/*************************************************************************************************************************************************************************************
 *
 * Entry: No entry
 *
 * Exits: Displays menu from which user can choose whether they'd like to add an entry,
 * list the current lot, display the months total profits or quit
 *
 * Purpose: Display menu for users
 *
 * **********************************************************************************************************************************************************************************/

void displayMenu()
{
        system("clear");
	//clear screen
        cout << "Car Lot Inventory:\n\n";
        cout << "Please select a number" << endl;
        cout << "1: Add Entry to Inventory" << endl;
        cout << "2: List Available Vehicles" << endl;
        cout << "3: Calculate Profits for Month" <<endl;
        cout << "4: Quit\n\n" << endl << endl;
}

/************************************************************************************************************************************************************************************
 *
 * Entry: No entry
 *
 * Exit: Output an integer based on users selection
 *
 * Purpose: To get and validate user input for menu choice
 *
 * **********************************************************************************************************************************************************************************/

int getChoice()
{
        int choice;

        while (!(cin >> choice))
        //validate choice as int
        {
                cout << "Please enter a valid choice between 1 and 4: ";
                cin.clear();
                cin.ignore(100, '\n');
        }
        while (choice < 1 || choice > 4)
        //validate choice is between 1 and 4
        {
                cout << "Please enter a number between 1 and 4: ";
                while (!(cin >> choice))
                {
                        cout << "Please enter a valid choice between 1 and 4: ";
                        cin.clear();
                        cin.ignore(100, '\n');
                }
        }
        return choice;
        //return int to main
}

/*************************************************************************************************************************************************************************************
 *
 * Entry: This function takes the vector for the struct Cars
 *
 * Exit: This function returns an updated vector with an additional entry
 *
 * Purpose: The purpose of this function is to allow the user to input the information for
 * a new car added to the lot.
 *
 ***********************************************************************************************************************************************************************************/

void addEntry(vector<Car>& cars)
{
	
	Car newCar;
	//set variable for struct
	char sold;
	//character to hold input regarding whether car is sold
	
	cout << "Enter Make: ";
	cin >> newCar.make;
	//input make

	cout << "Enter Model: ";
	cin >> newCar.model;
	//input model

	cout << "Enter Year: ";
	cin >> newCar.year;
	while (yearValid(newCar.year) == false)
        {
                cout << "Please enter a valid year in the format YYYY: ";
                cin.clear();
                cin.ignore(100, '\n');
                cin >> newCar.year;
        }
	//input and validate year input

	cout << "Enter Day Purchased: ";
	cin >> newCar.datePurchased.day;
	while (newCar.datePurchased.day > 31 || newCar.datePurchased.day < 1)
	{
		cout << "Invalid day, please re-input: ";
		cin.clear();
		cin.ignore(100, '\n');
		cin >> newCar.datePurchased.day;
	}
	//input and validate day input

	cout << "Enter Month Purchased: ";
        cin >> newCar.datePurchased.month;
	while (newCar.datePurchased.month < 1 || newCar.datePurchased.month > 12)
	{
		cout << "Invalid month, please re-input: ";
		cin.clear();
		cin.ignore(100,'\n');
		cin >> newCar.datePurchased.month;
	}
	//input and validate month input

	while (dayValid(newCar.datePurchased.day, newCar.datePurchased.month) == false)
	{
		cout << "That day is not valid for that month" << endl;
		cout << "Please re-input day: ";
		cin.clear();
                cin.ignore(100, '\n');
                cin >> newCar.datePurchased.day;
		cout << "Please re-input month: ";
		cin >> newCar.datePurchased.month;
	}
	//validate month and day inputs so non-existant days are not chosen

	cout << "Enter Year Purchased: ";
        cin >> newCar.datePurchased.year;
	while (yearValid(newCar.datePurchased.year) == false)
	{
		cout << "Please enter a valid year in the format YYYY: ";
                cin.clear();
                cin.ignore(100, '\n');
                cin >> newCar.datePurchased.year;
	}
	//input and validate year input

	cout << "Enter Purchase Price: $";
	while (!(cin >> newCar.purchasePrice))
        {
        	cout << "Invalid Price Input, please try again: $";
            	cin.clear();
         	cin.ignore(100, '\n');
      	}
	//input and validate price input

	cout << "Has the car been sold? Enter Y or N: ";
	cin >> sold;	
	while (!(sold == 'Y' || sold == 'y' || sold == 'N' || sold == 'n'))
	//if input is not Y or N ask for reinput
	{ 	
		cout << "Please enter Y or N: ";
		cin.clear();
		cin.ignore(100, '\n');
		cin >> sold;
	}
	
	if (sold == 'Y' || sold == 'y')
	//if Y then set isSold to true and get price and date
	{
		newCar.isSold = true;
		
		cout <<"Enter Day Sold: ";
		cin >> newCar.dateSold.day;
		while(newCar.dateSold.day > 31)
		{
			cout << "Invalid day, please re-input: ";
                	cin.clear();
                	cin.ignore(100, '\n');
                	cin >> newCar.dateSold.day;
		}
		//input and validate day

       		cout <<"Enter Month Sold: ";	
		cin >> newCar.dateSold.month;
		while(newCar.dateSold.month > 12)
                {
                        cout << "Invalid month, please re-input: ";
                        cin.clear();
                        cin.ignore(100, '\n');
                        cin >> newCar.dateSold.month;
                }
		//input and validate month

		while (dayValid(newCar.dateSold.day, newCar.dateSold.month) == false)
        	{
                	cout << "That day is not valid for that month" << endl;
                	cout << "Please re-input day: ";
                	cin.clear();
                	cin.ignore(100, '\n');
                	cin >> newCar.dateSold.day;
                	cout << "Please re-input month: ";
                	cin >> newCar.dateSold.month;
        	}
		//validate month has correct number of days

		
		cout <<"Enter Year Sold: ";
		cin >> newCar.dateSold.year;
		while (yearValid(newCar.dateSold.year)== false)
		{
			cout << "Please input valid year in the form YYYY: ";
                        cin.clear();
                        cin.ignore(100, '\n');
                        cin >> newCar.dateSold.year;
		}
		//input and validate year

		cout <<"Enter Sale Price: $";
		while (!(cin >> newCar.salePrice))
		{
			cout << "Invalid Price Input, please try again: $";
			cin.clear();
			cin.ignore(100, '\n');
		}
		//input and validate price
	}

	else if (sold == 'N' || sold == 'n')
	//if input is N then set isSold to false
	{
		newCar.isSold = false;	
	}
	
	cars.push_back(newCar);
	//add newCar to vector
}
/************************************************************************************************************************************************************************************
 *
 * Entry: This function takes the vactor declared in main and passed by reference
 *
 * Exit: This function outputs the information of all cars on the lot not yet sold
 *
 * Purpose: The purpose of this function is to check if a car has been sold and if it was
 * not then the function will output the information about the car
 *
 *
 * **********************************************************************************************************************************************************************************/
 
void listInventory(vector<Car>& cars)
{
	for (int i = 0; i < cars.size(); i++)
	//for each car
	{
		if (cars[i].isSold == false)
		//if not yet sold, output info
		{
			cout << "Make: " << cars[i].make << endl;
			cout << "Model: " << cars[i].model << endl;
			cout << "Year: " << cars[i].year <<endl;
			cout << "Date Purchased: " << cars[i].datePurchased.month <<"/"<< cars[i].datePurchased.day << "/" << cars[i].datePurchased.year << endl;
			//date prints month/day/year
			cout << "Purchase Price: $" << fixed << setprecision(2) << cars[i].purchasePrice << endl;
			//price to print as dollar and cents
			cout << endl;
		} 
	}
}
/************************************************************************************************************************************************************************************
 *
 * Entry: This function takes the reference to the vector of the struct Car as a parameter
 *
 * Exit: This function will output the total sales, and total purchases in a specific month
 * along with the total profits from said month
 *
 * Purpose: The purpose of this function is to calculate the total profits for a specific
 * month in a specific year based on the total purchases and sales.
 *
 *
 * **********************************************************************************************************************************************************************************/

void monthProfit(vector<Car> &cars)
{
	double totalPurchasePrice = 0.0;
	//variable to hold purchase price for month
	double totalSales = 0.0;
	//variable to hold sales for the month
	double monthProfits;
	//variable to hold total profits for moth
	int mm, yr, i;
	//varibales hold month and year and i = loop variable
	
	cout << "Please enter a year: ";
	cin >> yr;
	//get year input
	while (yearValid(yr) == false)
	{
		cout << "Invalid year, please re-input in format YYYY: ";
                cin.clear();
                cin.ignore(100, '\n');
                cin >> yr;
	}	
	//validate year input

	cout << "Please enter a month in " << yr << ":";
	cin >> mm;
	// get month input

	while (mm > 12 || mm < 1)
	{
		cout << "Invalid month, please re-input: ";
              	cin.clear();
           	cin.ignore(100, '\n');
            	cin >> mm ;
	}
	//validate month input

	for (i = 0; i < cars.size(); i++)
	// for each car if it was purchased or sold that month and year 
        {
        	if (cars[i].datePurchased.year == yr && cars[i].datePurchased.month == mm)
		{		        
			totalPurchasePrice += cars[i].purchasePrice;
			//add cars purchase price to total
		}	
		if (cars[i].isSold == true && cars[i].dateSold.year == yr && cars[i].dateSold.month == mm)
                {
			totalSales += cars[i].salePrice;
			//add cars sales price to total
		}
	}

	cout << "\nTotal Sales for "<<mm<<"/"<<yr<<": $" << fixed << setprecision(2) << totalSales << endl;
	//output total sales
	cout << "\nTotal Purchases for "<<mm<<"/"<<yr<<": $" << fixed << setprecision(2) << totalPurchasePrice << endl;
	//output total purchases
	
	monthProfits = totalSales - totalPurchasePrice;
	//find difference between sales and pruchases
	cout << "Total Profit for "<<mm<<"/"<<yr<<" was: $" << fixed << setprecision(2) << monthProfits << endl;
	//output total profits for the month	
}

/**************************************************************************************************************************************************************
 *
 * Entry: This function will take an integer representng the month and day 
 * and check it to see if the input was valid.
 *
 * Exit: This function will return either true or false based onn whether the
 * input is valid
 *
 * Purpose: The purpose of this function is to check the month and day input to
 * make sure it's valid
 *
 * ***********************************************************************************************************************************************************/

bool dayValid(int day, int month)
{
	if (month > 12 || month < 1)
	//if month is not between 1 and 12 return false
	{
		return false;
	}

	if(month == 1 || month == 3 || month == 5 || month == 7 || month == 8 || month == 10 || month == 12)
	//if month is 1,3,5,7,8,10,12 and day input is not between 1 and 31 return false
	{
	 	if (day < 1 || day > 31)
		{
			return false;
		}
	}

	else if(month == 4 || month == 6 || month == 9 || month == 11)
	//if month is 4,6,9 or 11 and day input is not between 1 and 30 return false
	{
		if (day < 1 || day > 30)
		{
			return false;
		}
	}
	else if (month == 2)
	//if month input is 2 and day input is not between 1 and 28 return false
	{
		 if (day < 1 || day > 28)
                {
                        return false;
                }
	}
		
return true;
//return true
}

/**************************************************************************************************************************************************************
 *
 * Entry: This function will take an integer representing the year
 *
 * Exit: This function will return either true or false based on whether the
 * input is valid
 *
 * Purpose: The prupose of this function to make sure the year input by the 
 * user is valid 1908 represents the ford model T and 2015 is current models
 *
 * ************************************************************************************************************************************************************/

bool yearValid(int year)
{
	if (year < 1908 || year > 2015)
	//check if year input is bettween first car 1908 and today 2015
		return false;
return true;
}

