/*************************************************************************************************************************************************************************************
 * 
 * Author: William George
 * Date Created: 11/28/2014
 * Date Last Modified: 11/30/2014
 * File Name: carLot2.cpp
 *
 * Overview: This program allows a user to enter information for a new car on a car lot.
 * including info about the make, model, year, purchase price, and pruchase date. Also if
 * car has been sold the user can enter the sale date and price. The program then gives the
 * user the opportunity to see what cars have not been sold and to find the total profit
 * from sales in a specific month.
 *
 * Inputs: The user will have the chance to input a choice for menu options, then the user
 * can enter the information about a car purchased. 
 *
 * Output: This program will first output a menu from which a user can choose. Then based
 * on the input the user can either look at the contents of the lot or see the profits for
 * a specific month the user chooses.
 *
 * **********************************************************************************************************************************************************************************/

#include <iostream>
#include <string>
#include <cstdlib>
#include <vector>
#include <math.h>
#include <iomanip>

using namespace std;

//prototype functions
void displayMenu();
int getChoice();



//class date
class Date
{
	private:
		int day, month, year;	//hold int for month, day and year
	
	public:
		//default constructor
		Date(){}
		//deconstructor 
		~Date(){}
		//constructor
		void setDate(int d, int m, int y )
		{

			while (y <1900 || y > 2100)
			{
				cout <<"Invalid Year, Please Try Again. Enter Year in Form YYYY: ";
				cin.clear();
				cin.ignore(100, '\n');
				cin >> y;
			}
			while (m > 12 || m < 1)
        		//if month is not between 1 and 12 reinput
        		{
                		cout <<"Invalid Month, Please Try Again. Enter Month: ";
                                cin.clear();
                                cin.ignore(100, '\n');
                                cin >> m;
        		}

        		if(m == 1 || m == 3 || m == 5 || m == 7 || m == 8 || m == 10 || m == 12)
        		//if month is 1,3,5,7,8,10,12 and day input is not between 1 and 31 return false
        		{
                		while (d < 1 || d > 31)
                		{
                        		cout <<"There are not "<< d <<" days in that month, please try again: ";
                                	cin.clear();
                                	cin.ignore(100, '\n');
                                	cin >> d;
                		}
        		}

        		else if(m == 4 || m == 6 || m == 9 || m == 11)
        		//if month is 4,6,9 or 11 and day input is not between 1 and 30 return false
        		{
                		if (d < 1 || d > 30)
                		{
                        		cout <<"There are not "<< d <<" days in that month, please try again: ";
                                        cin.clear();
                                        cin.ignore(100, '\n');
                                        cin >> d;
	
                		}
        		}
        		else if (m == 2)
        		//if month input is 2 and day input is not between 1 and 28 return false
        		{
                		while(d < 1 || d > 28)
                		{
					cout <<"There are not "<< d <<" days in that month, please try again: ";
                                        cin.clear();
                                        cin.ignore(100, '\n');
                                        cin >> d;                        		
                		}
        		}

			day = d;
			month = m;
			year = y;
		}

		//day accessor
		int getDay() const
		{return day;}

		//month accessor
		int getMonth() const
		{return month;}

		//year accessor
		int getYear() const
		{return year;}
};



class Car
{
	private:
		string make;		//car make
		string model;		//car model
		int year;		//car year
		Date datePurchased;	//date car was purchased
		double purchasePrice;	//price car was purchased for
		bool isSold;		//is car sold?
		Date dateSold;		//date car was sold
		double salePrice;	// car sale price

	public:
		Car(){};
		//default constructor wiith dateSold and salePrice arguments
		Car(string mak, string mod, int y, Date dP,  double pP, bool sold, Date dS, double sP)
		{
			make = mak;
			model = mod;
			year = y;
			datePurchased = dP;
			purchasePrice = pP;
			isSold = sold;
			dateSold = dS;
			salePrice = sP;
		}	
		
		//default deconstructor
		~Car(){}
		
		//default constructor without dateSold and salePrice arguments
		Car(string mak, string mod, int y, Date dP, double pP, bool sold)
                {
                        make = mak;
                        model = mod;
                        year = y;
                        datePurchased = dP;
                        purchasePrice = pP;
                        isSold = sold;
                }
		
		//make accessor and mutator
		void setMake(string m)
		{	make = m;	}
		string getMake()
		{return make;}
	
		//model accessor and mutator
		void setModel(string m)
                {	model = m;	}
		string getModel()
                {return model;}
	
		//year accessor and mutator
		void setYearBuilt(int y)
		{	year = y;	}
		int getYearBuilt()
		{return year;}

		//date pruchased accessor and mutator
		void setDatePurchased(int d, int m, int y)
		{	
			datePurchased.setDate(d,m,y);
		}
		Date getDatePurchased()
		{
			datePurchased.getDay();
			datePurchased.getMonth();
			datePurchased.getYear();
			return datePurchased;	
		}

		//purchase price accessor and mutator
		void setPurchasePrice(double pP)
		{	purchasePrice = pP;	}
		double getPurchasePrice()
		{return purchasePrice;}

