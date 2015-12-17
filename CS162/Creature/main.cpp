/********************************************************************************************************************************
Author: William George
Date Created: 2/10/2015
Date Last Modified: 2/15/2015
Program File: main.cpp

Purpose: This is a test program to test the creature class and see if it's functioning as expected. This program specifically
calls a function to test the Creatures attack() and defense() functions as well as the resolveAttack() function.

In: The user will select the creature they'd like to test and then will choose the opposing creature. The first user will then
select the number of times they'd like the battle to execute.

Out: Based on the first creature and the number of battles selected the user will first get a distribution of all the dice rolls
Next the attacks will execute and the program will output the percentage of attacks each character won.

********************************************************************************************************************************/

#include "creature.cpp"
#include <iostream>
using std::cout;
using std::cin;
using std::endl;

void displayMenu();
int getChoice();
Creature* getCreature(int choice);
void getAttackScoreDist(Creature *, int);
void getDefenseScoreDist(Creature *, int);
void attackSequence(Creature *a, Creature *b);
bool isValidNum(std::string num);

int main()
{
    srand(time(NULL));                  //set random function seed to time
    int choice1, choice2;               //get each choice for creature
    int iterations = 0;                 //loop counter
    std::string ti;                     //get user input for iterations
    int totalIter = 1;                  //validated user input for loop iterations
    int p1Wins = 0, p2Wins = 0;         //accumulators for each player wins
    std::string name1, name2;           //names of each players creature
    char ch;                            //slow program character for get function


    //clear screen get player one choice
    system("clear");
    cout << "Player 1: Choose your Warrior" << endl;
    displayMenu();
    choice1 = getChoice();

    //clear screen get player two choice
    cout << "Player 2: Choose your Warrior" << endl;
    displayMenu();
    choice2 = getChoice();

    //get and validate user input for number of loops
    cout << "How many times would you like to run the simulation? " << endl;
    cin >> ti;
    while(!isValidNum(ti))
    {
        cout << "Please enter a valid number: ";
        cin.clear();
        cin.ignore(100, '\n');
        cin >> ti;
    }
    //convert string input to integer
    totalIter = atoi(ti.c_str());

    //Set creature and get attack() distributions, call test function
    Creature *a;
    a = getCreature(choice1);
    getAttackScoreDist(a, totalIter);

    cin.get(ch);
    cin.get(ch);

    //get defense roll distributions, call test function
    getDefenseScoreDist(a, totalIter);
    cin.get(ch);
    //delete dynamic variable
    delete a;

    /*
    * Loop with player one going first until half of total iterations are done,
    * then run second half of total iterations
    */

    while(iterations != (totalIter/2))
    {
        //iteration accumulator
        iterations++;

        //instatiate creature object for player one
        Creature *a;
        a = getCreature(choice1);
        name1 = a->getName();

        //instatiate creature object for player two
        Creature *b;
        b = getCreature(choice2);
        name2 = b->getName();

        //while strength remaining run attack function
        while(b->getStrength() > 0 && a->getStrength() > 0)
        {
            system("clear");
            cout << "Running Game" << endl;
            attackSequence(a, b);

            //if player 2 has less than one strength remaining player 1 wins
            if (b->getStrength() < 1)
            {
                p1Wins++;
                break;
            }

            attackSequence(b,a);

            //if player 1 has less than one strength remaining player 2 wins
            if (a->getStrength() < 1)
            {
                p2Wins++;
                break;
            }
            //wait for user input
            //cout << "\n Press Enter " << endl;
            //cin.get(ch);
        }
        //delete dynamic Creature objects from heap
        delete a;
        delete b;
    }
    //loop for second half of attacks where player 2 starts
    while(iterations != totalIter)
    {
        iterations++;

        Creature *a;
        a = getCreature(choice1);
        name1 = a->getName();

        Creature *b;
        b = getCreature(choice2);
        name2 = b->getName();

        while(b->getStrength() > 0 && a->getStrength() > 0)
        {
            system("clear");
            cout << "Running Game" << endl;
            attackSequence(b, a);

            if (a->getStrength() < 1)
            {
                p2Wins++;
                break;
            }
            attackSequence(a, b);

            if (b->getStrength() < 1)
            {
                p1Wins++;
                break;
            }
            //cin.get(ch);
        }
        delete a;
        delete b;
    }

    //output Player wins
    cout << "Player One Wins: " << p1Wins << endl;
    cout << "Player Two Wins: " << p2Wins << endl;

    //get percentage of player wins
    double p1Percent = ((float)p1Wins/(float)totalIter);
    double p2Percent = ((float)p2Wins/(float)totalIter);

    //output percentage of wins for each character
    cout << name1 << " wins " <<  p1Percent * 100 << "% percent of the time." << endl;
    cout << name2 << " wins " <<  p2Percent * 100 << "% percent of the time." << endl;

    return 0;
}

