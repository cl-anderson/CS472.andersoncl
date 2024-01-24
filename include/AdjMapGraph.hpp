//
//  File:   AdjListGraph.hpp
//  Author: Your Glorious Instructor, cl-anderson
//  Purpose:
//  Implementation of the adjacency list implementation of the graph ADT
//

#include "Graph.hpp"
#include <map>
#include <vector>
#include <list>
#include <deque>
#include <algorithm>
#include <stack>
#include <queue>
#include <functional>
#include <unordered_map>

using namespace std;

template <class N>
class AdjMapGraph: public Graph<N>  {
private:
    using Edges = std::unordered_map<int, N>;
    map<N, Edges > vertexMap;
public:
    // Default constuctor, create empty
    AdjMapGraph() : Graph<N>() { };
    
    // Get the vertex map from the Graph we're copying
    AdjMapGraph(const AdjMapGraph& other) : Graph<N>()
    {
        vertexMap = other->vertexMap;
    }
    
    // Don't forget to overload the assignment operator
    AdjMapGraph& operator= (const AdjMapGraph&source)
    {
        vertexMap = source->vertexMap;
        return *this;
    }
    
    // Add the nodes in the list to graph
    AdjMapGraph(vector<N> newNodes) :
    Graph<N>(newNodes)
    {
        for (auto it = newNodes.begin();
             it < newNodes.end();
             ++it)
        {
            N node = *it;
            vertexMap[node];
        }
    }
    
    
    // Clean up behind ourselves
    ~AdjMapGraph() { }
    
    virtual bool adjacent(N x, N y){
        Edges edges = vertexMap.at(x);
        pair<N,N> *searchEdge = new pair<N,N>(x,y);
        typename Edges::const_iterator begin = edges.begin();
        typename Edges::const_iterator end = edges.end();
        auto pos = std::find_if(begin,end,
                                [&](pair<N,N> const &b) {
            bool match =  (b.first == searchEdge->first
                           && b.second == searchEdge->second);
            return match;
        });
        bool match = false;
        if (pos != end) { match = true; }
        return (match);
    }
    
    virtual vector<N> neighbors(N x) {
        vector<N> *nodes = new vector<N>();
        Edges edges = vertexMap.at(x);
        for (typename Edges :: const_iterator it = edges.begin(); it != edges.end(); it++) {
            pair<N,N> e = *it;
            nodes->push_back(e.second);
        }
        return *nodes;
    }
    
    virtual void addNode(N node){
        Edges * newEdgeMap = new Edges();
        vertexMap[node] = *newEdgeMap;
    }
    
    virtual void addEdge(char key, N x, N y){
        pair<N,N> forwardEdge = make_pair(x,y);
        pair<N,N> backwardEdge = make_pair(y,x);
        Edges edgeMap= vertexMap[x];
        vertexMap[x][key] = forwardEdge;
        vertexMap[y][key] = backwardEdge;
    }
    
    virtual void addInfo(N x, N info) {
        infoStorage[x] = info;
    }

    N getInfo(N x) {
        N info = infoStorage[x];
        return info;
    }

    virtual void deleteEdge(char key, N x, N y){
        vertexMap[x].erase(key);
        vertexMap[y].erase(key);
    }
    
    // Traversals
    void dfs(N startNode, std::function<void(N)> visit) {
        map<N, bool> visited;
        stack<N> s;
        for (auto v : vertexMap) {
            visited[v.first] = false;
        }
        s.push(startNode);
        while (!s.empty()) {
            N currentNode = s.top();
            s.pop();
            bool beenVisited = visited[currentNode];
            if (!beenVisited) {
                visit(currentNode);
                visited[currentNode] = true;
            }
            vector<N> neighVec = neighbors(currentNode);
            for (auto neighbor: neighVec ) {
                if (!visited[neighbor]) { s.push(neighbor); }
            }
        }
    }
    
    void bfs(N startNode, std::function<void(N)> visit) {
        map<N, bool> visited;
        for (auto v: vertexMap) {
            visited[v.first] = false;
        }
        queue<N> q;
        q.push(startNode);
        while (!q.empty()) {
            N currentNode = q.front();
            q.pop();
            bool beenVisited = visited[currentNode];
            if (!beenVisited) {
                visit(currentNode);
                visited[currentNode] = true;
            }
            vector<N> neighVec = neighbors(currentNode);
            for (auto neighbor: neighVec) {
                if (!visited[neighbor]) { q.push(neighbor); }
            }
        }
    }
};
