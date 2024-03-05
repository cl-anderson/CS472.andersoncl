// assn05.01.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <utility>
#include <vector>
#include <boost/graph/graph_traits.hpp>
#include <boost/graph/adjacency_list.hpp>
#include <boost/config.hpp>
#include <boost/type_traits/is_function.hpp>

int main()
{
	using namespace boost;
	struct vertex { std::string currency };
	struct edge { double exchangeRate };
	using graph_t = adjacency_list<listS, vecS, undirectedS, vertex, edge >;
	using vertex_t = graph_traits<graph_t>::vertex_descriptor;
	using edge_t = graph_traits<graph_t>::edge_descriptor;
	
	boost::adjacency_list<std::string> exchangeGraph;
	vertex_t t = boost::add_vertex(vertex{"USD"}, exchangeGraph);
	exchangeGraph.add_vertex("EUR");
	exchangeGraph.add_vertex("GBP");
	exchangeGraph.add_vertex("CAD");
	exchangeGraph.add_vertex("JPY");

	exchangeGraph.add_edge()
}