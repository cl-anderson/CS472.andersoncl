//
//  File:   Graph.hpp
//  Author: Your Glorious Instructor
//  Purpose:
//  Abstract base class (pure virtual class) for Graphs
//
#pragma once
#include <vector>
#include <utility>
#include <functional>
template <class N>
class Graph {
public:
    // Default constuctor, create empty
    Graph() {};
    Graph(std::vector<N> nodes, std::vector<std::pair<N, N>> edges) {};
    virtual ~Graph() {};
    
    virtual bool adjacent(N x, N y);
    virtual std::vector<N> neighbors(N x);
    virtual void addNode(N x);
    virtual void addEdge(N x, N y);
    virtual void deleteEdge(N x, N y);
    // Traversals
    virtual void dfs(N startNode, std::function<void(N)> visit);
    virtual void bfs(N startNode, std::function<void(N)> visit);
};

