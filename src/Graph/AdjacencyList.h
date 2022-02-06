#ifndef GRAPH_ADJACENCY_LIST
#define GRAPH_ADJACENCY_LIST

#include <iostream>
#include <string>
#include <list>
#include <sstream>
#include <queue>
#include <vector>
#include <unordered_set>
#include <algorithm>

using std::list;
using std::ostream;
using std::queue;
using std::vector;
using std::unordered_set;

namespace Graph_AdjacencyList
{

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

    const vector<int> BFS(int source)
    {
        vector<int> result;
        vector<bool> seen(7, false);

        queue<int> nodes;
        nodes.push(source);
        seen[source] = true;

        while (!nodes.empty()) {
            int current = nodes.front();
            nodes.pop();

            result.push_back(current);

            // add all (not seen) connections from current node
            for (int node : l[current]) {
                if (!seen[node]) {
                    nodes.push(node);
                    seen[node] = true;
                }
            }
        }

        return result;
    }

    const vector<int> distances(int source)
    {
        // index -> node
        // value -> distance
        vector<int> dist(7, 0);

        vector<bool> seen(7, false);

        queue<int> nodes;
        nodes.push(source);
        seen[source] = true;

        while (!nodes.empty()) {

            int current = nodes.front();
            nodes.pop();

            for (int node : l[current]) {
                if (!seen[node]) {
                    nodes.push(node);
                    dist[node] = dist[current] + 1;
                    seen[node] = true;
                }
            }
        }

        return dist;
    }

    const vector<int> path(int source, int target) {
        // index -> node
        // value -> distance
        vector<int> dist(7, 0);
        vector<int> parent(7, -1);

        vector<bool> seen(7, false);

        queue<int> nodes;
        nodes.push(source);
        seen[source] = true;
        parent[source] = source;

        while (!nodes.empty()) {

            int current = nodes.front();
            nodes.pop();

            for (int node : l[current]) {
                if (!seen[node]) {
                    nodes.push(node);
                    parent[node] = current;
                    dist[node] = dist[current] + 1;
                    seen[node] = true;
                }
            }
        }

        vector<int> path;
        if (target != -1) {
            int temp = target;
            path.push_back(temp);
            while (temp != source) {
                temp = parent[temp];
                if (temp != -1) {
                    path.push_back(temp);
                    std::cout << "temp: " << temp << std::endl;
                }
            }
        }
        std::reverse(path.begin(), path.end());

        return path;
    }
    
    void DFS(vector<int>& out, unordered_set<int>& seen, int current) {
        seen.insert(current);
        
        out.push_back(current);
        for (int node : l[current]) {
            if (!seen.count(node)) {
                DFS(out, seen, node);
            }
        }
    }

    vector<int> DFS(int source) {
        vector<int> result;
        unordered_set<int> seen;
        
        DFS(result, seen, source);

        return result;
    }

    bool backEdge(int current, unordered_set<int>& seen, unordered_set<int>& localStack) {
    
        // Node seen and on stack
        seen.insert(current);
        localStack.insert(current);
    
        for (int node : l[current]) {
        
            // Immediate Back edge
            if (localStack.count(node)) {
                return true;
            }
        
            if (!seen.count(node)) {
                if (backEdge(node, seen, localStack)) {
                    return true;
                }   
            }
        }
    
        // Take current out from stack
        localStack.erase(current);
    
        return false;
    }

    // TODO: separate logic directed/unircted graph cycle detection
    bool cycle() {
        unordered_set<int> seen;
        unordered_set<int> localStack;
    
        return backEdge(l->front(), seen, localStack);
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

void test_traversals() {
    Graph graph(7);
    graph.addEdge(1,2);  
    graph.addEdge(1,0);  
    graph.addEdge(2,3);  
    graph.addEdge(0,4);  
    graph.addEdge(3,4);  
    graph.addEdge(3,5);  
    graph.addEdge(4,5);  
    graph.addEdge(5,6);  

    std::cout << graph << std::endl;

    const auto result_BFS = graph.BFS(graph.get()[0].front());
    std::cout << "BFS -> ";
    for (int node : result_BFS) {
        std::cout << node << ", ";
    }
    std::cout << std::endl;

    // BFS is helpful calculating shortest path in undirected graphs
    const auto distances = graph.distances(graph.get()[0].front());
    std::cout << "Shortest distance from node: " << graph.get()[0].front() << ":" << std::endl;
    for (int i=0; i<static_cast<int>(distances.size()); i++) {
        std::cout << " - node " << i << " -> " << distances[i] << std::endl;
    }

    int source = 6;
    int target = 1;
    std::cout << "Path from '" << source << "' to '" << target << "' -> ";
    const auto& path = graph.path(source, target);
    std::cout << "size: " << path.size() << std::endl;
    for (int node : path) {
        std::cout << node << " ";
    }
    std::cout << std::endl;

    std::cout << "DFS -> ";
    const auto result_DFS = graph.DFS(graph.get()[0].front());
    for (int node : result_DFS) {
        std::cout << node << ", ";
    }
    std::cout << std::endl;

}


void test_cycle_directedGraph() {

    Graph graph(6);
    graph.addEdge(1, 2, false);  
    graph.addEdge(2, 3, false);  
    graph.addEdge(0, 1, false);  
    graph.addEdge(0, 4, false);  
    graph.addEdge(0, 5, false);  
    graph.addEdge(5, 4, false);  

    std::cout << "Directed graph (no cycle) contains cycle: " << graph.cycle() << std::endl;

    graph.addEdge(3, 0, false);

    std::cout << "Directed graph (cycle) contains cycle: " << graph.cycle() << std::endl;

}

}

#endif