// Class to generate a random maze using disjoint sets and print it in ASCII format to a file
// By Mary Elaine Califf and Alex Lerch
#ifndef MAZE_H
#define MAZE_H

#include <iostream>
#include <fstream>
using namespace std;

typedef int direction;
typedef int cell;

struct CellWalls
{
    bool south;
    bool east;
    CellWalls(bool startEast = true, bool startSouth = true) : east(startEast), south(startSouth) {}
};

class Maze
{
private:
    CellWalls *mazeWalls; // maze cells
    int numRows;
    int numColumns;

public:
    // constructor
    Maze(int rows, int cols);

    // copy constructor
    Maze(const Maze &orig) { copy(orig); };

    // destructor
    ~Maze() { delete [] mazeWalls; }

    // assignment operator
    Maze &operator=(const Maze &rhs);

    // generates the maze by randomly knocking down walls
    void generateMaze();

    // prints the maze to the specified outputStream
    void print(ostream &outputStream);

private:
    // private helper method to copy the data from another Maze object
    void copy(const Maze &orig);

    // find a random cell within the maze
    cell findRandomCell();

    // find a direction
    direction findDirection();

    // gets a valid neighbor
    cell getNeighbor(cell currentCell, direction directionFromCurrentCell);

    // checks for whether the cell is the first one in the row. true if it is, false otherwise
    bool isBeginningOfRow(cell currentCell);
};

#endif
