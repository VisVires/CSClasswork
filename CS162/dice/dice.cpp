#include <cstdlib>
#include <ctime>
#include "dice.h"

/****************************************************************
Purpose: Default Constructor
*****************************************************************/

Dice::Dice()
//default constructor
{
    numSides = 6;
    srand(time(NULL)); // Seeds random number generator
}

/******************************************************************
Purpose: Constructor
******************************************************************/

Dice::Dice(int numSides)
//constructor
{
    this->numSides = numSides;
    srand(time(NULL)); // Seeds random number generator
}
/*******************************************************************

********************************************************************/
/*
void Dice::setNumSides(int numSides)
{
    this->numSides = numSides;
}
*/
/********************************************************************

Purpose: Find random number between 1 and numSides and store it to dice object

In: None
Out: returns random number between 1 and numSides

********************************************************************/

int Dice::rollDice() const
{
    return (rand() % numSides) + 1;
    //output random num between 1 and numSides
}
/********************************************************************

Purpose: Take two dice rolls and add them together

In: Two int representing dice rolls
Out: returns sum of two dice objects

*********************************************************************/

// Take two dice objects, roll them, and return the sum
int rollTwoDice(const Dice& die1, const Dice& die2)
{
    return die1.rollDice() + die2.rollDice();
    //add two dice
}

/********************************************************************
Purpose: Default Constructor
********************************************************************/

LoadedDice::LoadedDice()
//default constructor
{
    numSides = 6;
    srand(time(NULL)); // Seeds random number generator
}

/*********************************************************************
Purpose: Constructor
*********************************************************************/

LoadedDice::LoadedDice(int numSides)
//constructor
{
    this->numSides = numSides;
    srand(time(NULL)); // Seeds random number generator
}

/*****************************************************************************************

Purpose: Find random number between 1 and numSides and store it to dice object

In: None
Out: Returns int either equaling numSides or random number between 1 and numSides - 1

*********************************************************************************************/

int LoadedDice::rollDice() const
{
    int num = (rand() % 2) + 1;
    //get random number between 1 & 2

    if (num == 1)
    //if num = 1
        return (rand() % (numSides - 1)) + 1;
        //returns random number between 1 and numSides - 1
    else
    //if num = 2
        return numSides;
        //return numSides
}
