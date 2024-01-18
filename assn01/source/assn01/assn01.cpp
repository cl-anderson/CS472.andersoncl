// assn01.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "AdjMatrixGraph editing.hpp"

int main()
{
    AdjMatrixGraph<int> testAMG;

    testAMG.addNode(0);
    testAMG.addNode(1);
    testAMG.addNode(2);
    testAMG.addNode(3);

    testAMG.addEdge(0, 1);
    testAMG.addEdge(0, 2);
    testAMG.addEdge(0, 3);

    testAMG.addEdge(1, 0);
    testAMG.addEdge(1, 2);
    testAMG.addEdge(1, 3);

    testAMG.addEdge(2, 0);
    testAMG.addEdge(2, 1);
    testAMG.addEdge(2, 3);

    testAMG.addEdge(3, 0);
    testAMG.addEdge(3, 1);
    testAMG.addEdge(3, 2);

    testAMG.deleteEdge(3, 0);

	return 0;
}