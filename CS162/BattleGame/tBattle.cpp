//#include "creature.cpp"
//#include "team.cpp"
#include "tBattle.h"
#include "team.h"
#include "creature.h"

TeamBattle::TeamBattle(std::deque<Creature*> teamOne, std::deque<Creature*> teamTwo)
{
        this->teamOne = teamOne;        //set team one
        this->teamTwo = teamTwo;        //set team two
	teamOnePoints = 0;
	teamTwoPoints = 0;
        srand(time(NULL));              //set seed
}

/**************************************************************************************

Purpose: Run creature battle sequences until one user is out of creatures

In: None
Out: Output battle sequence

***************************************************************************************/

void TeamBattle::battle()
{

    char ch;                //user wait

    //while each team still has creatures to battle, run battle
    while (!(teamOne.size() == 0 || teamTwo.size() == 0))
    {
        Creature *a;                //player one creature
        Creature *b;                //player two creature

        bool teamOneLose = false;
        bool teamTwoLose = false;

        a = teamOne.front();        //set player one to first added creature on team one
        b = teamTwo.front();        //set player two to first added creature on team two

        //clear screen
        system("clear");

        //output match-up
        cout << "Team " << a->getTeamNum() << " Warrior: " << a->getName() << " the " <<a-> getType() << " vs. ";
        cout << "Team " << b->getTeamNum() << " Warrior: " << b->getName() << " the " <<b->getType() << endl;

        //wait for user input
        cin.get(ch);

        //while both characters str is > 0
        while(!teamOneLose || !teamTwoLose)
        {
            system("clear");

            attackSequence(b, a);

            if (a->getStrength() < 1)
            {

                teamOneLose = true;
                break;
            }

            attackSequence(a, b);

            if (b->getStrength() < 1)
            {
                teamTwoLose = true;
                break;
            }
            cin.get(ch);
        }

        /*
        *If team one loses calculate and update strOfVictory, add team one to loser pile
        *add team two to back of lineup remove both players from front
        */

        if (teamOneLose)
        {
            cout << b->getName() <<" the "<< b->getType() <<" Wins!" << endl;
            strOfVictory(b,a);

            cin.get(ch);

            losers.push_back(a);
            teamTwo.push_back(b);

            //if team one is out of warriors exit
            if (teamOne.size() == 1)
            {
                teamOne.pop_front();
                teamTwo.pop_front();
                cout << "Player One Is Out of Warriors!" << endl;
                return;
            }
            else
            {
                teamOne.pop_front();
                teamTwo.pop_front();
            }
            b->recover();
            cin.get(ch);
        }

        /*
        *If team two loses calculate and update strOfVictory, add team two to loser pile
        *add team one to back of lineup remove both players from front
        */
        else if (teamTwoLose)
        {
            cout << a->getName() << " the " << a->getType() << " Wins!" << endl;
            strOfVictory(a,b);

            cin.get(ch);
            losers.push_back(b);
            teamOne.push_back(a);


            //if team two is out of warriors leave function
            if (teamTwo.size() == 1)
            {
                teamOne.pop_front();
                teamTwo.pop_front();
                cout << "Player Two Is Out of Warriors!" << endl;
                return;
            }
            else
            {
                teamOne.pop_front();
                teamTwo.pop_front();
            }
            a->recover();
            cin.get(ch);
        }
    }
}

/************************************************************************************************

Purpose: Calculate strength of victory based on Creatures opponents healthy strength, if difference
is negative strength of victory = 1

In: Pointers to each creature involved in battle
Out: Add to winner's strength of victory accumulator

************************************************************************************************/

void TeamBattle::strOfVictory(Creature *a, Creature *b)
{
    int strOfVictory;
    //subtract loser healthy strength from winner
    strOfVictory = b->getStartStrength() - a->getStartStrength();

    //if less than one then strength of victory = 1 point
    if (strOfVictory < 1)
    {
        strOfVictory = 1;
    }

    //add to strOfVictory accumulator
    a->setStrOfVictory(strOfVictory);
}

/***********************************************************************************************

Purpose: Run creature attack sequence

In: Pointers to each creature in attack
Out: Changes creature b's remaining strength

***********************************************************************************************/

void TeamBattle::attackSequence(Creature* a, Creature* b)
{
        //attack Creature b object
        a->attack(b);
        //defend using creature attack total
        b->defense(a->getAttackTotal());
        //complete attack and alter defender strength variable
        b->resolveAttack(a->getAttackTotal());
}