/********************************************************************************************

Purpose: Display menu for user choice

In: None
Out: Outputs Menu on Display

*********************************************************************************************/

void displayMenu()
{
        cout << "\nPlease select a number" << endl;
        cout << "1: GOBLIN" << endl;
        cout << "2: BARBARIAN"<< endl;
        cout << "3: REPTILE PEOPLE" << endl;
        cout << "4: BLUE MEN" << endl;
        cout << "5: THE SHADOW" << endl;
        cout << endl << endl;
}

/*********************************************************************************************

Purpose: Get and validate user choice
In: None
Out: Output int representing validated user choice

**********************************************************************************************/

int getChoice()
{
        std::string num;
        bool valid = false;
        int choice;

        cin >> num;
        while (!valid)
        {
            valid = true;
            //check if all number in string are between 1 and 5
            for(int i = 0; i < num.length(); i++)
            {
                if(!(num.at(i) >= '1' && num.at(i) <= '5'))
                {
                    cout << "Please enter a valid choice between 1 and 5: ";
                    cin.clear();
                    cin.ignore(100, '\n');
                    valid = false;
                    cin >> num;
                }
            }
        }
        //change string to integer
        choice = atoi(num.c_str());

        return choice;
        //return int to main
}

/*******************************************************************************

Purpose: Set Creature pointer to user choice

In: User choice integer
Out: Return pointer to user selected Creature Object

*******************************************************************************/

Creature *getCreature(int choice)
{
    //clear screen
    system("clear");
    //set creature pointer
    Creature *a;
    //set pointer to user choice of Creature
    switch (choice)
    {
        case 1: a = new Goblin;
                break;
        case 2: a = new Barbarian;
                break;
        case 3: a = new Reptile;
                break;
        case 4: a = new BlueMen;
                break;
        case 5: a = new Shadow;
    }
    return a;
}
/*******************************************************************************

Purpose: Test function for Creature attack roll distribution

In: Get pointer to Creature object and user inputted total attack iterations
Out: Output attack roll total distribution

*******************************************************************************/

void getAttackScoreDist(Creature *a, int tIter)
{
    int iter = 0;           //accumulator for iterations
    //accumulators for each attack total
    int one = 0;
    int two = 0;
    int three = 0;
    int four = 0;
    int five = 0;
    int six = 0;
    int seven = 0;
    int eight = 0;
    int nine = 0;
    int ten = 0;
    int eleven = 0;
    int twelve = 0;
    int thirteen = 0;
    int fourteen = 0;
    int fifeteen = 0;
    int sixteen = 0;
    int seventeen = 0;
    int eighteen = 0;
    int nineteen = 0;
    int twenty = 0;

   while (iter != tIter)
   {
       //get attack total
        int attack = a->attack(a);

        //set to accumulator
        switch (attack)
        {
            case 1: one++;
                    break;
            case 2: two++;
                    break;
            case 3: three++;
                    break;
            case 4: four++;
                    break;
            case 5: five++;
                    break;
            case 6: six++;
                    break;
            case 7: seven++;
                    break;
            case 8: eight++;
                    break;
            case 9: nine++;
                    break;
            case 10:ten++;
                    break;
            case 11:eleven++;
                    break;
            case 12:twelve++;
                    break;
            case 13: thirteen++;
                    break;
            case 14: fourteen++;
                    break;
            case 15: fifeteen++;
                    break;
            case 16: sixteen++;
                    break;
            case 17: seventeen++;
                    break;
            case 18: eighteen++;
                    break;
            case 19: nineteen++;
                    break;
            case 20: twenty++;
                    break;
        }
        iter++;
    }
        //clear screen and output results
        system("clear");
        cout << "Player One Attack Score Distribution" << endl;
        cout << "1: " << one << endl;
        cout << "2: " << two << endl;
        cout << "3: " << three << endl;
        cout << "4: " << four << endl;
        cout << "5: " << five << endl;
        cout << "6: " << six << endl;
        cout << "7: " << seven << endl;
        cout << "8: " << eight << endl;
        cout << "9: " << nine << endl;
        cout << "10: " << ten << endl;
        cout << "11: " << eleven << endl;
        cout << "12: " << twelve << endl;
        cout << "13: " << thirteen << endl;
        cout << "14: " << fourteen << endl;
        cout << "15: " << fifeteen << endl;
        cout << "16: " << sixteen << endl;
        cout << "17: " << seventeen << endl;
        cout << "18: " << eighteen << endl;
        cout << "19: " << nineteen << endl;
        cout << "20: " << twenty << endl;
}
/*******************************************************************************

Purpose: Test function for Creature defense roll distribution

In: Get pointer to Creature object and user inputted total attack iterations
Out: Output defense roll total distribution and total of attack hits for Shadow
Creature
*******************************************************************************/

