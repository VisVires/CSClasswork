#include <iostream>
using std::cout;
using std::cin;
using std::endl;
#include <deque>
#include <string>
#include "room.h"

/*
Constructor
*/
MeatHead::MeatHead()
{
	totGainz = 0;
}

/*******************************************************************************

Purpose: Use Linear Search to search user bag for items acquired during game

In: String representing Utensil to search for in deque
Out: Returns True if utensil is in bag or Retruns false if not in bag

********************************************************************************/
bool MeatHead::searchBag(std::string utensil)
{
	bool inBag = false;					//return variable

	//linear search algorithm
	for (unsigned int i = 0; i < gymBag.size(); i++)
	{
		if (gymBag[i] == utensil)
		{
			inBag = true;
		}
	}

	return inBag;
}

/**********************************************************************************

Purpose: Adds designated utensil to user gym bag, user can only hold 4 utensils 
at a time

In: string representing utensil
Out: Updates deque container holding utensils

***********************************************************************************/
void MeatHead::addToBag(std::string utensil)
{
	if (gymBag.size() == 4)
	{
		cout << "You can't have more than 4 items in your bag at a time, bro" << endl;
		cout << "We've gotta drop your " << gymBag[0] << "." << endl;
		gymBag.pop_front();
	}

	//add item to gym bag and print confirmation
	gymBag.push_back(utensil);
	cout << utensil << " added to gym bag" << endl;
}

/***********************************************************************************

Purpose: Accessor function for deque representing gym bag

***********************************************************************************/
std::deque <std::string> MeatHead::getGymBag()
{
	return gymBag;
}

/**********************************************************************************

Purpose: Gainz accumulator

In: Integer representing either caloric or strength gainz
Out: Updated total of gainz based on input

***********************************************************************************/
void MeatHead::makeGainz(int gainz)
{
	totGainz += gainz;
}

/************************************************************************************

Purpose: Accessor function for gainz variable  

*************************************************************************************/
int MeatHead::getGainz()
{
	return totGainz;
}
