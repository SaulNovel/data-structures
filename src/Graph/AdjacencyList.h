#ifndef GRAPH_ADJACENCY_LIST
#define GRAPH_ADJACENCY_LIST

#include <iostream>
#include <string>
#include <list>
#include <sstream>

namespace Graph_AdjacencyList
{

using std::list;
using std::ostream;

class Graph
{
    list<int>* l;
    int nVertex;

public:

    Graph(int nVertex) 
    : nVertex(nVertex) {
        l = new list<int>[nVertex];
    }
    
    void addEdge(int i, int j, bool undirected = true) {
        l[i].push_back(j);
        if (undirected) {
            l[j].push_back(i);
        }    
    }
    
    const list<int>* get() { return l; }
    
    const int size() const { return nVertex; }
    
    friend ostream& operator<<(ostream& os, Graph& obj) {
        // Iterate over all rows
        auto adjList = obj.get();
        for (int i=0; i<obj.size(); i++) {
            os << i << " -> ";
            // Every element of ith linked list
            for (auto& node : adjList[i]) {
                os << node << ", ";
            }
            os << std::endl;
        }

        return os;
    }
    
    ~Graph() {
        delete[] l;
    }
};

void test() {
    Graph graph(6);
    
    graph.addEdge(0,1);
    graph.addEdge(0,4);
    graph.addEdge(2,1);
    graph.addEdge(3,4);
    graph.addEdge(4,5);
    graph.addEdge(2,3);
    graph.addEdge(3,5);
    
    std::cout << graph << std::endl;
}


}

#endif