#ifndef GRAPH
#define GRAPH

#include <iostream>

#include <unordered_map>
#include <unordered_set>
#include <set>
#include <vector>

namespace Graph
{

/** 
 *     2 -- 0
 *    / \
 *   1 - 3
 * 
 * - Vertex: Each node of the graph is called a vertex (0, 2, 1, 3)
 * - Edge: The link or path between two vertices is called an edge (0-2, 2-0, 2-1, 2-3, 1-2, 1-3, 3-2, 3-2)
 * - Adjacent node: In a graph, if two nodes are connected by an edge then they are called adjacent nodes or neighbors
 * - Degree of the node: The number of edges that are connected to a particular node is called the degree of the node
 * - Path: The sequence of nodes that we need to follow when we have to travel from one vertex to another in a graph is called the path
 * 
 * Edge list example: (Array states the donnections)
 * - Graph = [[0, 2], [2, 3], [2, 1], [1, 3]]
 * 
 * Adjacent list: (index: node, value:node neighbours)
 * - graph = [[2], [2, 3], [0, 1, 3], [1, 2]]
 * 
 * Adjacent matrix: 
 * - graph = [
 *    0: [0, 0, 1, 0], (node 0 connected to 2)
 *    1: [0, 0, 1, 1], (node 1 connected to 2, 3)
 *    2: [1, 1, 0, 1], (node 2 connected to 0, 1, 3)
 *    3: [0, 1, 1, 0]  (node 3 connected to 1, 2)
 *   ]
*/

/**
 * Implementation of Graph using adjacent list approach:
 * - Undirected
 * - Unweighted
 * 
 * For adjacentcy uses a HasTable
*/
template<class T>
class Graph {

public:

    Graph() :
        numberOfVertices_(0),
        vertices_({}),
        edges_({})
    {}

    void addVertex(const T& vertex) {
        // avoid duplicates
        if (vertices_.count(vertex)) {
            std::cout << "Vertex '" << vertex << "' already exists in the graph" << std::endl;
            return;
        }
        vertices_.insert(vertex);
        numberOfVertices_++;
    }

    void addEdge(const T& vertex1, const T& vertex2) {
        if (!vertices_.count(vertex1)) {
            std::cout << "Cannot add edge, vertex '" << vertex1 << "' does not exists" << std::endl;
            return;
        }
        if (!vertices_.count(vertex2)) {
            std::cout << "Cannot add edge, vertex '" << vertex2 << "' does not exists" << std::endl;
            return;
        }

        edges_[vertex1].push_back(vertex2);
        edges_[vertex2].push_back(vertex1);
    }

    size_t size() {
        return static_cast<size_t>(numberOfVertices_);
    }

    void print() {

        // Keep insertion order
        const std::set<T> vertices(vertices_.begin(), vertices_.end());

        for (const T& vertex : vertices) {
            std::cout << vertex << " --> {";
            const std::vector<T> connections = edges_.at(vertex);

            for (size_t i=0; i<connections.size(); i++) {
                std::cout << connections.at(i) << (((i!=connections.size()-1)) ? ", " : "}\n"); 
            }
        }
    }


private:
    // Keeps a track of the number of nodes in the graph
    int numberOfVertices_;

    std::unordered_set<T> vertices_;

    // Edges
    // - Key: vertex
    // - value: connections
    std::unordered_map<T, std::vector<T>> edges_;
};


}

#endif