		//isSold mutator and accessor
		void setIsSold(bool sold)
		{	isSold = sold;	}
		bool getIsSold()
		{return isSold;}

		//date sold accessor and mutator
		void setDateSold(int d, int m, int y)
		{
			dateSold.setDate(d,m,y);
		}
		Date getDateSold()
		{
           		dateSold.getDay();
                	dateSold.getMonth();
                   	dateSold.getYear();
			return dateSold;
		}

		//sale price accessor and mutator
		void setSalePrice(double sale)
		{	salePrice = sale;	}
		double getSalePrice()
		{return salePrice;}
	
		//get profits prototype
		double getProfits();
};	


class CarLot
{
	private:
		vector<Car> carLot;		//carLot vector

	public:
		//constructors
		CarLot(){};		
		CarLot(vector<Car> lot)	
		{carLot = lot;}

		//destructor
		~CarLot(){}

		//accessor for carLot vector
		vector <Car> getCarLot()
		{return carLot;}
		
		//function prototypes
		void addCar(vector<Car> &lot);
		int listCurrentInv(vector<Car> &lot);
		double getMonthProfit(vector<Car> &lot);
};
/*************************************************************************************************************************************************************************************
 *	This function finds the profits for an individual car
 *
 ****************************************************************************************** ****************************************************************************************/

double Car::getProfits()
{
	double profits;			//holds profits variable
	profits = getSalePrice() - getPurchasePrice();
	return profits;
}

/************************************************************************************************************************************************************************************
 *	This function adds a car to the vector car lot.	
 *
 * **********************************************************************************************************************************************************************************/

void CarLot::addCar(vector<Car> &lot)
{
	Car newCar;						//create newCar object
	string make;						//holds car make
	string model;						//holds car model
	int year, dayP, dayS, monthP, monthS, yearP, yearS;	//holds date info
	double priceP, priceS;					//price sold and pruchased
	bool isSold;						//is car sold
	char sold;						//holds user input for isSold
	
	//sets car make
	cout << "Enter Make: ";
        cin >> make;
	newCar.setMake(make);

	//sets car model
	cout << "Enter Model: ";
        cin >> model;
	newCar.setModel(model);

	//sets car year
	cout << "Enter Year: ";
        cin >> year;
	while (year < 1908 || year > 2015)
	{
		cout << "Invalid Year Please Reinput Year YYYY: ";
		cin.clear();
		cin.ignore(100, '\n');
		cin >> year;
	}
	newCar.setYearBuilt(year);

	//sets purchase date
	cout << "Enter Day Purchased: ";
        cin >> dayP;
	cout << "Enter Month Purchased: ";
        cin >> monthP;
	cout << "Enter Year Purchased: ";
        cin >> yearP;
	newCar.setDatePurchased(dayP, monthP, yearP);

	//sets and validates purchase price
	cout << "Enter Purchase Price: $";
        while (!(cin >> priceP))
	{
		cout << "Invalid Price Input, please try again: $";
                cin.clear();
                cin.ignore(100, '\n');
	}
	newCar.setPurchasePrice(priceP);

	//validates variable sold as y or n
	cout << "Has the car been sold? Enter Y or N: ";
        cin >> sold;
        while (!(sold == 'Y' || sold == 'y' || sold == 'N' || sold == 'n'))
	 {
                cout << "Please enter Y or N: ";
                cin.clear();
                cin.ignore(100, '\n');
                cin >> sold;
        }

	//if sold is Y or y set as true and get dateSold and sale price
        if (sold == 'Y' || sold == 'y')
	{
                //sets isSold as true
		isSold = true;
		newCar.setIsSold(isSold);

		//sets date sold
                cout <<"Enter Day Sold: ";
                cin >> dayS; 
	 	cout <<"Enter Month Sold: ";
                cin >> monthS;
		cout <<"Enter Year Sold: ";
                cin >> yearS;
		newCar.setDateSold(dayS, monthS, yearS);	

		//sets and validates sale price
		cout <<"Enter Sale Price: $";
      		while (!(cin >> priceS))
      		{
        		cout << "Invalid Price Input, please try again: $";
            		cin.clear();
      			cin.ignore(100, '\n');
   		}
		newCar.setSalePrice(priceS);
	}
	
	//if sold is n or N set isSold as false
	else if (sold == 'N' || sold == 'n')
	{
                isSold = false;
		newCar.setIsSold(isSold);
        }
	
	//add car to vector
        lot.push_back(newCar);	      
     	
}

/************************************************************************************************************************************************************************************
 *
 *	This function lists the current inventory in the car lot based on whether the car
 *	is sold
 *
 * **********************************************************************************************************************************************************************************/

