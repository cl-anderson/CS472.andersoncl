// assn05.03.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

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