// assn01.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "AdjMatrixGraph.hpp"
#include "AdjMapGraph.hpp"
template <class N>

N printInfo(N node);

template <class N>
int main()
{
    std::cout << "Hello World!\n";
    // Improved adjmatrix stuff
    AdjMatrixGraph<int> testAMG;

    testAMG.addNode(0, 0);
    testAMG.addNode(1, 1);
    testAMG.addNode(2, 2);
    testAMG.addNode(3, 3);

    testAMG.addEdge(0, 1);
    testAMG.addEdge(0, 2);
    testAMG.addEdge(0, 3);
    testAMG.addEdge(1, 2);
    testAMG.addEdge(1, 3);
    testAMG.addEdge(2, 3);


    testAMG.deleteEdge(3, 0);

    // Unordered map stuff
    AdjMapGraph<int> testAdjMap;
    testAdjMap.addNode(0);
    testAdjMap.addNode(1);
    testAdjMap.addNode(2);
    testAdjMap.addNode(3);

    testAdjMap.addEdge(0, 1);
    testAdjMap.addEdge(0, 2);
    testAdjMap.addEdge(0, 3);
    testAdjMap.addEdge(1, 2);
    testAdjMap.addEdge(1, 3);
    testAdjMap.addEdge(2, 3);

    return 0;
}

template <class N>
N printInfo(N node)
{
    infoLocation = node->index;

}
// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
