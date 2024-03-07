// assn05.03.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
// sources: https://www.boost.org/doc/libs/1_37_0/libs/graph/doc/adjacency_list.html, 
//          https://stackoverflow.com/questions/3100146/adding-custom-vertices-to-a-boost-graph,
//          https://www.boost.org/doc/libs/1_39_0/libs/graph/example/undirected.cpp,
//          https://www.boost.org/doc/libs/1_79_0/libs/graph/doc/graph_concepts.html,
//          https://www.geeksforgeeks.org/prims-minimum-spanning-tree-mst-greedy-algo-5/

#include <iostream>
#include <utility>
#include <vector>
#include <boost/config.hpp>
#include <boost/graph/graph_traits.hpp>
#include <boost/graph/graph_utility.hpp>
#include <boost/graph/adjacency_list.hpp>
//#include <boost/type_traits/is_function.hpp>
using namespace boost;
template <typename T>

boost::adjacency_list<T> customPrim(adjacency_list<T> graph);
template <typename T>
int main()
{
    struct edge { T exchangeRate; };
    struct vertex { char vert; };
    using graph_t = adjacency_list<listS, vecS, directedS, vertex, edge >;
    using vertex_t = graph_traits<graph_t>::vertex_descriptor;
    using edge_t = graph_traits<graph_t>::edge_descriptor;
    
    boost::adjacency_list<std::char> testGraph;
    vertex_t A = add_vertex(testGraph);
    vertex_t B = add_vertex(testGraph);
    vertex_t C = add_vertex(testGraph);
    vertex_t D = add_vertex(testGraph);

    add_edge(testGraph, A, B, edge(1));
    add_edge(testGraph, B, C, edge(5));
    add_edge(testGraph, C, D, edge(4));
    add_edge(testGraph, D, A, edge(3));
    add_edge(testGraph, B, D, edge(10));
    add_edge(testGraph, B, A, edge(7));

    return 0;
}

template <typename T>
boost::adjacency_list<T> customPrim(adjacency_list<T> graph)
{
    adjacency_list<T> mstTree;
    vertex_t start = graph
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
    std::cout << "Edge Weight\n";
    for (int i = 1; i < V; i++)
    {
        std::cout << parent[i] << " : " << i << " \t"
            << graph[i][parent[i]] << " \n";
    }
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
    for (int i = 0; i < V; i++) { key[i] = INT_MAX, mstSet[i] = false; }
    key[0] = 0;

    parent[0] = -1;

    for (int count = 0; count < V - 1; count++) 
    {
        int u = minKey(key, mstSet);
        mstSet[u] = true;
        for (int v = 0; v < V; v++)
        {
            if (graph[u][v] && mstSet[v] == false
                && graph[u][v] < key[v])
                parent[v] = u, key[v] = graph[u][v];
        }
    }
    printMST(parent, graph);
}