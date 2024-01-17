// assn01.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "AdjMatrixGraph edited.hpp"

int main()
{
	AdjacencyListGraph<int> testGraph;
	for (int i = 0; i <= 5; i++)
	{
		testGraph.addNode(i);
	}

	testGraph.addEdge(5, 4);
	testGraph.addEdge(4, 3);
	testGraph.addEdge(4, 2);

	testGraph.deleteEdge(5, 4);

	return 0;
}