/**********************************************************************************************

Purpose: Calculate winning team based on team total strength of victory. If a tie then winning
team is determined by coin flip

In: None
Out: Output winning team

***********************************************************************************************/

void TeamBattle::findWinningTeam()
{
    //if team one has players remaining get player points
    if (teamOne.size() > 0)
    {
        for(unsigned int i = 0; i < teamOne.size(); i++)
        {
            teamOnePoints += teamOne[i]->getStrOfVictory();
        }
    }

    //if team two has players remaining get player points
    if (teamTwo.size() > 0)
    {
        for(unsigned int i = 0; i < teamTwo.size(); i++)
        {
            teamTwoPoints += teamTwo[i]->getStrOfVictory();
        }
    }

    //accumulate total strOfVictory for each team
    for (unsigned int i = 0; i < losers.size(); i++)
    {
        if (losers[i]->getTeamNum() == 1)
        {
            teamOnePoints += losers[i]->getStrOfVictory();
        }
       if (losers[i]->getTeamNum() == 2)
        {
            teamTwoPoints += losers[i]->getStrOfVictory();
        }
    }

    //output final score
    cout << "Player One Score: " << teamOnePoints << endl;
    cout << "Player Two Score: " << teamTwoPoints << endl;


    //output winner, if tie use coin flip
    if (teamOnePoints > teamTwoPoints)
    {
        cout << "Overall Winner is Player One!" << endl;
    }
    else if (teamOnePoints < teamTwoPoints)
    {
        cout << "Overall Winner is Player Two!" << endl;
    }
    else if (teamOnePoints == teamTwoPoints)
    {
        int flipResult;
        int flipGuess = 0;
        cout << "TIE" << endl;
        cout << "Flip a coin to determine the winner" << endl;

	while (!(flipGuess == 1 || flipGuess == 2))
	{
        	cout << "Player Two choose 1 for heads or 2 for tails: ";
		cin >> flipGuess;
	}

        flipResult = coinFlip();

	if(flipResult == 1)
	{
		cout << "HEADS" << endl;
	}

	else if(flipResult == 2)
	{
		cout << "TAILS" << endl;
	}

        if (flipGuess == flipResult)
        {
            cout << "You guessed correct! Player Two Wins!" << endl;
        }
        else
            cout << "Wrong! Player One Wins!" << endl;

    }
}

/*****************************************************************************************

Purpose: Determine Creature places based on last surviving then last to the loser container

In: None
Out:Output the Creatures in 1st, 2nd and 3rd place

******************************************************************************************/

void TeamBattle::findWinningCreatures()
{
    std::vector<Creature*> bracket;             //vector to hold three winners
    Creature* a;                                //pointer to top creatures in winning bracket
    Creature* b;                                //pointer to top creatures in losing bracket
    int place = 1;
    unsigned int i = 0;

    /*
    * while one team has players left and winning bracket has less than 3 creatures
    * add player to bracket vector and remove top player from team
    */
    while(!(teamOne.size() == 0 && teamTwo.size() == 0))//|| bracket.size() == 3)
    {
        if (teamOne.size() > 0)
        {
            a = teamOne.front();
            bracket.push_back(a);
            teamOne.pop_front();
        }

        else if (teamTwo.size() > 0)
        {
            a = teamTwo.front();
            bracket.push_back(a);
            teamTwo.pop_front();
        }
    }

    //if more than one winner is from the same team output place as a tie
    for (i = 0; i < bracket.size(); i++)
    {
        cout << place << " place: ";
        cout << "Team Number " << bracket[i]->getTeamNum() << ": ";
        cout << bracket[i]->getName() << " the " << bracket[i]->getType() << endl;
    }

    /*
    * If bracket does not have three creatures, add last creature added to losers pile to bracket until bracket has 3
    */

    while(bracket.size() < 3 && losers.size() != 0)
    {
        b = losers.back();
        bracket.push_back(b);
        losers.pop_back();
    }

    //output remainder of winners bracket
    while(i < 3)
    {
        cout << i + 1 << " place: ";
        cout << "Team Number " << bracket[i]->getTeamNum() << ": ";
        cout << bracket[i]->getName() << " the " << bracket[i]->getType() << endl;
        i++;
    }
}

/***********************************************************************************************

Purpose: Coin Flip and return Result

In: None
Out: Returns random number between 1 and 2

************************************************************************************************/

int TeamBattle::coinFlip() const
{
    return (rand() % 2) + 1;
    //output random num between 1 and 2
}
