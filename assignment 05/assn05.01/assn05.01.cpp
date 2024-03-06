// assn05.01.cpp : This file contains the 'main' function. Program execution begins and ends there.
// sources: https://www.boost.org/doc/libs/1_37_0/libs/graph/doc/adjacency_list.html, 
//          https://stackoverflow.com/questions/3100146/adding-custom-vertices-to-a-boost-graph,
//          https://www.boost.org/doc/libs/1_39_0/libs/graph/example/undirected.cpp,
//          https://www.boost.org/doc/libs/1_79_0/libs/graph/doc/graph_concepts.html            

#include <iostream>
#include <utility>
#include <vector>
#include <boost/graph/graph_traits.hpp>
#include <boost/graph/adjacency_list.hpp>
#include <boost/config.hpp>
#include <boost/type_traits/is_function.hpp>
template <typename T>
int main()
{
	using namespace boost;
	struct vertex { std::string currency; };
	struct edge { T exchangeRate; };
	using graph_t = adjacency_list<listS, vecS, directedS, vertex, edge >;
	using vertex_t = graph_traits<graph_t>::vertex_descriptor;
	using edge_t = graph_traits<graph_t>::edge_descriptor;
	
	boost::adjacency_list<std::string> exchangeGraph;
	vertex_t USD = add_vertex(exchangeGraph);
	vertex_t EUR = add_vertex(exchangeGraph);
	vertex_t GBP = add_vertex(exchangeGraph);
	vertex_t CAD = add_vertex(exchangeGraph);
	vertex_t JPY = add_vertex(exchangeGraph);

	add_edge(exchangeGraph, USD, EUR, edge(0.92));
	add_edge(exchangeGraph, USD, GBP, edge(0.78));
	add_edge(exchangeGraph, USD, CAD, edge(1.35));
	add_edge(exchangeGraph, USD, JPY, edge(150.35));

	add_edge(exchangeGraph, EUR, USD, edge(1.08));
	add_edge(exchangeGraph, EUR, GBP, edge(0.85));
	add_edge(exchangeGraph, EUR, CAD, edge(1.47));
	add_edge(exchangeGraph, EUR, JPY, edge(163.15));

	add_edge(exchangeGraph, GBP, USD, edge(1.26));
	add_edge(exchangeGraph, GBP, EUR, edge(1.16));
	add_edge(exchangeGraph, GBP, CAD, edge(1.71));
	add_edge(exchangeGraph, GBP, JPY, edge(190.62));

	add_edge(exchangeGraph, CAD, USD, edge(0.73));
	add_edge(exchangeGraph, CAD, EUR, edge(0.67));
	add_edge(exchangeGraph, CAD, GBP, edge(0.58));
	add_edge(exchangeGraph, CAD, JPY, edge(110.18));

	add_edge(exchangeGraph, JPY, USD, edge(0.0066));
	add_edge(exchangeGraph, JPY, EUR, edge(0.0061));
	add_edge(exchangeGraph, JPY, GBP, edge(0.0052));
	add_edge(exchangeGraph, JPY, CAD, edge(0.0090));




	return 0;
}
#define V 5
int minKey(int key[], bool mstSet[])
{
    // Initialize min value
    int min = INT_MAX, min_index;

    for (int v = 0; v < V; v++)
        if (mstSet[v] == false && key[v] < min)
            min = key[v], min_index = v;

    return min_index;
}

// A utility function to print the
// constructed MST stored in parent[]
void printMST(int parent[], int graph[V][V])
{
    std::cout << "Edge \tWeight\n";
    for (int i = 1; i < V; i++)
        std::cout << parent[i] << " - " << i << " \t"
        << graph[i][parent[i]] << " \n";
}

// Function to construct and print MST for
// a graph represented using adjacency
// matrix representation
void primMST(int graph[V][V])
{
    // Array to store constructed MST
    int parent[V];

    // Key values used to pick minimum weight edge in cut
    int key[V];

    // To represent set of vertices included in MST
    bool mstSet[V];

    // Initialize all keys as INFINITE
    for (int i = 0; i < V; i++)
        key[i] = INT_MAX, mstSet[i] = false;

    // Always include first 1st vertex in MST.
    // Make key 0 so that this vertex is picked as first
    // vertex.
    key[0] = 0;

    // First node is always root of MST
    parent[0] = -1;

    // The MST will have V vertices
    for (int count = 0; count < V - 1; count++) {

        // Pick the minimum key vertex from the
        // set of vertices not yet included in MST
        int u = minKey(key, mstSet);

        // Add the picked vertex to the MST Set
        mstSet[u] = true;

        // Update key value and parent index of
        // the adjacent vertices of the picked vertex.
        // Consider only those vertices which are not
        // yet included in MST
        for (int v = 0; v < V; v++)

            // graph[u][v] is non zero only for adjacent
            // vertices of m mstSet[v] is false for vertices
            // not yet included in MST Update the key only
            // if graph[u][v] is smaller than key[v]
            if (graph[u][v] && mstSet[v] == false
                && graph[u][v] < key[v])
                parent[v] = u, key[v] = graph[u][v];
    }

    // Print the constructed MST
    printMST(parent, graph);
}