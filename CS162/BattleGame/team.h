#ifndef TEAM_H_INCLUDED
#define TEAM_H_INCLUDED

#include <deque>

class Creature;

class Team
{
private:
        int numOfCreatures;             //user inputed number of creatures
        std::deque<Creature*> team;     //deque of creature pointers
        int teamNumber;                 //team number
public:
        Team(int teamNumber, int numOfCreatures);
        ~Team(){};
        void chooseTeam();
        int getChoice();
        std::deque<Creature*> getTeam();
        Creature* getCreature(int);
        void displayMenu();
        void printTeam();
};

#endif // TEAM_H_INCLUDED
