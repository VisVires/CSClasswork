/************************************************************************************************************************************************************************************
 *
 * Author: William George
 * Date Created: 11/20/2014
 * Date Last Modified: 11/23/2014
 * File Name: shopCart.cpp
 *
 * Overview: This purpose of this program is to build a struct that will represent a
 * shopping cart. The program will display a meny where users can add items with their 
 * price, name and quantity and it will display the items currently in the cart.
 *
 * Input: The program will take a couple inputs, first it will take the users choice as an
 * input. They will first be allowed to input their choice, then if the user selects add
 * item the user will be allowed to input the name, price and quatity for the new item.
 *
 * Output: The program will first output a menu then depending on the user's choice will 
 * output a prompt to add name, price and quantity of an item or it will output a list of
 * the contents of the cart or it will output the total price of the cart.
 *
 *
 * *********************************************************************************************************************************************************************************/

#include <iostream>
#include <string>
#include <cstdlib>
#include <iomanip>
//preprocess directives
using namespace std;

struct Item
{
	string name;	//item name
	double price;	//item price
	int quantity;	//item quantity
};

void displayMenu();	//function to display menu
int getChoice();	//function to validate and return user choice
int addItem(Item *cart, int totalItems);//function to add items to shopping cart array
void list(Item *cart, int totalItems);	//function to list contents of shopping cart
double totalPrice(Item *cart, int totalItems);	//function to display total price of shopping cart contents
bool isNum(string num);

int main()
{

	Item item;		//define structure variable
	const int SIZE = 100;	//set max size of array to 100
	struct Item shoppingCart [SIZE]; //array of item shopping cart
	int choice;
	int totalItems = 0;
	char ch;
	double tPrice = 0.00;

	do
	//loop until user selects 4 for quit
	{
		displayMenu();	//call displayMenuu function
		choice = getChoice();	//set user choice to choice
	
	
		switch(choice)
		//actions for user choice
		{
			case 1: totalItems = addItem(shoppingCart, totalItems);
				// call add item function and set total
				cout << "Press enter to continue" << endl;
				cin.get(ch);
				cin.get(ch);
				//wait for user to press enter
				break;

			case 2: list(shoppingCart, totalItems);
				//call function to list items in cart
				cout << "Press enter to continue" << endl;
				cin.get(ch);
				cin.get(ch);
				//wait for user to input enter
				break;

			case 3: tPrice = totalPrice(shoppingCart, totalItems);
				// call function to check total price of cart
				// set total price variable
				cout << "The total price of the items in the cart is: $" << fixed << setprecision(2) << tPrice << endl;
				cout << "Press enter to continue";
				cin.get(ch);
				cin.get(ch);
				//wait for user to press enter
				break;

			case 4: cout <<"Thank you for shopping! Good-Bye" << endl;
			//good-bye message
		}
	}
	while (choice != 4);
	//leave loop
return 0;
}

/**************************************************************************************************************************************************************
 *
 * Entry: No Entry
 *
 * Exit: This function will output a menu of options from which the user can
 * choose
 *
 * Purpose: The purpose of this function is to output a menu for a user to
 * choose whether they would like to add an item, list items or get a total 
 * price
 *
 * ***********************************************************************************************************************************************************/

void displayMenu()
{
	system("clear");
	//clear screen
	cout << "Shopping Cart Menu:\n\n";
	cout << "Please select a number" << endl;	
	cout << "1: Add Item to Cart" << endl;
	cout << "2: List Cart Contents" << endl;
	cout << "3: See Total Price of Cart" <<endl;
	cout << "4: Quit" << endl << endl;
}

/************************************************************************************************************************************************************************************
 *
 * Entry: No entry
 *
 * Exit: Output is an integer based off of the users selection
 *
 * Purpose: The purpose of this function is to get the users choice then validate it.
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

/************************************************************************************************************************************************************************************
 *
 * Entry: This function takes a pointer to the array of the structure of the shopping cart
 *
 * Exit: This function then returns the updated shoppingCart and an int of the total
 * items in the cart
 *
 * Putpose: The purpose of this function is to add an item name along with it's price and
 * quantity to the shoppingCart array
 *
 * **********************************************************************************************************************************************************************************/
