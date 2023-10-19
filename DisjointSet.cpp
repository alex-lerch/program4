// DisjointSet implementation using union by size and path compression
// By Mary Elaine Califf and

#include "DisjointSet.h"
#include <iostream>

DisjointSet::DisjointSet(int numObjects)
{
    //to do
}

//recursive method to find the item -- does path compression on the way out of the recursion
int DisjointSet::find(int objectIndex)
{
    // to do -- see assignment instructions for details
}

bool DisjointSet::doUnion(int objIndex1, int objIndex2)
{
    // to do -- see assignment instructions for details
}

void DisjointSet::printArrayValues(std::ostream &outputStream)
{
    for (int i = 0; i < numValues; i++)
    {
        outputStream << theArray[i] << " ";
    }
    outputStream << std::endl;
}
