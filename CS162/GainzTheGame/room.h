#ifndef ROOM_H_INCLUDED
#define ROOM_H_INCLUDED

#include <iostream>
#include <cstdlib>
#include <string>
#include "meatHead.h"

/*
Room Base Class
*/
class Room
{
protected:
	std::string type;			//string representing room type/name
	
public:
	//pointers in each direction
	Room *north;
	Room *east;
	Room *south;
	Room *west;
	Room(std::string type);
	~Room();
	virtual std::string getType() = 0;
	virtual void roomTask(MeatHead*) = 0;
	void getMenu();
	int getChoice();	
};

/*
First Room Class
*/
class StartRoom : public Room
{
private:
	std::string room;
public:
	StartRoom(std::string room):Room(room)
	{
		this->room = room;
	}
	~StartRoom(){}
	std::string getType();
	void outputGoal();
	void roomTask(MeatHead*);
};

/*
Last Room Class
*/

class EndRoom : public Room
{
private:
	std::string room;
	int time;
public:
	EndRoom(std::string room):Room(room)
	{
		this->room = room;
	}
	~EndRoom(){}
	std::string getType();
	void roomTask(MeatHead*);
};

/*
Food Room Class
*/

class FoodRoom : public Room
{
private:
	std::string foodType;

public:
	FoodRoom(std::string foodType):Room(foodType)
	{
		this->foodType = foodType;
	}
	~FoodRoom(){}
	std::string getType();
	void roomTask(MeatHead*);
};

/*
Weight Room Class
*/

class WeightRoom : public Room
{
private:
	std::string exType;
public:
	WeightRoom(std::string exType):Room(exType)
	{
		this->exType = exType;
	}
	~WeightRoom(){}
	std::string getType();
	void roomTask(MeatHead*);
	int getExChoice();
};

/*
Puzzle Room Class
*/

class PuzzleRoom : public Room
{
private:
	std::string utensil;
public:
	PuzzleRoom(std::string utensil):Room(utensil)
	{
		this->utensil = utensil;
	}
	~PuzzleRoom(){}
	std::string getType();
	std::string upperCase(std::string);
	void roomTask(MeatHead*);
	bool getPuzzle(int);
};

#endif //ROOM_H_INCLUDED
