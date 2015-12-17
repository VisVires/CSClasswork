#ifndef WORLD_H_INCLUDED
#define WORLD_H_INCLUDED

class World
{
    private:
        int x;				//stores users input x coordinate
        int y;				//stores user input y coordinate
        static const int MAXCOL = 85;	//Maximum number of columns
        static const int MAXROW = 27;	//Maximum number of rows
        static const char life = '8';	//Character representing live cells
        static const char death = '.';	//Character representing dead cells

    public:

        char world [MAXROW][MAXCOL];	
        char otherWorld [MAXROW][MAXCOL];
        World();
        void setX(int xCoord);
        void setY(int yCoord);
        void updateWorld();
        void copyWorld();
        void copyCell(int row, int col);
        void lifeOrDeath(int row, int col, int neighbors, int edge);
        int countNeighbors(int row, int col);
	int countEdge(int row, int col);
        void outputWorld();
        void addBlinker();
        void addGlider();
        void addToad();
        void addGun();

};
#endif // WORLD_H_INCLUDED