int CarLot::listCurrentInv(vector<Car> &lot)
{
	Date datePurchased;		//date object
	int carsInLot = 0;		//counter for cars in the lot		

	//for each car output make, model, year
	for (int i = 0; i < lot.size(); i++)
	{
		//if car is not sold output make, model, year and purchase date
		if (lot[i].getIsSold() == false)
		{
			carsInLot++;	//increment carsInLot counter
			datePurchased = lot[i].getDatePurchased();
			cout << "Make: " << lot[i].getMake() << endl;
                        cout << "Model: " << lot[i].getModel() << endl;
                        cout << "Year: " << lot[i].getYearBuilt() <<endl;
                   	cout << "Date Purchased: " << datePurchased.getMonth() <<"/"<< datePurchased.getDay()<<"/"<< datePurchased.getYear()<< endl;
			cout << "Purchase Price: $" << fixed << setprecision(2) << lot[i].getPurchasePrice() << endl;
			cout << endl;
		}
	}

	return carsInLot;
}

/************************************************************************************************************************************************************************************
 *
 *	This function outputs the months profits and the cars sold during the month
 * 
 * *********************************************************************************************************************************************************************************/

double CarLot::getMonthProfit(vector<Car> &lot)
{

	Date purchaseDate;			//date object for purchase date
	Date saleDate;				//date object for sale date
	double totalPurchasePrice = 0.0;	//total purchase price
	double totalSales = 0.0;		//total sale price
	double monthProfits;			//profits for month
	int mm, yr;				//month year input
	int i;					//loop variable
	int counter = 0;			//counts number of cars sold



	cout << "Please enter a year: ";
        cin >> yr;
	//validate year input
	while (yr < 1908 || yr > 2015)
        {
                cout << "Invalid Year Please Reinput Year YYYY: ";
                cin.clear();
                cin.ignore(100, '\n');
                cin >> yr;
        }




	cout << "Please enter a month in " << yr << ": ";
        cin >> mm;
	//validates month input
	while (mm > 12 || mm < 1)
        {
                cout << "Invalid month, please re-input: ";
                cin.clear();
                cin.ignore(100, '\n');
                cin >> mm ;
        }




	//for each car get purchase and sale price and add to total sales and purchases
	for (i = 0; i < lot.size(); i++)
	{
		purchaseDate = lot[i].getDatePurchased();
		saleDate = lot[i].getDateSold();
                if (purchaseDate.getYear() == yr && purchaseDate.getMonth() == mm)
                {
                        totalPurchasePrice += lot[i].getPurchasePrice();
		 }
                if (lot[i].getIsSold() == true && saleDate.getYear() == yr && saleDate.getMonth() == mm)
                {
			counter++;
                        totalSales += lot[i].getSalePrice();
		}
        }




	cout << "\nTotal Sales for "<<mm<<"/"<<yr<<": $" << fixed << setprecision(2) << totalSales << endl;
	cout << "Total Purchases for "<<mm<<"/"<<yr<<": $" << fixed << setprecision(2) << totalPurchasePrice << endl;

	//finds and outputs difference between total sales and purchases
	monthProfits = totalSales - totalPurchasePrice;
	cout << "\nTotal Profit for "<<mm<<"/"<<yr<<" was: $" << fixed << setprecision(2) << monthProfits << "\n\n\n" ;




	//if a car was sold output each car and profits from each car 
	if (counter != 0)
	{
		cout << "\n\nThe following cars were sold:"<< endl; 
		for (i = 0; i < lot.size(); i++)
        	{
                	saleDate = lot[i].getDateSold();
                	if (lot[i].getIsSold() == true && saleDate.getYear() == yr && saleDate.getMonth() == mm)
                	{
                	        cout << lot[i].getYearBuilt() << " " << lot[i].getMake() << " " << lot[i].getModel() << endl;
				cout << "Profits: $" << fixed << setprecision(2) << lot[i].getProfits() << "\n\n";
                	}
        	}
	}

}



//main program
int main()
{
	CarLot lot;		//car lot object
	vector<Car> carLot;	//car lot vector
	int choice;		//gets user choice
	char ch;		//character for cin.get input
	int carsInLot;		//variable to hold number of cars currently in the lot	

	do
	{
		//display menu
		displayMenu();
		//calls get choice and gets user choice
		choice = getChoice();

		switch(choice)
		{		//call add car function	
			case 1: lot.addCar(carLot);
				cout << "Press enter to return to menu" << endl;
                                cin.get(ch);
                                cin.get(ch);
				break;
				
				//call current inventory function
			case 2: carsInLot = lot.listCurrentInv(carLot);
				cout << "Currently there are "<<carsInLot<< " cars in the lot" <<endl;
				cout << "Press enter to return to menu" << endl;
                                cin.get(ch);
                                cin.get(ch);
				break;
			
				//call get profit function
			case 3: lot.getMonthProfit(carLot);
				cout << "Press enter to return to menu" << endl;
                                cin.get(ch);
                                cin.get(ch);
				break;
	
			case 4: cout << "Thank you, Good-Bye" << endl;
		}
	}
	//exit loop
	while (choice != 4);

	
return 0;
}
/************************************************************************************************************************************************************************************
 *
 *	Entry: No entry
 *
 *	Exit: This function outputs a menu
 *
 *	Purpose: The purpose of this function is to output a menu of choices for a user
 *
 * *********************************************************************************************************************************************************************************/

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
 *	Entry: No entry
 *
 * 	Exit: This function returns the users input
 *
 * 	Purpose: The purpose of this function is to validate and return a users input
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



