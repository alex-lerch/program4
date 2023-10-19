// program to do a test of the disjoint set class
// By Mary Elaine Califf

#include "DisjointSet.h"
#include <iostream>
using namespace std;

int main()
{
    DisjointSet mySet(16);

    cout << "original array" << endl;
    mySet.printArrayValues(cout);
    cout << endl;

    mySet.doUnion(2, 3);
    mySet.doUnion(4, 5);
    mySet.doUnion(2, 5);

    cout << "after first 3 doUnions " << endl;
    mySet.printArrayValues(cout);
    cout << endl;

    mySet.doUnion(13, 15);
    mySet.doUnion(14, 0);
    mySet.doUnion(1, 7);
    mySet.doUnion(1, 0);
    mySet.doUnion(9, 15);

    cout << "after 9,15" << endl;
    mySet.printArrayValues(cout);
    cout << endl;

    mySet.doUnion(6, 11);
    mySet.doUnion(11, 13);

    cout << "after 11,13" << endl;
    mySet.printArrayValues(cout);
    cout << endl;

    cout << "0 set label: " << mySet.find(0) << endl;
    cout << "11 set label: " << mySet.find(11) << endl;
    cout << "5 set label: " << mySet.find(5) << endl;

    cout << "result of 14,2 "<<mySet.doUnion(14, 2)<<endl;
    cout << "result of 10,12 "<<mySet.doUnion(10, 12)<<endl;
    cout << "result of 8,12 "<<mySet.doUnion(8, 12)<<endl;

    cout << "after 8,12" << endl;
    mySet.printArrayValues(cout);
    cout << endl;

    cout << "result of 5,8 " << mySet.doUnion(5, 8) << endl;
    cout << "result of 15,0 " << mySet.doUnion(15, 0) << endl;

    cout << "\nFinal version" << endl;
    mySet.printArrayValues(cout);
}