int addItem(Item *cart, int totalItems)
{	
	string num;
	//variable to hold user input
	int numItems;
	//int for number of items added
	string itemQuantity;
	//string to check user input for quantity

	cout <<"How many items would you like to add to the cart? "<< endl;
	cin >> num;
	
	while (isNum(num) == false)
	//check if num of items is valid
       	{
                        cout << "Invalid Quantity, please re-input: ";
                        cin.clear();
                        cin.ignore(100, '\n');
                        cin >> itemQuantity;
      	}
	numItems = atoi(num.c_str());
	//change num to integer numItems      	

	for(int i = totalItems; i < (totalItems + numItems); i++)
	//take user inputs for price and name
      	{
		cout << "\nEnter item name: ";
        	cin >> cart[i].name;
        	cout << "Enter item price: $";
        	while (!(cin >> cart[i].price))
		//validate price input
		{
			cout << "Invalid Price, please re-input: $";
			cin.clear();
			cin.ignore(100, '\n');
		}
        	
		cout << "Enter item quantity: ";
        	cin >> itemQuantity;
		while (isNum(itemQuantity) == false)
		//validate quantity input
		{
			cout << "Invalid Quantity, please re-input: ";
                        cin.clear();
                        cin.ignore(100, '\n');
			cin >> itemQuantity;
		}
		cart[i].quantity = atoi(itemQuantity.c_str());
		//change quantiity to integer and store to array
        }

        totalItems += numItems;
	//add items to total inputs
	return totalItems;
	//return total inputs to main function
}

/************************************************************************************************************************************************************************************
 *
 * Entry: This function takes the value of a specific location of an array item
 *
 * Exit: This function outputs the items name, type and quantity
 *
 * Purpose: This function outputs the structures components at the specified location in
 * the array
 *
 *
 * **********************************************************************************************************************************************************************************/

void list(Item *cart, int totalItems)
{
	for (int i=0; i < totalItems; i++)
	//for each item in array output name, price and quantity
	{
		cout << "Item name: " << cart[i].name << endl;
		cout << "Price: $" << fixed << setprecision(2) << cart[i].price << endl;
		cout << "Quantity: " << cart[i].quantity << "\n\n";
	}
}

/************************************************************************************************************************************************************************************
 *
 * Entry: This function will take the parameters of a pointer to the shopping cart 
 * array and the total items in the cart
 *
 * Exit: This function sends a double back to main with the total price of all items
 * in the shopping cart array 
 *
 * Purpose: The purpose of this function is to take every item in the array and multiply 
 * it by the quantity then add it to the tPrice variable which holds the total price.
 *
 *
 * *********************************************************************************************************************************************************************************/

double totalPrice(Item *cart, int totalItems)
{
	double tPrice = 0;
	//total price variable
	double itemPrice = 0;
	int index;
	//loop variable
	

	for(index = 0; index < totalItems; index++)
	//for each item in loop multiply the price by the quantity and set to item price
	//then add to total price
	{
		itemPrice = cart[index].price * cart[index].quantity;
		tPrice += itemPrice;
	}
	return tPrice;
	//return total price to main function
}

/************************************************************************************************************************************************************************************
 *
 * Entry: This function takes an integer input and checks if it is valid
 *
 * Exit: This function returns either true or false
 *
 * Purpose: This function checks to see if integer input is a valid input
 *
 * *******************************************************************************************************************************************************************************/
 
bool isNum(string numInput)
 {
        for(int i=0; i < numInput.length(); i++)
	//check input for non-number integers and return false if a non-digit is found
        {
                if(!(numInput.at(i) >= '0' && numInput.at(i) <= '9'))
                return false;
        }
        return true;
 }

