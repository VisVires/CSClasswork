/******************************************************************************
 *
 * Author: William George
 * Date Built: 02/20/2015
 * Date Last Modified: 03/01/2015
 * File Name: assign4.cpp
 *
 * Purpose: Tournament to pit teams of creatures from creature class object 
 * against each other, outputing the overall winner and the top 3 creatures in
 * the battle.
 *
 * Inputs: User chooses number of creatures then players each choose creatures
 * on the team
 *
 * Output: Program outputs the details of battle and the final result of the 
 * team battle.
 *
 * ***************************************************************************/

#include "team.h"
#include "creature.h"
#include "tBattle.h"
#include <cstdlib>
#include <iostream>
using std::endl;
using std::cout;
using std::cin;
#include <string>

int isValidNum(std::string);

int main()
{
        std::string numCreaturesInput;              //get user number input
        int numOfCreatures;                         //validated user number input
        char ch;                                    //wait for user input
        char again;                                 //variable to run loop again

        do
        {
            cout << "How Many Creatures Per Team? ";
            cin >> numCreaturesInput;

            numOfCreatures = isValidNum(numCreaturesInput);

            //initiate dynamic team objects
            Team* teamOne = new Team(1, numOfCreatures);
            Team* teamTwo = new Team(2, numOfCreatures);

            //clear screen
            system("clear");
            cout << "Player One, please choose your team" << endl;
            teamOne->chooseTeam();

            //clear screen
            system("clear");
            cout << "Player Two, please choose your team" << endl;
            teamTwo->chooseTeam();

            //clear screen
            system("clear");
            teamOne->printTeam();
            teamTwo->printTeam();

            cin.get(ch);
            cin.get(ch);

            //initiate dynamic battle sequence object
            TeamBattle *war = new TeamBattle(teamOne->getTeam(), teamTwo->getTeam());
            //perform battle
            war->battle();
            //get winning team
            war->findWinningTeam();
            //get winners bracket
            war->findWinningCreatures();

            //delete dynamic memory objects
            delete teamOne;
            delete teamTwo;
            delete war;
            //get user input to play again
            cout << "Play Again Y/N? ";
            cin >> again;
        }

        while (again == 'y' || again == 'Y');

    return 0;
}

/*******************************************************************************

Purpose: Check if number input is valid

In: String number input
Out: If valid return true, otherwise return false

*******************************************************************************/

int isValidNum(std::string num)
{
    bool validNum = false;
	int vNumber;                //validated number

	while(!validNum)
    {
        validNum = true;
        //check length of string for non numeric char
        for(unsigned int i = 0; i < num.length(); i++)
        {
            if(!(num.at(i) >= '0' && num.at(i) <= '9'))
            {
                validNum = false;
                cout << "That's not a valid number, please re-input: ";
                cin >> num;
            }
        }
    }

    //convert string to int
    vNumber = atoi(num.c_str());
    return vNumber;
}
