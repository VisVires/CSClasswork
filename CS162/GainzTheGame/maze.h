#ifndef MAZE_H_INCLUDED
#define MAZE_H_INCLUDED

#include <string>
#include "room.h"
#include "meatHead.h"

class Room;
class MeatHead;

class Maze
{
private:
	//room pointers
	Room *startRoom;
	Room *bombRoom;
	Room *spagRoom;
	Room *steakRoom;
	Room *shakeRoom;
	Room *sushiRoom;
	Room *wingRoom;
	Room *ellipRoom;
	Room *deadRoom;
	Room *squatRoom;
	Room *farmRoom;
	Room *runRoom;
	Room *forkRoom;
	Room *knifeRoom;
	Room *napRoom;
	Room *blendRoom;
	Room *chopRoom;
	//iterator
	Room *player;
	//player info
	MeatHead *meathead;

public:
	Maze();
	~Maze();
	void buildMaze();
	void traverseRooms();
	std::string getRoom();
	void movePlayer();
};


#endif // MAZE_H_INCLUDED
