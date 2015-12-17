#ifndef TBATTLE_H_INCLUDED
#define TBATTLE_H_INCLUDED

#include <queue>
#include <stack>


class Team;
class Creature;

class TeamBattle
{
private:
    std::deque<Creature*> teamOne;      //deque holds team one
    std::deque<Creature*> teamTwo;      //deque for team two
    std::deque<Creature*> losers;       //deque for losers pile
    int teamOnePoints;              	//team one point accumulator
    int teamTwoPoints;	              	//team two point accumulator


public:
    TeamBattle(std::deque<Creature*> teamOne, std::deque<Creature*> teamTwo);
    ~TeamBattle(){};
    void attackSequence(Creature *a, Creature *b);
    void strOfVictory(Creature *a, Creature *b);
    void battle();
    void findWinningTeam();
    void findWinningCreatures();
    int coinFlip() const;
};

#endif // TBATTLE_H_INCLUDED
