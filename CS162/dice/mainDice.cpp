#include <iostream>
using std::endl;
using std::cout;
using std::cin;
#include <iomanip>
#include "dice.cpp"
#include "dice.h"
#include <vector>
#include <algorithm>
#include <cmath>
#include <fstream>

double findMean(std::vector <int> &);
int findMedian(std::vector <int> &);
std::vector<int> findMode(std::vector <int> &);
double standardDev(std::vector <int> &, double mean);

int main()
{
    	Dice dice1(12);                  	//dice object with 8 sides
    	Dice dice2;                     	//default dice object

    	LoadedDice lDice1(12);           	//dice object with 8 sides
    	LoadedDice lDice2;              	//default dice object

    	std::vector <int> lStats;       	//vector to hold loaded dice rolls
    	std::vector <int> nStats;       	//vector to hold normal dice rolls

    	std::vector <int> lModeVect;    	//vector to hold loaded dice modes
    	std::vector <int> nModeVect;    	//vector to hold normal dice modes

    	int num, rolls;                 	//int to hold roll result
    	double lMean, nMean;            	//int to hold loaded/normal means

    	std::fstream loadDice;
    	std::fstream normalDice;

    	loadDice.open("LoadDiceResults.csv", std::ios::out);
    	if(!loadDice)
    	{
    		cout << "Cannot open file" << endl;
        	return 1;
    	}

    	normalDice.open("normalDiceResults.csv", std::ios::out);
    	if(!normalDice)
    	{
		cout << "Cannot open file" << endl;
        	return 1;
    	}

	cout << "Enter how many times you'd like to roll or -1 to see stats" << endl;
        cin >> rolls;

   	while(rolls != -1)
    	//loop until user enters -1
    	{

        	cout << " Normal Dice Rolls: " << endl;
        	for(int i = 0; i < rolls; i++)
        	//roll normal dice and store to normal stats
        	{
            		num = rollTwoDice(dice1, dice2);
            		cout << num << endl;
                    normalDice << num << endl;
            		nStats.push_back(num);
        	}


        	cout << "Loaded Dice Rolls: " << endl;
        	for(int i = 0; i < rolls; i++)
        	//roll loaded dice and store to loaded stats
        	{
            		num = rollTwoDice(lDice1, lDice2);
            		cout << num << endl;
                    loadDice << num << endl;
            		lStats.push_back(num);
        	}

        	cout << "Enter how many times you'd like to roll or -1 to see stats" << endl;
        	cin >> rolls;
	}


        //find normal dice stats
        nMean = findMean(nStats);
        cout << "Normal Mean: " << std::fixed << std::setprecision(2) << nMean << endl;
        cout << "Normal Median: " << findMedian(nStats) << endl;
        cout << "Normal Mode: ";
        nModeVect = findMode(nStats);
        for (int i = 0; i < nModeVect.size(); i++)
        {
               	cout << nModeVect[i] << " ";
        }
       	cout << endl;
        cout << "Normal Standard Deviation: " << standardDev(nStats, nMean) << endl << endl;


        //find loaded dice stats
        lMean = findMean(lStats);
        cout << "Loaded Mean: " << std::fixed << std::setprecision(2)<< lMean << endl;
        cout << "Loaded Median: " << findMedian(lStats) << endl;
        cout << "Loaded Mode: ";
        lModeVect = findMode(lStats);
        for (int i = 0; i < lModeVect.size(); i++)
        {
           	cout << lModeVect[i] << " ";
        }
        cout << endl;
        cout << "Loaded Standard Deviation: " << standardDev(lStats, lMean) << endl;


	normalDice.close();
	loadDice.close();

	return 0;
}

/*******************************************************************************************************************************

Purpose: Find mean of a vector of stats

In: Takes vector of dice roll results
Out: Outputs mean of values in vector

*******************************************************************************************************************************/

double findMean(std::vector <int> &stats)
{
    double total = 0;
    //initialize variable to find sum

    for(int i = 0; i < stats.size(); i++)
    //accumulates total of rolls
    {
        total += stats[i];
    }

    return total/stats.size();
    //return mean
}

/*********************************************************************************************************************************

Purpose: Find median of vector of dice rolls

In: Takes vector of dice roll results
Out: Outputs median of dice roll results

**********************************************************************************************************************************/

int findMedian(std::vector <int> &stats)
{
    int median;                     //holds median
    int rollNum = stats.size();     //set rollNum as total number of rolls

    std::sort (stats.begin(), stats.end()); //sort roll num by value

    if (rollNum % 2 == 0)
    //if even
    {
        median = (stats[rollNum / 2 - 1] + stats[rollNum / 2]) / 2;
        //find average of two middle numbers
    }
    else
    {
        median = stats[rollNum / 2];
        //find median position
    }
    return median;
}

/********************************************************************************************************************************

Purpose: Find mode of vector of numbers

In: Takes vector of ints
Out:  returns vector of most frequent occurring int in vector

********************************************************************************************************************************/

std::vector<int> findMode(std::vector <int> &stats)
{
    std::vector<int> mode;
	//set mode vector
	int counter = 1;
	//number counter to see frequency of numbers
	int mostNums = 0;
	//variable to see the most frequent number

	for(int i = 0; i < stats.size(); i++)
	{
		if(stats[i] == stats[i+1])
		//checks if value is equal to the next value
		{
			counter++;
			//if so increment counter
            if (counter == mostNums)
			//if counter is equal to the most frequent variable then add to mode vector
			{
				mode.push_back(stats[i]);
			}
			else if (counter > mostNums)
			//if counter is greater than previous most frequent value
			{
				mode.clear();
				//clear mode vector
				mostNums = counter;
				//set new number as the most frequent
				mode.push_back(stats[i]);
				//add new value to mode vector at position one
			}
		}
		else
		{
			counter = 1;
			//reset counter
		}
	}
	return mode;
}

/*************************************************************************************************************************

Purpose: Find standard deviation of vector of dice rolls

In: Vector of dice rolls and mean of vector
Out: Outputs standard deviation

**************************************************************************************************************************/

double standardDev(std::vector <int> &stats, double mean)
{
    double sd, meanDiff, total;                 //standard deviation, squared difference between each value and the mean, sum of values
    std::vector <double> sqDiff;                //vector to hold squared difference between each value and the mean

    for (int i = 0; i < stats.size(); i++)
    {
        meanDiff = pow((stats[i] - mean), 2);
        //square difference between each value and mean
        sqDiff.push_back(meanDiff);
        //store values to vector
    }

    for (int i = 0; i < sqDiff.size(); i++)
    {
        total += sqDiff[i];
        //find total of vector
    }

    sd = sqrt(total/sqDiff.size());
    //find square root of mean of squared differences and set to standard deviation
    return sd;
    //return standard deviation
}
