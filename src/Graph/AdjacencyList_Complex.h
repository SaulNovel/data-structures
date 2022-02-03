#ifndef GRAPH_ADJACENCY_LIST_COMPLEX
#define GRAPH_ADJACENCY_LIST_COMPLEX

#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>
#include <list>
#include <sstream>

using std::unordered_map;
using std::vector;
using std::list;
using std::ostream;
using std::string;

namespace Graph_AdjacencyList
{

template<typename T>
struct Node
{
    T node;

    // TODO: for weighted graphs it could be a list of pairs
    // - first: node
    // - second: weight
    list<T> connections;
    
    Node(const T& node) : node(node) {} 
};

template<typename T>
class Graph
{
    // All nodes
    unordered_map<T, Node<T>*> adjList;

public:
    Graph(const vector<T>& nodes) {
        for (const T& node : nodes) {
            adjList[node] = new Node<T>(node);
        }
    }
    
    void addEdge(const T& node1, const T& node2, bool undirected=false) {
        adjList[node1]->connections.push_back(node2);
        if (undirected) {
            adjList[node2]->connections.push_back(node1);
        }
    }
    
    unordered_map<T, Node<T>*>& get() {
        return adjList;
    }
    
    friend ostream& operator<<(ostream& os, Graph& obj) {
        for (const auto& item : obj.get()) {
            auto& node = item.first;
            auto& connections = item.second->connections;
            os << node << " -> ";
            for (const auto& node2 : connections) {
                os << node2 << ", ";   
            }
            os << std::endl;
        }
        
        return os;
    }
    
};

void test() {
    
    vector<string> cities = {"Madrid", "London", "Paris", "New York"};
    
    Graph<string> graph(cities);
    graph.addEdge("Madrid", "London");
    graph.addEdge("New York", "London");
    graph.addEdge("Madrid", "Paris");
    graph.addEdge("Paris", "New York");
    
    std::cout << graph << std::endl;    
}

}

#endif