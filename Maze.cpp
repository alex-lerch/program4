// Implementation of Maze class
// By Mary Elaine Califf and Alex Lerch

#include "Maze.h"
#include "DisjointSet.h"
using namespace std;

// define the directions we could take within the maze
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


// generates the maze by randomly knocking down walls
void Maze::generateMaze()
{
    // calculate the number of cells in the maze
    int numCells = numRows * numColumns;

    // create the disjoint set to keep track of when all cells are connected
    DisjointSet mySet(numCells);

    // used to help determine when the maze is completed
    bool mazeComplete = false;

    while (!mazeComplete) { // while the maze has not yet been completed
        // find random cell
        cell currentCell = findRandomCell();

        // randomly find a direction that will be used to help find a neighbor of currentCell
        direction directionFromCurrentCell = findRandomDirection();

        // gets the correct neighbor of the currentCell and updates directionFromCurrentCell
        cell neighbor = getNeighbor(currentCell, directionFromCurrentCell);

        // if the two cells are not in the same set then remove wall between them and then union them then check for maze completed
        if (! (mySet.find(currentCell) == mySet.find(neighbor)) ) {

            // remove wall between two chosen cells
            removeSharedWall(currentCell, directionFromCurrentCell, neighbor);

            // union cells in the disjoint set then update mazeComplete if the maze has been completed
            if (mySet.doUnion(currentCell, neighbor)) { // if the maze has been completed
                mazeComplete = true;
            }

        }
    }
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


// find a random direction
int Maze::findRandomDirection() {
    return rand() % 4;
}


// gets a valid neighbor of currentCell and updates the directionFromCurrentCell if necessary
cell Maze::getNeighbor(cell currentCell, direction &directionFromCurrentCell) {

    // define used variables
    cell leftCell = currentCell - 1;
    cell rightCell = currentCell + 1;
    cell downCell = currentCell + numColumns;
    cell upCell = currentCell - numColumns;
    int numCells = numColumns * numRows;

    // select the neighbor based on the randomly selected direction
    switch(directionFromCurrentCell) {

        // if the direction is left
        case LEFT:
            if (isBeginningOfRow(currentCell)) {
                // update direction
                directionFromCurrentCell = RIGHT;
                // return right neighbor
                return rightCell;
            }
            else {
                return leftCell;
            }
            break;

        // if the direction is down
        case DOWN:
            if (downCell > (numCells - 1)) { // if the cell below the currentCell is not part of the maze
                // update direction
                directionFromCurrentCell = UP;
                // return the correct neighbor
                return upCell;
            }
            else {
                return downCell;
            }
            break;

        // if the direction is right
        case RIGHT:
            if (isBeginningOfRow(rightCell)) {
                // update direction
                directionFromCurrentCell = LEFT;
                // return left neighbor
                return leftCell;
            }
            else {
                return rightCell;
            }
            break;

        // if the direction is up
        case UP:
            if (upCell < 0) { // if the cell above currentCell is not part of the maze
                // update direction
                directionFromCurrentCell = DOWN;
                // return correct neighbor
                return downCell;
            }
            else {
                return upCell;
            }
            break;
    }
    
    // return invalid number
    return -1;
}

// checks for whether the cell is the first one in the row. true if it is, false otherwise
bool Maze::isBeginningOfRow(cell currentCell) {
    return ( (currentCell % numColumns) == 0 );
}


// removes the shared wall between currentCell and neighbor
void Maze::removeSharedWall(cell currentCell, direction directionFromCurrentCell, cell neighbor) {

    switch(directionFromCurrentCell) {
        // to remove wall to the left of currentCell, remove neighbor's east wall
        case LEFT:
            mazeWalls[neighbor].east = false;
            break;

        // remove currentCell's south wall
        case DOWN:
            mazeWalls[currentCell].south = false;
            break;

        // remove currentCell's east wall
        case RIGHT:
            mazeWalls[currentCell].east = false;
            break;

        // to remove wall above currentCell, remove neighbor's south wall
        case UP:
            mazeWalls[neighbor].south = false;
            break;
    }
}