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
template <typename T>
using namespace boost;
struct vertex { std::string currency; };
struct edge { T exchangeRate; };
using graph_t = adjacency_list<listS, vecS, directedS, vertex, edge >;
using vertex_t = graph_traits<graph_t>::vertex_descriptor;
using edge_t = graph_traits<graph_t>::edge_descriptor;


int main()
{
    std::cout << "Hello World!\n";
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
