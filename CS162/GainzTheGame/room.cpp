#include "room.h"
#include "meatHead.h"
#include <iostream>
using std::cout;
using std::cin;
using std::endl;
#include <cstdlib>
#include <algorithm>
#include <ctime>
#include <deque>

/**************************************************************************************
Purpose: Constructor for Room base class
***************************************************************************************/
Room::Room(std::string type)
{
	this->type = type;
	north = NULL;
	east = NULL;
	south = NULL;
	west = NULL;
}

/****************************************************************************************
Purpose: Destructor
*****************************************************************************************/
Room::~Room(){}

/********************************************************************************************
Purpose: Display menu for user choice

In: None
Out: Outputs Menu on Display
*********************************************************************************************/
void Room::getMenu()
{
		cout << "\nSelect a Direction to Travel" << endl;
		cout << "Please select a number" << endl;
		cout << "1: North" << endl;
		cout << "2: East" << endl;
		cout << "3: South" << endl;
		cout << "4: West" << endl;
}

/*********************************************************************************************

Purpose: Get and validate user choice

In: None
Out: Output int representing validated user choice

**********************************************************************************************/
int Room::getChoice()
{
	std::string num;        //user input
	bool valid = false;
	int choice;             //validated choice

	cin >> num;

	while (!valid)
	{
		valid = true;
		//check if all number in string are between 1 and 4
		for (unsigned int i = 0; i < num.length(); i++)
		{
			if (!(num.at(i) >= '1' && num.at(i) <= '4' && num.length() == 1))
			{
				cout << "Please enter a valid choice between 1 and 4: ";
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

/***********************************************************************************

Purpose: Accessor function for room type

***********************************************************************************/
std::string StartRoom::getType()
{
	return room;
}

/*************************************************************************************

Purpose: Output menu from which the user is able to choose what they'd like to do

In: A pointer to a Meathead object
Out: Moves user to the next room 

**************************************************************************************/
void StartRoom::roomTask(MeatHead* meathead)
{
	int choice = 0;

	//output menu
	cout << "Please select a number" << endl;
	cout << "1: See Goal" << endl;
	cout << "2: Move to Next Room" << endl;
	cout << "3: Quit Game" << endl;

	//get user choice
	while (choice < 1 || choice > 3)
	{
		choice = getChoice();
	}

	//output game goal, play game or quit game
	switch (choice)
	{
	case 1: outputGoal();
			break;
	case 3: cout << "Thanks for playing!" << endl;
			exit(1);
	}
}

/*****************************************************************************************

Purpose: Output user mission

In: None
Out: None

******************************************************************************************/
void StartRoom::outputGoal()
{
	system("clear");
	cout << "GAINZ THE GAME" << endl;
	cout << "After the Earthquake Your Mom was trapped under a pillar!" << endl;
	cout << "You must eat and lift weights and call upon the will of Brodin, the god of gainz, and lift the pillar "<< endl;
	cout << "to save your Mom. To lift the weight you must eat, to eat you must have the right tools, and to get " << endl;
	cout << "the right tools you must solve the riddles. " << endl;
	cout << "Watch out for Broki, the robber of gainz! He will do all he can to keep you from completing your task." << endl;
	cout << "Quick! You only have 8 minutes to save her!  You need 100 gainz to win, Hurry!" << endl; 
}

/*************************************************************************************

Purpose: Accessor function for room type

**************************************************************************************/
std::string EndRoom::getType()
{
	return room;
}

/*******************************************************************************************

Purpose: Output congratulatory message

In: Pointer to Meathead class
Out: Outputs congratulatory message

********************************************************************************************/
void EndRoom::roomTask(MeatHead* meathead)
{
	cout << "You did it! You made all kinds of gains, Brodin would be proud!" << endl;
	cout << "Congrats bruh, you saved your Mom! Mad Respect" << endl;
}

/**************************************************************************************

Purpose: Accessor function for room type

**************************************************************************************/
std::string FoodRoom::getType()
{
	return foodType;
}

/***************************************************************************************

Purpose: Enter a food room and use an item, held in a container by the MeatHead object
to acquire calorie gainz

In: A pointer to the MeatHead object
Out: Adds gainz to MeatHead objects total gainz

****************************************************************************************/
void FoodRoom::roomTask(MeatHead* meathead)
{
	cout << "TIME TO EAT!" << endl;
	cout << "This is the " << foodType << " room" << endl;
	
	//output current contents of gymbag
	std::deque<std::string> gymbag = meathead->getGymBag();

	if (gymbag.size() > 0)
	{
		cout << "You have the: " << endl;
		for (unsigned int i = 0; i < gymbag.size(); i++)
		{
			cout << gymbag[i] << endl;
		}
	}

	//if user has chopticks, eat sushi and update gainz. Else move on to next room
	if (foodType == "Sushi")
	{
		if (meathead->searchBag("Chopsticks"))
		{
			cout << "Let's get "<< foodType <<" gainz" << endl;
			cout << "Brodin grants you 7 Calorie Gainz" << endl;
			meathead->makeGainz(7);
		}
		else
			cout << "Fool! You need chopsticks to eat Sushi, go find them!" << endl;
	}

	//if user has a fork, eat spaghetti and update gainz. Else move on to next room
	else if (foodType == "Spaghetti")
	{
		if (meathead->searchBag("Fork"))
		{
			cout << "Let's get " << foodType << " gainz" << endl;
			cout << "Brodin grants you 14 Calorie Gainz" << endl;
			meathead->makeGainz(14);
		}
		else
			cout << "I pity the fool who tries to eat Spaghetti without a fork!" << endl;
	}

	//if user has a fork and knife and napkin, eat steak and update gainz. Else move on to next room
	else if (foodType == "Steak")
	{
		if (meathead->searchBag("Fork") && meathead->searchBag("Knife") && meathead->searchBag("Napkin"))
		{
			cout << "Let's get " << foodType << " gainz" << endl;
			cout << "Brodin grants you 27 Calorie Gainz" << endl;
			meathead->makeGainz(27);
		}
		else
			cout << "You can't eat steak without a fork, a knife and a napkin!" << endl;
	}

	//if user has a napkin, eat wings and update gainz. Else move on to next room
	else if (foodType == "Wings")
	{
		if (meathead->searchBag("Napkin"))
		{
			cout << "Let's get " << foodType << " gainz" << endl;
			cout << "Brodin grants you 10 Calorie Gainz" << endl;
			meathead->makeGainz(10);
		}
		else
			cout << "You're gonna get too messy eating these wings without a napkin!" << endl;
	}

	//if user has a knife and blender, make and eat a Protein Shake and update gainz. Else move on to next room
	else if (foodType == "Protein Shake")
	{
		if (meathead->searchBag("Blender") && meathead->searchBag("Knife"))
		{
			cout << "Let's drink a " << foodType << " and get all kinds of gainz" << endl;
			cout << "Brodin grants you 20 Calorie Gainz" << endl;
			meathead->makeGainz(20);
		}
		else
			cout << "You can't drink a shake uncut and unblended fool! Get a knife and a blender" << endl;
	}
}

/***************************************************************************************

Purpose: Accessor function for room type

***************************************************************************************/
std::string WeightRoom::getType()
{
	return exType;
}

/****************************************************************************************

Purpose: Give the user a choice of how they'd like to workout and give the MeatHead object
the designated number of strength gainz

In: Pointer to MeatHead object
Out: Updates MeatHead gainz accumulator based on user choice 

*****************************************************************************************/
void WeightRoom::roomTask(MeatHead* meathead)
{
	int exChoice;						//user excercise choice

	cout << "TIME TO WORKOUT!" << endl;
	//output room type
	cout << "This is the " << exType << " room" << endl;

	//check room type and output choices
	//Treadmill room
	if (exType == "Treadmill")
	{
		cout << "Press 1 to run 5 km" << endl;
		cout << "Press 2 to run 10 x 100m Sprints" << endl;

		//get and validate user choice
		exChoice = getExChoice();

		//update user gainz
		if (exChoice == 1)
		{
			cout << "5 km? That's cardio bruh! You lost gainz!" << endl;
			cout << "Broki took 30 of your gainz" << endl;
			meathead->makeGainz(-30);
		}
		else
		{
			cout << "You're winded, but you're more powerful! Gainz acquired!" << endl;
			cout << "Brodin has blessed you with 15 gainz" << endl;
			meathead->makeGainz(15);
		}
	}

	//Squat room
	else if (exType == "Squats")
	{
		cout << "Press 1 to do 1 set of 20 Reps with Lightweight" << endl;
		cout << "Press 2 to do 4 sets of 5 reps with Heavyweight" << endl;

		//get and validate user choice
		exChoice = getExChoice();

		//update user gainz
		if (exChoice == 1)
		{
			cout << "Quarter Reps don't count bruh, the only way to get stronger is to lift more weight!" << endl;
			cout << "Broki robbed you of 10 of your gainz" << endl;
			meathead->makeGainz(-10);
		}
		else
		{
			cout << "YEAHHHH BUDDY!! Gainz acquired! Praise be to Brodin" << endl;
			cout << "The Iron God is proud of your Ass to Grass Squats you get 30 gainz" << endl;
			meathead->makeGainz(30);
		}	
	}

	//Deadlift room
	else if (exType == "Deadlift")
	{
		cout << "Press 1 to do 1 set of 20 Reps with Lightweight" << endl;
		cout << "Press 2 to do 4 sets of 5 reps with Heavyweight" << endl;

		//get and validate user choice
		exChoice = getExChoice();

		//update user gainz
		if (exChoice == 1)
		{
			cout << "There's no bad choice for Deadlifts, get it baby! RUPPPP!" << endl;
			cout << "Brodin has blessed you with 20 gainz" << endl;
			meathead->makeGainz(20);
		}
		else
		{
			cout << "LIGHTWEIGHT! Pick it up, and put it down! Brodin looks favorably upon you, Brother of Iron"  << endl;
			cout << "You made all 35 gainz" << endl;
			meathead->makeGainz(35);
		}
	}

	//Elliptical room
	else if (exType == "Elliptical")
	{
		cout << "Press 1 to do High Resistance 20 minutes" << endl;
		cout << "Press 2 to do Low Resistance for 1 Hour" << endl;

		//get and validate user choice
		exChoice = getExChoice();

		//update user gainz
		if (exChoice == 1)
		{
			cout << "There's no good choice for Cardio! You're wasting time and Gainz" << endl;
			cout << "Broki robbed you of 20 of your gainz" << endl;
			meathead->makeGainz(-20);
		}
		else
		{
			cout << "Do you want to be skinny fat? You must be a follower of Broki" << endl;
			cout << "Broki took 35 of your gainz" << endl;
			meathead->makeGainz(-35);
		}
	}

	//Farmer Carry room
	else if (exType == "Farmers Carry")
	{
		cout << "Press 1 to do 1 x 100m Carry" << endl;
		cout << "Press 2 to do 5 x 20m Carry " << endl;

		//get and validate user choice
		exChoice = getExChoice();

		//update user gainz
		if (exChoice == 1)
		{
			cout << "Everybody wanna be a bodybuilder but no one wanna carry this heavy ass weight. Blessed be Brodin the Allspotter"  << endl;
			cout << "The gods are pleased! You get 15 gainz" << endl;
			meathead->makeGainz(15);
		}
		else
		{
			cout << "You need to get that grip strength! You gotta hold the weight to get stronger." << endl;
			cout << "Brodin gives you 5 gainz" << endl;
			meathead->makeGainz(5);
		}
	}
}

/**************************************************************************************

Purpose: Get and validate user choice for excercise

In: None
Out: Returns a validated integer equaling either 1 or 2

***************************************************************************************/
int WeightRoom::getExChoice()
{
	std::string num;        //user input
	bool valid = false;
	int choice;             //validated choice

	cin >> num;

	while (!valid)
	{
		valid = true;
		//check if all number in string are between 1 and 2
		for (unsigned int i = 0; i < num.length(); i++)
		{
			if (!(num.at(i) >= '1' && num.at(i) <= '2' && num.length() == 1))
			{
				cout << "Please enter a valid choice: ";
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

/****************************************************************************************

Purpose: Accessor function for room type

*****************************************************************************************/
std::string PuzzleRoom::getType()
{
	return utensil;
}

/*************************************************************************************

Purpose: Have user answer a riddle to either move to the next room or to acquire a 
utensil placed in the MeatHead container

In: Pointer to MeatHead object
Out: Either place a utensil in MeatHead object container or advance to next room

**************************************************************************************/
void PuzzleRoom::roomTask(MeatHead* meathead)
{
	//if user has already obtained utensil answer a riddle to move on
	if (meathead->searchBag(utensil))
	{
		cout << "You've already got a " << utensil << endl;
		cout << "To move on answer the following riddle: " << endl;
		
		//generate random number between 1 and 10
		int puzzleNum = (rand() % 10) + 1;

		//call riddle function and set bool variable to returned value
		bool correct = getPuzzle(puzzleNum);
		
		//if user was incorrect, ask another question
		while (correct == false)
		{
			cout << "Sorry you failed to answer correctly, try another" << endl;
			int puzzleNum = (rand() % 10) + 1;
			correct = getPuzzle(puzzleNum);
		}
		//return to maze
		return;
	}

	//if user does not yet have utensil
	else
		cout << "To get a " << utensil << " you must answer a riddle correctly" << endl;

	//generate random number
	int puzzleNum = (rand() % 10) + 1;

	//if puzzel is correct give user utensil
	if (getPuzzle(puzzleNum))
		meathead->addToBag(utensil);
	//output message and move on to next room
	else
		cout << "Sorry you failed to answer correctly, maybe next time" << endl;
	
}

/**************************************************************************************

Purpose: Use number input to choose 1 riddle from the 10 listed, give user 3 tries to
answer. On each incorrect try a hint will be output

In: A number generated by a random number generator
Out: Outputs a riddle and if the user answers correctly returns true, else it returns
false

***************************************************************************************/
bool PuzzleRoom::getPuzzle(int num)
{
	bool correct = false;				//check if user was correct
	std::string answer;					//get users answer
	int tries = 3;						//number of attempts remaining
	
	do
	{
		//output number of tries
		cout << "You have " << tries << " guesses remaining" << endl << endl;
		
		//output question and hints based on number of tries
		switch (num)
		{
		case 1: 
			cout << "Which creature walks on four legs in the morning, two legs in the afternoon, and three legs in the evening?" << endl;
			
			// 1st Hint
			if (tries == 2)
				cout << "Hint: 1 Word, 3 letters" << endl;
			// 2nd Hint
			else if (tries == 1)
				cout << "Hint: Rhymes with Fan" << endl;
			//get user answer
			cin >> answer;
			//change answer to all uppercase
			answer = upperCase(answer);
			//decrement # of tries
			tries--;

			//if answer is correct set correct to true
			if (answer == "MAN")
				correct = true;

			//if wrong 3 times, output answer
			if (tries == 0 && correct == false)
				cout << "THE ANSWER IS MAN" << endl;
			break;
		
		case 2: 
			cout << "Paul's height is six feet, he's an assistant at a butcher's shop, and wears size 9 shoes. What does he weigh?" << endl;

			if (tries == 2)
				cout << "Hint: 1 Word, 4 letters" << endl;

			else if (tries == 1)
				cout << "Hint: What does Paul do?" << endl;

			cin >> answer;
			answer = upperCase(answer);
			tries--;

			if (answer == "MEAT")
				correct = true;

			if (tries == 0 && correct == false)
				cout << "THE ANSWER IS MEAT" << endl;
			
			break;

		case 3:
			cout << "What kind of room has no doors or windows?" << endl;

			if (tries == 2)
				cout << "Hint: 1 Word, 8 letters" << endl;

			else if (tries == 1)
				cout << "Hint: Fungus" << endl;

			cin >> answer;
			answer = upperCase(answer);
			tries--;

			if (answer == "MUSHROOM")
				correct = true;

			if (tries == 0 && correct == false)
				cout << "THE ANSWER IS A MUSHROOM" << endl;
			break;

		case 4:
			cout << "Which word in the dictionary is spelled incorrectly?" << endl;

				if (tries == 2)
					cout << "Hint: 1 Word, 11 letters" << endl;

				else if (tries == 1)
					cout << "Hint: It's Synonymn is Wrong too" << endl;

			cin >> answer;
			answer = upperCase(answer);
			tries--;

			if (answer == "INCORRECTLY")
				correct = true;

			if (tries == 0 && correct == false)
				cout << "THE ANSWER IS INCORRECTLY" << endl;

			break;

		case 5:
			cout << "Feed me and I live, yet give me a drink and I die." << endl;

				if (tries == 2)
					cout << "Hint: 1 Word, 4 letters" << endl;

				else if (tries == 1)
					cout << "Hint: I can burn you" << endl;

			cin >> answer;
			answer = upperCase(answer);
			tries--;

			if (answer == "FIRE")
				correct = true;

			if (tries == 0 && correct == false)
				cout << "THE ANSWER IS FIRE" << endl;
			break;

		case 6:
			cout << "What occurs once in every minute, twice in every moment, yet never in a thousand years?" << endl;

				if (tries == 2)
					cout << "Hint: Happens once every mile too" << endl;

				else if (tries == 1)
					cout << "Hint: A letter" << endl;

			cin >> answer;
			answer = upperCase(answer);
			tries--;

			if (answer == "M")
				correct = true;
			if (tries == 0 && correct == false)
				cout << "THE ANSWER IS THE LETTER M" << endl;
			break;

		case 7:
			cout << "Poor people have it. Rich people need it. If you eat it you die. What is it?" << endl;

				if (tries == 2)
					cout << "Hint: One word, seven letters" << endl;

				else if (tries == 1)
					cout << "Hint: It really isn't anything" << endl;
				
			cin >> answer;
			answer = upperCase(answer);
			tries--;

			if (answer == "NOTHING")
				correct = true;
			
			if (tries == 0 && correct == false)
				cout << "THE ANSWER IS NOTHING" << endl;

			break;

		case 8:
			cout << "What comes down but never goes up?" << endl;

				if (tries == 2)
					cout << "Hint: 1 Word, 4 letters" << endl;

				else if (tries == 1)
					cout << "Hint: It's wet" << endl;

			cin >> answer;
			answer = upperCase(answer);
			tries--;

			if (answer == "RAIN")
				correct = true;

			if (tries == 0 && correct == false)
				cout << "THE ANSWER IS RAIN" << endl;
			break;

		case 9:
			cout << "Mary’s father has 5 daughters – Nana, Nene, Nini, Nono. What is the fifth daughters name?" << endl;

				if (tries == 2)
					cout << "Hint: 1 Word, 4 letters" << endl;

				else if (tries == 1)
					cout << "Hint: Read the question" << endl;

			cin >> answer;
			answer = upperCase(answer);
			tries--;

			if (answer == "MARY")
				correct = true;
			if (tries == 0 && correct == false)
				cout << "THE ANSWER IS MARY" << endl;
			break;

		case 10:
			cout << "They come out at night without being called, and are lost in the day without being stolen. What are they?" << endl;

				if (tries == 2)
					cout << "Hint: 1 Word, 5 letters" << endl;

				else if (tries == 1)
					cout << "Hint: Great balls of fire" << endl;

			cin >> answer;
			answer = upperCase(answer);
			tries--;

			if (answer == "STARS")
				correct = true;
			if (tries == 0 && correct == false)
				cout << "THE ANSWER IS THE STARS" << endl;
			break;
		}

		//output message if correct
		if (correct == true)
			cout << "CORRECT!!" << endl;
		
	}
	//loop until correct is true or user is out of tries
	while (correct == false && tries != 0);
	
	return correct;
}

/****************************************************************************************

Purpose: Takes string input and converts it to all uppercase

In: String input by user
Out: Uppercase version of original string input

****************************************************************************************/
std::string PuzzleRoom::upperCase(std::string word)
{
	//transform word to all uppercase letters
	transform(word.begin(), word.end(), word.begin(), ::toupper);
	return word;
}
