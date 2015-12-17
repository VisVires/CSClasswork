/*************************************************************************************************************************************************************************************
 *
 * Author: William George
 * Date Created: 11/26/2014
 * Date Last Modified: 12/1/2014
 * File Name: geom.cpp
 *
 * Overview: This program uses classes and methods to display the relationship 
 * of two points along a single line. The user will input their two points or 
 * coordinates and the program will return the length and slope of the line 
 * between the two points.
 *
 *
 * Inputs: This program will only take two inputs from the user, one for the
 * first coordinate and again for the second coordinate. 
 *
 * 	Input Example: Please enter the address of your x coordinate for your
 * 	first point: 4
 * 	Please enter the y address for your first point: 5
 *
 * Outputs: This program will then process theses points and output the 
 * distance between the two and the slope of the line formed between the two
 * points.
 *
 * **********************************************************************************************************************************************************************************/

#include <iostream>
#include <cmath>

using namespace std;

class Point
{
	
	private:
	//member variables
		double xCoord;
		double yCoord;
	
	public:
		//member functions
		
		Point(double x = 0, double y = 0)
		//constructor
		{
			xCoord = x;
			yCoord = y;
		}
		~Point(){}
		//destructor 
		void setX(const double x)
		//x mutator
		{
			xCoord = x;
		}

		double getX()
		//x accessor
		{
			return xCoord;
		}
		
		void setY(const double y)
		//y mutator
		{
			yCoord = y;
		}

		double getY()
		//y accessor
		{
			return yCoord;
		}
		
		double distanceTo(Point &point2)
		//distance function using pythagorean theorem
		{
			double xDist, yDist;			
        		xDist = xCoord - point2.getX();
        		yDist = yCoord - point2.getY();
        		return sqrt((xDist*xDist) + (yDist*yDist));
		}
};

class LineSegment
{
	private:
		//member variables
		Point begin;
		Point end;
	public:
		//member functions
		LineSegment(){}
		//default constructor					
		LineSegment(Point p1, Point p2)
		
		{
			begin = p1;
			end = p2;
		}

		Point getBegin()
		//acccessor begin
		{return begin;}
	
		Point getEnd()
		//accessor end
		{return end;}
		
		double length(Point begin, Point end)
		//length function using distance function
		{
			double lineLength;	//variable for line length
			lineLength = begin.distanceTo(end);
			return lineLength;
		}

		double slope (Point begin, Point end)
		//slope function using difference in y/ difference in x
		{
			double lineSlope, xDiff, yDiff;	//variables for x and y differences and slope
			
			xDiff = end.getX() - begin.getX();
			yDiff = end.getY() - begin.getY();
			lineSlope = yDiff / xDiff;
			return lineSlope;
		}
};


int main()
{
	double x1, x2, y1, y2;	//coordinate variables 
	double lineSlope; 	//slope variable 
	double lineLength;	//length variable
	char again;		//play again character

	Point one(x1,y1);	//sets point one class object
	Point two(x2,y2);	//sets point two class object
	LineSegment line;	//sets LineSegment class object
	
	do
	{
		cout << "Enter the coordinates for the first point" << endl;

		cout << "X Coordinate: ";
		//sets x coord of point one
		while (!(cin >> x1))
		{
			cout << "Invalid coordinate, please reinput: " << endl;
			cin.clear();
			cin.ignore(100, '\n');
		}
		one.setX(x1);

        	cout << "Y Coordinate: ";
		//sets y coord of point one
		while (!(cin >> y1))
                {
                        cout << "Invalid coordinate, please reinput: " << endl;
                        cin.clear();
                        cin.ignore(100, '\n');
                }

		one.setY(y1);

		cout << "Enter the coordinates for the second point" << endl;
        	
		cout << "X Coordinate: ";
		//sets x coord of point two
        	while (!(cin >> x2))
                {
                        cout << "Invalid coordinate, please reinput: " << endl;
                        cin.clear();
                        cin.ignore(100, '\n');
                }
		two.setX(x2);
	
        	cout << "Y Coordinate: ";
        	while (!(cin >> y2))
                {
                        cout << "Invalid coordinate, please reinput: " << endl;
                        cin.clear();
                        cin.ignore(100, '\n');
                }
		two.setY(y2);
		//sets y of point two

		//finds line length using point objects
		lineLength = line.length(one, two);

		//finds line slope using point objects
		lineSlope = line.slope(one,two);
		cout << "\nThe length of the line is " << lineLength << endl;

		if (isinf(lineSlope))
		//checks if slope is vertical
			cout << "The line is vertical" << endl;
		else
			cout << "The slope of the line is " << lineSlope << endl;

		
		cout << "Enter Y to enter new Coordinates: ";
		//play again
		cin >> again;

	}
	//if again is y or Y ask for new coordinates
	while (again == 'Y' || again == 'y');

return 0;
}

