/********************************************************************************************************************************************************************************************
 *Author: William George
 *Date Created: 10/8/2014
 *Date Last Modified: 10/12/2014
 *File Name: fireLaw.cpp
 *
 *Overview: The purpose of this program is to ask a user what room they'd like to use then input the number of people coming to the meeting. If there are too many people coming to the meeting then the program will tell them they need to find a new room to accomadate the entire group of participants and adhere to the fire laws max capactiy.
 *
 *
 *Input: User inputs which room they'd like to use then asks how many people will be attending the meeting. If there are too many people coming the program will tell the user fi they can use the room and how many extra people can come or cannot come if there are too many.
 *
 *Output: program outputs to select a valid room number then asks how many people will be attending. Afterwards it outputs whether they can use the meeting room and if so tells them how many more people can attend. If not it outputs they cannot use the room and how many people they must exclude to fit the meeting spaces max capacity requirements
 *
 *
 *
 *
 * *****************************************************************************************************************************************************************************************/

#include<iostream>
using namespace std;

int main()
{
const int roomOne = 8,//define meeting room max capacties
	  roomTwo = 10,
	  roomThree = 15,
	  roomFour = 32,
	  roomFive = 4;
int meetingRoomNumber;//define meeting room number
int maxCapacity;		
int numAttendees;
int remainingCapacity;//left over room in the meeting room if there is overflow or less than what is needed in the room

	cout<<"Please select meeting room 1,2,3,4 or 5 ";//output please choose meeting room number
	cin>>meetingRoomNumber;//user input

while(!(meetingRoomNumber >= 1 && meetingRoomNumber <=5))//validates that the user input is actually in the correct range of values
{
	cout << "That is not a valid meeting room please select room 1,2,3,4 or 5: ";
	cin>> meetingRoomNumber; //reinput meeting room number
}
cout<<"Your Meeting Room is: "<<meetingRoomNumber<<endl;// tells user their input back to them

switch(meetingRoomNumber)//switch statement to define max capacity based on user input for room number
{
	case 1: maxCapacity = roomOne;
	break; 
	case 2: maxCapacity = roomTwo;
	break;
	case 3: maxCapacity = roomThree;
	break; 
	case 4: maxCapacity = roomFour;
	break;
	case 5: maxCapacity = roomFive;
}

cout<<"Max Capacity of Meeting Room "<<meetingRoomNumber<<" is "<<maxCapacity<<" people "<<endl;//tells user how many people can meet in that room
cout<<"How many people will be attending the meeting? ";//asks user how manay people will be attending the meeting
cin>> numAttendees;//input number of people coming to the meeting

remainingCapacity = maxCapacity - numAttendees;//finds the difference bettween the attendees and the max capactiy
if (remainingCapacity >= 0)//if the max capacity is greater than the num of attendess then the meeting may be held and some more people may attend
{
	cout<<"Meeting may be held in Meeting Room "<<meetingRoomNumber<<" also you may invite "<<remainingCapacity<<" more people."<<endl;
}
else//if the max capacity is less than the number of people coming then the user must choose a new meeting room. 
{
	remainingCapacity = remainingCapacity * -1;
	cout<<"Meeting may not be held in "<<meetingRoomNumber<<" please select another room that will accomadate the remaining "<<remainingCapacity<<" people."<<endl; 
}
return 0;
}//end program