void getDefenseScoreDist(Creature *a, int tIter)
{
    int iter = 0;               //total defense function iterations
    int total = 0;              //accumulator for total hits
    //accumulators for each possible defense total
    int one = 0;
    int two = 0;
    int three = 0;
    int four = 0;
    int five = 0;
    int six = 0;
    int seven = 0;
    int eight = 0;
    int nine = 0;
    int ten = 0;
    int eleven = 0;
    int twelve = 0;
    int thirteen = 0;
    int fourteen = 0;
    int fifeteen = 0;
    int sixteen = 0;
    int seventeen = 0;
    int eighteen = 0;

   while (iter != tIter)
   {
        //get defense total using 0 as attack total
        int defense = a->defense(0);
        //if defense is not zero accumulate hits
        if (defense != 0)
            total++;

        switch (defense)
        {
            case 1: one++;
                    break;
            case 2: two++;
                    break;
            case 3: three++;
                    break;
            case 4: four++;
                    break;
            case 5: five++;
                    break;
            case 6: six++;
                    break;
            case 7: seven++;
                    break;
            case 8: eight++;
                    break;
            case 9: nine++;
                    break;
            case 10:ten++;
                    break;
            case 11:eleven++;
                    break;
            case 12:twelve++;
                    break;
            case 13: thirteen++;
                    break;
            case 14: fourteen++;
                    break;
            case 15: fifeteen++;
                    break;
            case 16: sixteen++;
                    break;
            case 17: seventeen++;
                    break;
            case 18: eighteen++;
                    break;
        }
        iter++;
    }
        //clear screen
        system("clear");
        //output results
        cout << "Player One Defense Score Distribution" << endl;
        cout << "1: " << one << endl;
        cout << "2: " << two << endl;
        cout << "3: " << three << endl;
        cout << "4: " << four << endl;
        cout << "5: " << five << endl;
        cout << "6: " << six << endl;
        cout << "7: " << seven << endl;
        cout << "8: " << eight << endl;
        cout << "9: " << nine << endl;
        cout << "10: " << ten << endl;
        cout << "11: " << eleven << endl;
        cout << "12: " << twelve << endl;
        cout << "13: " << thirteen << endl;
        cout << "14: " << fourteen << endl;
        cout << "15: " << fifeteen << endl;
        cout << "16: " << sixteen << endl;
        cout << "17: " << seventeen << endl;
        cout << "18: " << eighteen << endl;
        //output total hits
        cout << total << " / " << iter << " hits" << endl;
}
/*******************************************************************************

Purpose: Run attack and defense functions for each creature and change creature
strength

In: Pointers to each creature
Out: Change defending characters strength attribute

*******************************************************************************/

void attackSequence(Creature *a, Creature *b)
{
        //attack Creature b object
        a->attack(b);
        //defend using creature attack total
        b->defense(a->getAttackTotal());
        //complete attack and alter defender strength variable
        b->resolveAttack(a->getAttackTotal());

}

/*******************************************************************************

Purpose: Check if number input is valid

In: String number input
Out: If valid return true, otherwise return false

*******************************************************************************/

bool isValidNum(std::string num)
{
	for(int i = 0; i < num.length(); i++)
	{
		if(!(num.at(i) >= '0' && num.at(i) <= '9'))
		return false;
	}
	return true;
}
