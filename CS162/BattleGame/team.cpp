#include "creature.h"
//#include "creature.cpp"
#include "team.h"
#include <deque>
#include <iostream>
using std::endl;
using std::cout;
using std::cin;

/********************************************************************************
Purpose: Constructor
*********************************************************************************/

Team::Team(int teamNumber, int numOfCreatures)
{
    this->teamNumber = teamNumber;                  //set teamNumber
    this->numOfCreatures = numOfCreatures;          //set number of creatures
}

/***********************************************************************************
Purpose: Return deque of Creature pointers
************************************************************************************/

std::deque<Creature*> Team::getTeam()
{
    return team;
}

/********************************************************************************************

Purpose: Display menu for user choice

In: None
Out: Outputs Menu on Display

*********************************************************************************************/

void Team::displayMenu()
{
        cout << "\nPlease select a number" << endl;
        cout << "1: GOBLIN" << endl;
        cout << "2: BARBARIAN"<< endl;
        cout << "3: REPTILE PEOPLE" << endl;
        cout << "4: BLUE MEN" << endl;
        cout << "5: THE SHADOW" << endl;
        cout << endl;
}


/*******************************************************************************

Purpose: Set Creature pointer to user choice

In: User choice integer
Out: Return pointer to user selected Creature Object

*******************************************************************************/

Creature* Team::getCreature(int choice)
{
    //set creature pointer
    Creature *a;
    //set pointer to user choice of Creature
    switch (choice)
    {
        //create goblin object
        case 1: a = new Goblin;
                break;
        //create barbarian object
        case 2: a = new Barbarian;
                break;
        //create reptile object
        case 3: a = new Reptile;
                break;
        //create blue men object
        case 4: a = new BlueMen;
                break;
        //create shadow object
        case 5: a = new Shadow;
    }
    return a;
}

/*******************************************************************************

Purpose: Allow user to choose team and store to deque
In: None
Out: Creates Deque with numOfCreature dynamically created Creature objects

*******************************************************************************/

void Team::chooseTeam()
{
    int num = 0;                    //loop increment
    int choice;                     //user choice
    std::string name;               //creature name

    //while counter doesn't equal num of creatures run loop
    while (num != numOfCreatures)
    {
        //increment
        num++;
        Creature *a;

        //output menu of creatures
        displayMenu();
        //get and validate user choice
        choice = getChoice();
        //initialize creature object
        a = getCreature(choice);

        //get user name for creature
        cin.ignore(100, '\n');
        cout << "What is the " << a->getType() <<" name?" << endl;
        getline(cin, name);

        //set creature name and team number
        a->setName(name);
        a->setTeamNum(teamNumber);
        //add creature to team container
        team.push_back(a);
        //print confirmation
        cout << team.back()->getName() << " the " << team.back()->getType() << " has been added to Team " << team.back()->getTeamNum() << endl;
    }
}

/********************************************************************************

Purpose: Print users team of creatures
In: None
Out: Outputs Contents of Team deque

*********************************************************************************/

void Team::printTeam()
{
    cout << "Team Number: " << teamNumber << endl;
    //output name and type
    for (unsigned int i = 0; i < team.size(); i++)
    {
        cout << team[i]->getName() << " the " << team[i]->getType()<< endl;
    }
}


/*********************************************************************************************

Purpose: Get and validate user choice
In: None
Out: Output int representing validated user choice

**********************************************************************************************/

int Team::getChoice()
{
        std::string num;
        bool valid = false;
        int choice;

        cin >> num;
        while (!valid)
        {
            valid = true;
            //check if all number in string are between 1 and 5
            for(unsigned int i = 0; i < num.length(); i++)
            {
                if(!(num.at(i) >= '1' && num.at(i) <= '5' && num.length() == 1))
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

