// assn01.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "AdjMatrixGraph editing.hpp"
template <class N>

int main()
{
    AdjMatrixGraph<N> testAMG;

    testAMG.addNode(0, 16);
    testAMG.addNode(1, 13);
    testAMG.addNode(2, 54);
    testAMG.addNode(3, 17);

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