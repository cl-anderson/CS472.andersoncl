// assn01.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "AdjMatrixGraph editing.hpp"
#include "AdjMapGraph.hpp"
template <class N>


int main()
{

    // Improved adjmatrix stuff
    AdjMatrixGraph<N> testAMG;

    testAMG.addNode(0, 1);
    testAMG.addNode(1, 2);
    testAMG.addNode(2, 3);
    testAMG.addNode(3, 4);

    testAMG.addEdge(0, 1);
    testAMG.addEdge(0, 2);
    testAMG.addEdge(0, 3);
    testAMG.addEdge(1, 2);
    testAMG.addEdge(1, 3);
    testAMG.addEdge(2, 3);


    testAMG.deleteEdge(3, 0);

    // Unordered map stuff
    AdjMapGraph<N> testAdjMap;
    testAdjMap.addNode(0, 1);
    testAdjMap.addNode(1, 2);
    testAdjMap.addNode(2, 3);
    testAdjMap.addNode(3, 4);

    testAdjMap.addEdge('A', 0, 1);
    testAdjMap.addEdge('B', 0, 2);
    testAdjMap.addEdge('C', 0, 3);
    testAdjMap.addEdge('D', 1, 2);
    testAdjMap.addEdge('E', 1, 3);
    testAdjMap.addEdge('F', 2, 3);

    testAdjMap.deleteEdge('A', 0, 1);

	return 0;
}