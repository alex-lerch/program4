// Implementation of Maze class
// By Mary Elaine Califf and

#include "Maze.h"
#include "DisjointSet.h"
using namespace std;

#define LEFT 0
#define DOWN 1
#define RIGHT 2
#define UP 3

Maze::Maze(int rows, int cols)
{
    numRows = rows;
    numColumns = cols;
    int numCells = rows * cols;
    mazeWalls = new CellWalls[numCells];
    mazeWalls[numCells - 1].east = false;
}

Maze &Maze::operator=(const Maze &rhs)
{
    if (this != &rhs)
    {
        delete [] mazeWalls;
        this->copy(rhs);
    }
    return *this;
}

void Maze::generateMaze()
{
    int numCells = numRows * numColumns;
    DisjointSet mySet(numCells);
    bool mazeComplete = false;

    // find random cell
    cell currentCell = findRandomCell();

    // randomly select a neighbor of currentCell
    direction directionFromCurrentCell = findDirection();

    // gets the correct neighbor of the currentCell
    cell neighbor = getNeighbor(currentCell, directionFromCurrentCell);

    // todo: implement removing walls without worrying about doing it multiple times or completing the maze, git commit once achieved

    // asl debug
    std::cout << "cell chosen: " << currentCell << "\ndirection chosen: " << directionFromCurrentCell << "\nchosen neighbor: " << neighbor << std::endl;
}

void Maze::print(ostream &outputStream)
{
    // print the top row of walls
    for (int i = 0; i < numColumns; i++)
        outputStream << " _";
    outputStream << '\n';
    for (int i = 0; i < numRows; i++)
    {
        int cellbase = i * numColumns;
        // print west wall (except at entrance)
        if (i == 0)
            outputStream << ' ';
        else
            outputStream << '|';
        for (int j = 0; j < numColumns; j++)
        {
            if (mazeWalls[cellbase + j].south)
                outputStream << '_';
            else
                outputStream << ' ';
            if (mazeWalls[cellbase + j].east)
                outputStream << '|';
            else
                outputStream << ' ';
        }
        outputStream << '\n';
    }
}

void Maze::copy(const Maze &orig)
{
    this->numRows = orig.numRows;
    this->numColumns = orig.numColumns;
    int numCells = numRows * numColumns;
    mazeWalls = new CellWalls[numCells];
    for (int i = 0; i < numCells; i++)
    {
        this->mazeWalls[i] = orig.mazeWalls[i];
    }
}


// find a random cell within the maze
int Maze::findRandomCell() {
    return rand() % (numColumns * numRows);
}


// find a direction
int Maze::findDirection() {
    return rand() % 4;
}


// gets a valid neighbor
cell Maze::getNeighbor(cell currentCell, direction directionFromCurrentCell) {
    cell leftCell = currentCell - 1;
    cell rightCell = currentCell + 1;
    cell downCell = currentCell + numColumns;
    cell upCell = currentCell - numColumns;
    int numCells = numColumns * numRows;
    switch(directionFromCurrentCell) {
        case LEFT:
            if (isBeginningOfRow(currentCell)) {
                // return right neighbor
                return rightCell;
            }
            else {
                return leftCell;
            }
            break;

        case DOWN:
            if (downCell > (numCells - 1)) {
                return upCell;
            }
            else {
                return downCell;
            }
            break;

        case RIGHT:
            if (isBeginningOfRow(rightCell)) {
                // return left neighbor
                return leftCell;
            }
            else {
                return rightCell;
            }
            break;

        case UP:
            if (upCell < 0) {
                return downCell;
            }
            else {
                return upCell;
            }
            break;
    }
}

// checks for whether the cell is the first one in the row. true if it is, false otherwise
bool Maze::isBeginningOfRow(cell currentCell) {
    return ( (currentCell % numColumns) == 0 );
}