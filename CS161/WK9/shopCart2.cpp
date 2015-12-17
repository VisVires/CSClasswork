/*************************************************************************************************************************************************************************************
 * Author: William George
 * Date Created: 11/27/2014
 * Date Last Modified: 11/30/2014
 * File Name: shopCart2.cpp
 *    
 *	Overview: This purpose of this program is to build a class that will represent a
 *    	shopping cart and a class that will be called item. The program will display a 
 *    	menu where users can add items with the price, name and quantity to the shopping 
 *    	cart object and it will display the items currently in the cart, it will also give
 *    	the user a choice to see the total price of the items in the cart. 
 *        
 *    	Input: The program will take a couple inputs, first it will take the users choice 
 *    	as an input. They will first be allowed to input their choice, then if the user 
 *    	selects add item the user will be allowed to input the name, price and quatity 
 *    	for the new item.
 *
 *  	Output: The program will first output a menu then depending on the user's choice 
 *  	will output a prompt to add name, price and quantity of an item or it will output 
 *  	a list of the contents of the cart or it will output the total price of the cart.
 *               
 *********************************************************************************************************************************************************************************/

#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>
#include <iomanip>

using namespace std;

bool isNum(string num);
void displayMenu();
int getChoice();

class Item
{
	private:
	//member variables
		string name;	//item name variable
		double price;	//item price variable
		int quantity;	//item quantity variable
	public: 
		//member functions
		//default constructor with arguments
		Item(string n = " ", double p = 0.0, int q = 0)
		{
			name = n;
			price = p;
			quantity = q;
		}
		//default destructor
		~Item(){}
		
		//name accessor and mutator
		void setName (const string n)
		{	name = n;	}	
		string getName()
		{	return name;	}

		//set accessor and mutator
		void setPrice(const double p)
		{	price = p;	}
		double getPrice()
		{	return price;	}

		//quantity accessor and mutator
		void setQuantity(const int q)
		{	quantity = q;	}
		int getQuantity()
		{	return quantity;	}
		
};

//shopping cart class
class ShoppingCart
{
	private:
		//member variable
		vector<Item> shoppingCart; //vector of Items
	public:
		//default constructor
		ShoppingCart(){};
		//shopping cart constructor with empty vector
		ShoppingCart(vector<Item> item)
		{
		}

		//shopping cart accessor
		vector<Item> getShoppingCart()	
		{	return shoppingCart;	}

		//prototype functions
		void addItem(vector <Item> &shoppingCart);
		void listItems(vector <Item> &shoppingCart);
		double totalPrice(vector <Item> &shoppingCart);
};

/************************************************************************************************************************************************************************************
 *	This function will read the users inputs and store them in the empty vector
 *
 * **********************************************************************************************************************************************************************************/

void ShoppingCart::addItem(vector <Item> &shoppingCart)
{
	string itemQuantity;		//string to check validity item quantity
	Item newItem;			//item class object 
	string name;			//holds item name
	double price;			//holds item price
	int quantity;			//holds item quantity
	
      	cout << "\nEnter item name: ";
    	cin >> name; 
	//set name as item name
	newItem.setName(name);
  	
	cout << "Enter item price: $";
	//validate price input
  	while (!(cin >> price))
	{
		cout << "Invalid Price, please re-input: $";
       		cin.clear();
     		cin.ignore(100, '\n');
	}
	//set price as item price
	newItem.setPrice(price);
	
	cout << "Enter item quantity: ";
      	cin >> itemQuantity;
	//validate item input using isNum function
     	while (isNum(itemQuantity) == false)
	{
		cout << "Invalid Quantity, please re-input: ";
          	cin.clear();
         	cin.ignore(100, '\n');
            	cin >> itemQuantity;
	}
	
	//change item input to int	
	quantity = atoi(itemQuantity.c_str());
	//set quantity as item quantity
	newItem.setQuantity(quantity);
	//add item to vector
	shoppingCart.push_back(newItem);
}
/******************************************************************************************
 *	This function will list the items currently in the shopping cart vector
 *
 *****************************************************************************************/

void ShoppingCart::listItems(vector <Item> &cart)
{
	//for each item in cart display name, price and quantity	
	for (int i = 0; i < cart.size(); i++)
	{
 		cout << "Item name: " << cart[i].getName() << endl;
                cout << "Price: $" << fixed << setprecision(2) << cart[i].getPrice() << endl;
                cout << "Quantity: " << cart[i].getQuantity() << "\n\n";
	}
}

/******************************************************************************************
 *	This function will use the price and quantity for each item in the cart to 
 *	calculate the total price for the cart.
 *
i * ***************************************************************************************/

double ShoppingCart::totalPrice(vector <Item> &cart)
{
	double tPrice = 0;	//total price counter
	double itemPrice = 0;	//gets item price as product of price and quantity

	//for each item mutliply price by quantity and add to total price
	for (int index = 0; index < cart.size(); index++)
	{
	       	itemPrice = cart[index].getPrice() * cart[index].getQuantity();
                tPrice += itemPrice;
        }
	
	//return total price
	return tPrice;
}



///main function
int main()
{
	ShoppingCart cart;              //define shopping cart  object
        vector <Item> sCart; 		//vector of items shopping cart
        int choice;			//holds user choice
        char ch;			//character to pause program
        double tPrice = 0.00;		//holds total price

	 do
        //loop until user selects 4 for quit
        {
        	displayMenu();  //call displayMenu function
        	choice = getChoice();   //set user choice to choice
        
                //actions for user choice
  		switch(choice)
                {

                                //call add item function
                        case 1: cart.addItem(sCart);
                                cout << "Press enter to continue" << endl;
                                //wait for user to press enter
                                cin.get(ch);
                                cin.get(ch);
                                break;
                                
				//call function to list items in cart
			case 2:	cart.listItems(sCart);
                                cout << "Press enter to continue" << endl;
                                //wait for user to input enter
                                cin.get(ch);
                                cin.get(ch);
                                break;
                               
				//call function to check total price of cart
                                //set total price variable
			case 3: tPrice = cart.totalPrice(sCart);
                                cout << "The total price of the items in the cart is: $" << fixed << setprecision(2) << tPrice << endl;
                                cout << "Press enter to continue";

                                //wait for user to press enter
                                cin.get(ch);
                                cin.get(ch);
                                break;
			case 4: cout <<"Thank you for shopping" << endl;
		}

	}
	//leave loop
	while (choice != 4);

return 0;
}

/************************************************************************************************************************************************************************************
 *
 *	Entry: No entry conditions
 *
 * 	Exit: This function prints the menu options for the user
 *
 *	Purpose: This function prints the menu options for the user
 *
 * **********************************************************************************************************************************************************************************/

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
 *	Entry : No entry conditions
 *
 *	Exit: This function returns a number input by the user
 *
 *	Purpose: The purpose of this function is to take and validate the number input by
 *	the user.
 *
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
 *	Entry: This function takes a number input by the user as string
 *
 *	Exit: This function returns either true or false if the number is valid
 *
 *	Purpose: This function checks if an input is numeric and returns true if so.
 *
 * **********************************************************************************************************************************************************************************/

bool isNum(string numInput)
{
	//for each digit check if numeric
       for(int i=0; i < numInput.length(); i++)
       {
               if(!(numInput.at(i) >= '0' && numInput.at(i) <= '9'))
               return false;
       }
       return true;
}

