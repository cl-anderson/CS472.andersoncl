// AdjListGraph.cpp : This file contains the 'main' function. Program execution begins and ends there.
// author: chloe anderson, modified from the CS372 data structures class Graph assignment
// sources: personal CS372 repository
//				https://www.softwaretestinghelp.com/graph-implementation-cpp/#Graph_Representation
//			   https://www.programiz.com/dsa/graph-adjacency-list
//			   https://codeforwin.org/c-programming/c-program-to-copy-one-array-to-another-using-pointers
//			   https://www.tutorialspoint.com/cplusplus-program-to-implement-adjacency-matrix
//			   https://www.geeksforgeeks.org/c-program-to-implement-adjacency-matrix-of-a-given-graph/
//			   https://www.educative.io/courses/graph-algorithms-coding-interviews-c-plus-plus/7A99xpz4JMQ 

#include <iostream>
#include <vector>
#include <algorithm>
#include <stack>

int search(int value, std::stack<int> stuff)
{
	std::stack<int> stuffcopy = stuff;
	int tracker = 0;
	while (stuffcopy.empty() == false && tracker == 0) 
	{
		if (stuff.top() == value) { tracker++; }
		else { stuffcopy.pop(); }
	}
	return tracker;
}

template <typename ValueType>
class AdjacencyListGraph {
	std::stack<int> IDstack;
	struct node {
		int vertex = 0;
		std::vector<int> neighborList;
	};
private:
	std::vector<node> adjList; // hiding details of format from user
public:
	AdjacencyListGraph() {}

	bool adjacent(int x, int y) {
		for (auto i : x.neighborList)
		{
			if (x.neighborList[i] == y) { return true; }
		}
		return false;
	}

	std::vector<int> neighbors(node value)
	{
		std::vector<int> list;
		for (auto i : value.neighborList)
		{
			list.push_back(value.neighborList[i]);
		}
		return list;
	}

	void addNode(int value)
	{
		if (search(value, IDstack) == 1)
		{
			IDstack.push(value);
			node newNode;
			newNode.vertex = value;
			adjList.push_back(newNode);
		}
	}

	void addEdge(int source, int dest) { // assuming this is an undirected list, the edge connection goes both ways.
		int counter = 0;
		int sourcePosition = -1;
		int destPosition = -1;
		for (auto x : adjList)
		{
			if (adjList[counter].vertex == source)
			{
				sourcePosition = counter;
			}
			if (adjList[counter].vertex == dest)
			{
				destPosition = counter;
			}
			counter++;
		}
		adjList[sourcePosition].neighborList.push_back(dest);
		adjList[destPosition].neighborList.push_back(source);
	}

	void deleteEdge(int source, int dest) {
		int counter = 0;
		int sourcePosition = -1;
		int destPosition = -1;
		for (auto x : adjList)
		{
			if (adjList[counter].vertex == source)
			{
				sourcePosition = counter;
			}
			if (adjList[counter].vertex == dest)
			{
				destPosition = counter;
			}
			counter++;
		}
		std::remove(adjList[sourcePosition].neighborList.begin(), adjList[sourcePosition].neighborList.end(), dest);
		std::remove(adjList[destPosition].neighborList.begin(), adjList[destPosition].neighborList.end(), source);
	}

	void deleteNode(int value)
	{
		int counter = 0;
		int pos = -1;
		for (auto x : adjList)
		{
			if (adjList[counter].vertex == value)
			{
				pos = counter;
			}
			counter++;
		}
		std::remove(adjList.begin(), adjList.end(), pos);
	}
};;