#ifndef MEATHEAD_H_INCLUDED
#define MEATHEAD_H_INCLUDED

#include <iostream>
#include <cstdlib>
#include <string>
#include <deque>

class Room;

class MeatHead
{
private:
	std::deque<std::string> gymBag;			//container for utensils
	int totGainz;							//gainz acquired
	Room* location;							//user location

public:
	MeatHead();
	~MeatHead(){};
	bool searchBag(std::string);
	void addToBag(std::string);
	std::deque<std::string> getGymBag();
	void makeGainz(int);
	int getGainz();
};

#endif //MEATHEAD_H_INCLUDED
