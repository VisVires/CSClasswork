#ifndef CREATURE_H_INCLUDED
#define CREATURE_H_INCLUDED

#include <iostream>
using std::cout;
using std::cin;
using std::endl;

#include <ctime>
#include <string>
#include <cstdlib>


class Creature
{
    protected:
        std::string type;               //holds creature type
        std::string name;               //holds creature name
        int arm;                        //creature armor
        int attTotal;                   //total of attack rolls
        int defTotal;                   //total of defense rolls
        int str;                        //remaining strength
        int startingStr;                //starting strength
        int aDiceNum;                   //number of attack dice
        int dDiceNum;                   //number of defense dice
        int aNumSides;                  //number of sides on attack dice
        int dNumSides;                  //number of sides on defense dice
        bool goblinAch;                 //if goblin achilles attack executed set to true
        int strOfVictoryPoints;     	//number of total points for player victories
        int teamNum;                    //creature team number

    public:
        Creature();
        Creature(std::string type, int aDiceNum, int dDiceNum, int aNumSides, int dNumSides, int arm, int str, bool goblinAch);
        ~Creature(){};
        virtual std::string getType() = 0;
        int rollDice(int) const;
        virtual int attack(Creature *a);
        virtual int defense(int);
        std::string getName();
        void setName(std::string);
        int getAttackTotal();
        int getStrength();
        int getStartStrength();
        void setStrOfVictory(int);
        int getStrOfVictory();
        void setGoblinAch(bool);
        bool getGoblinAch();
        void setTeamNum(int);
        int getTeamNum();
        void resolveAttack(int attackTotal);
        void recover();

};

/*********************************************************************/

class Barbarian: public Creature
{
    public:
        Barbarian():Creature("Barbarian", 2, 2, 6, 6, 0, 12, false){};
        ~Barbarian(){};
        std::string getType();

};
/*********************************************************************/

class Reptile: public Creature
{
    public:
        Reptile():Creature("Reptile People", 3, 1, 6, 6, 7, 18, false){};
        ~Reptile(){};
        std::string getType();
};

/********************************************************************/

class BlueMen: public Creature
{
    public:
        BlueMen():Creature("Blue Men", 2, 3, 10, 6, 3, 12, false){};
        ~BlueMen(){};
        std::string getType();
};

/*********************************************************************/

class Goblin: public Creature
{
    public:
        Goblin():Creature("Goblin", 2, 1, 6, 6, 3, 8, false){};
        ~Goblin(){};
        std::string getType();
        int attack(Creature *);
};

/***********************************************************************/

class Shadow: public Creature
{
    public:
        Shadow():Creature("The Shadow", 2, 1, 10, 6, 0, 12, false){};
        ~Shadow(){};
        std::string getType();
        int defense(int);
};

#endif // CREATURE_H_INCLUDED
