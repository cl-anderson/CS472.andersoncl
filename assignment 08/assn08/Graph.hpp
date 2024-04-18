#include <vector>
#include <algorithm>
// references: https://www.softwaretestinghelp.com/graph-implementation-cpp/#Graph_Representation
//			   https://www.programiz.com/dsa/graph-adjacency-list
//			   https://codeforwin.org/c-programming/c-program-to-copy-one-array-to-another-using-pointers
//			   https://www.tutorialspoint.com/cplusplus-program-to-implement-adjacency-matrix
//			   https://www.geeksforgeeks.org/c-program-to-implement-adjacency-matrix-of-a-given-graph/
//			   https://www.educative.io/courses/graph-algorithms-coding-interviews-c-plus-plus/7A99xpz4JMQ 
template <typename ValueType>
class Graph {
public:
	virtual ~Graph();

	// is there a node from x to y
	virtual bool adjacent(ValueType x, ValueType y) = 0;

	// Return a vector of neighbor nodes  
	virtual std::vector<ValueType> neighbors(ValueType x) = 0;

	// add an edge from source, to dest
	// add dest if it isn't already in graph
	virtual void addEdge(ValueType source, ValueType dest) = 0;

	//Add x to graph
	virtual void addNode(ValueType x) = 0;

	virtual void deleteEdge(ValueType source, ValueType dest) = 0;
	virtual void deleteNode(ValueType node) = 0;
};

template <typename ValueType>
class AdjacencyListGraph : virtual public Graph<ValueType>{
	struct node {
		//int vertex;
		std::vector<node> neighborList;
	};
private:
	std::vector<node> adjList; // hiding details of format from user
public:
	AdjacencyListGraph() {}

	bool adjacent(ValueType x, ValueType y) {
		for (auto i : x.neighborList)
		{
			if (x.neighborList[i] == y) { return true; }
		}
		return false;
	}

	std::vector<ValueType> neighbors(ValueType value)
	{
		std::vector<ValueType> list;
		for (auto i : value.neighborList)
		{
			list.push_back(value.neighborList[i]);
		}
		return list;
	}

	void addNode(ValueType value)
	{
		node newNode;
		adjList[value] = newNode;
	}

	void addEdge(ValueType source, ValueType dest) { // assuming this is an undirected list, the edge connection goes both ways.
		source.neighborList.push_back(dest);
		dest.neighborList.push_back(source);
	}

	void deleteEdge(ValueType source, ValueType dest) {
		source.neighborList.remove(source.neighborList.begin(), source.neighborList.end(), dest);
		dest.neighborList.remove(dest.neighborList.begin(), dest.neighborList.end(), source);
	}

	void deleteNode(ValueType value)
	{
		// remove this node from all neighbor lists, effectively removing it from
		// the graph. doing it this way preserves the values of other nodes
		for (auto i : adjList)
		{
			int temp = value;
			std::cout << adjList[i];
			//adjList[i].neighborList.removeif(temp);
		}
	}
};

template <typename ValueType>
class AdjacencyMatrixGraph : virtual public Graph<ValueType>{
	struct node {
		ValueType value;
	};
private:
	int size;
	node arr[5][5]; // hiding details of format from user
	node *matrixPtr = &arr; // using a pointer to an array so we can more easily add and delete nodes
public:
	AdjacencyMatrixGraph() {} // default constructor
	AdjacencyMatrixGraph(int x) // constructor with size
	{
		size = x;
		for (int i = 0; i < size; ++i)
		{
			for (int j = 0; j < size; ++j)
			{
				matrixPtr[i][j] = 0;
			}
		}
	}
	~AdjacencyMatrixGraph() {}

	bool adjacent(ValueType x, ValueType y)
	{
		if (matrixPtr[x][y] == 1) { return true; }
	}

	std::vector<ValueType> neighbors(ValueType value)
	{
		std::vector<ValueType> neighborVec;
		for (int i = 1; i < size; i++)
		{ 
			if (matrixPtr[value][i] == 1) { neighborVec.push_back[i]; }
		}
		return neighborVec;
	}

	void addEdge(ValueType source, ValueType dest)
	{
		matrixPtr[source][dest] = 1;
	}

	void addNode(ValueType x) // to add a node we'll need to make a new, bigger array and set the ptr to it
	{
		node newArray[size + 1][size + 1];
		for (int i = 0; i < size; ++i)
		{
			for (int j = 0; j < size; ++j)
			{
				if (matrixPtr[i][j] == 1)
				{
					newArray[i][j] = 1;
				}
				newArray[i][j] = 0;
			}
		}
		matrixPtr = newArray;
	}

	void deleteEdge(ValueType source, ValueType dest)
	{
		matrixPtr[source][dest] = 0;
	}

	void deleteNode(ValueType x)
	{
		node newArray[size - 1][size - 1];
		for (int i = 0; i < size - 1; ++i)
		{
			for (int j = 0; j < size - 1; ++j)
			{
				if (matrixPtr[i][j] == 1)
				{
					newArray[i][j] = 1;
				}
				newArray[i][j] = 0;
			}
		}
		matrixPtr = newArray;
	}
};