#include "creature.h"
#include <string>
#include <iostream>
using std::cout;
using std::cin;
using std::endl;

/***********************************************************************************************************
Purpose: Constructor
************************************************************************************************************/

Creature::Creature(std::string name, int aDiceNum, int dDiceNum, int aNumSides, int dNumSides, int arm, int startingStr, bool goblinAch)
{
    this->name = name;              //creature name
    this->aDiceNum = aDiceNum;      //number of attack dice
    this->dDiceNum = dDiceNum;      //number of defense dice
    this->aNumSides = aNumSides;    //number of sides on attack dice
    this->dNumSides = dNumSides;    //number of sides on defense dice
    this->arm = arm;                //armor
    this->startingStr = startingStr;//starting strength
    this->str = startingStr;        //current strength
    this->goblinAch = false;        //Achilles attacked
}
/************************************************************************************************************

Purpose: Roll dice to get attack total
In: Pointer to defending creature object
Out: Return accumulated dice rolls

************************************************************************************************************/

int Creature::attack(Creature *a)
{
    int diceRolls = 0;                  //counter for dice rolls
    attTotal = 0;                       //accumulator for attack rolls

    //increment dice rolls and accumulate attack total until dice rolls = dice number
    do
    {
        diceRolls++;
        attTotal += rollDice(aNumSides);
        //cout << "Roll " << diceRolls <<" total: " << attTotal << endl;
    }
    while (diceRolls < aDiceNum);

    //if achilles attack inflicted halve attack score
    if (goblinAch)
    {
        attTotal = attTotal/2;
    }

    cout << name << " Attack: " << attTotal << endl;
    //return totals of attack
    return attTotal;
}
/*******************************************************************************

Purpose: Get protected attack total

In: None
Out: Return creature attack

*******************************************************************************/

int Creature::getAttackTotal()
{
    return attTotal;
}

/*******************************************************************************

Purpose: Get character defense total

In: Other Creatures attack total
Out: Returns accumulated defense score

*******************************************************************************/


int Creature::defense(int attTotal)
{
    int diceRolls = 0;          //dice roll accumulator
    defTotal = 0;               //accumulates total of dice rolls

    //roll dice and accumulate total while dice rolls remain
    do
    {
        diceRolls++;
        defTotal += rollDice(dNumSides);
        //cout << "Roll " << diceRolls << " total: " << defTotal << endl;
    }
    while (diceRolls < dDiceNum);

    cout << name << " Defense: " << defTotal << endl;
    //return defense total
    return defTotal;
}

/************************************************************************************************

Purpose: Complete calculations for attacks and defenses for defending creature

In: Takes attacking Creatures attack total
Out: Updates remaining strength for creature

*************************************************************************************************/

void Creature::resolveAttack(int attackTotal)
{
    int damage;                 //variable to hold difference between attack and defense
    int armDamage;              //variable to get damage with armor

    //get damage
    damage = attackTotal - defTotal;
    cout << name <<" Armor: " << arm << endl;

    //get damage with armor
    armDamage = damage - arm;

    //if damage with armor is less than zero than damage is zero
    if (armDamage < 0)
    {
        armDamage = 0;
    }

    cout << "Total Damage: " << armDamage << endl;
    //calculate remaining strength
    str = str - armDamage;
    cout << "Remaining Strength for "<< name << " is: " << str << endl << endl;

}
/***********************************************************************************************

Purpose: Roll dice and return dice rolls

In: Number of sides for creature
Out: Returns random number between 1 and numSides

************************************************************************************************/

int Creature::rollDice(int numSides) const
{
    return (rand() % numSides) + 1;
    //output random num between 1 and numSides
}

/************************************************************************************************

Purpose: Return remaining strength for creature

***********************************************************************************************/

int Creature::getStrength()
{
    return str;
}

/*******************************************************************************

Purpose: Set goblin achillies attack to true

*******************************************************************************/

void Creature::setGoblinAch(bool goblinAch)
{
    this->goblinAch = goblinAch;
}

/*******************************************************************************

Purpose: Return true or false for Goblin Attack, used for testing

*******************************************************************************/

bool Creature::getGoblinAch()
{
    return goblinAch;
}

/********************************************************************************
Purpose: Return name of Barbarian subclass
*********************************************************************************/

std::string Barbarian::getName()
{
    return name;
}

/*******************************************************************************
Purpose: Return name of Reptile People subclass
********************************************************************************/
std::string Reptile::getName()
{
    return name;
}

/*******************************************************************************
Purpose: Return name of Blue Men subclass
*******************************************************************************/

std::string BlueMen::getName()
{
    return name;
}

/*******************************************************************************
Purpose: Return name of Goblin subclass
*******************************************************************************/

std::string Goblin::getName()
{
    return name;
}

/*******************************************************************************

Purpose: Goblin attack function

In: Pointer to defending Creature object
Out: Return attack total

*******************************************************************************/

int Goblin::attack(Creature *a)
{
    int diceRolls = 0;      //dice roll accumulator
    attTotal = 0;           //accumulated total of dice rolls
    bool ach = false;       //boolean to set if achilles attack is executed

    //accumulate dice roll totals until dice total rolled
    do
    {
        diceRolls++;
        attTotal += rollDice(aNumSides);
        //cout << "Roll " << diceRolls <<" total: " << attTotal << endl;
    }
    while (diceRolls < aDiceNum);

    cout << name << " Attack: " << attTotal << endl;

    /*
    * if a 12 is rolled and defending creature is not a goblin
    * and has an achilles set ach attack to true for defending creature
    */
    if (attTotal == 12 &&  a->getName() != "Goblin" && a->getGoblinAch() == false)
    {
            cout << "Achilles Attack!!" << endl;
            ach = true;
            a->setGoblinAch(ach);
    }

    //return attack total
    return attTotal;
}

/*******************************************************************************
Purpose: Return name of Shadow subclass
*******************************************************************************/

std::string Shadow::getName()
{
    return name;
}

/*******************************************************************************

Purpose: Get The Shadow attack total where 50% of attacks are met with the cloak
meaning 50% of attacks are misses

In: Other creatures attack total
Out: Returns The Shadow's defense total which will be 0 50% of the time

*******************************************************************************/

int Shadow::defense(int attTotal)
{
    int diceRolls = 0;              //dice roll acummulator
    defTotal = 0;                   //gets total of defense rolls
    int cloak;                      //holds 2 for cloak capability or 1 for normal defense

    //get cloak number
    cloak = (rand() % 2) + 1;

    /*
    * if cloak = 2 set defense total to equal to attack total to result in
    * zero damage in resolveAttack() function
    */
    if (cloak == 2)
    {
        cout << "YOU MISSED" << endl;
        return defTotal = attTotal;
    }
    //run regular defense roll and accumulate total defense
    else
    {
        do
        {
            diceRolls++;
            defTotal += rollDice(dNumSides);
            //cout << "Roll " << diceRolls << " total: " << defTotal << endl;
        }
        while (diceRolls < dDiceNum);

        cout << name <<" Defense: " << defTotal << endl;
        //return regular attack total
        return defTotal;
    }
}
