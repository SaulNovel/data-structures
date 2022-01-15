#include <iostream>
#include <string>

#include <TreeExercises/BinarySearchTree.h>

namespace SearchingTest
{

/**
 * In graphs:
 * 1) Breadth First Search: shortest path/closer nodes to our node (space complexity bigger than Depth First Search)
 * - In case of graph, check all nodes directly linked to the starting node
 * - Example: most related item on amazon, closest connections
 * 2) Depth First Search: check to see if it exists\
 * - Solving a maze (which path to take to find exist)
 * - Go as deep as you can and when you find a node where you cannot go anymore go back and find a different path
 * - Does the oath exists?
 * - Uses less memory than Breadth First Search
 * - If the graph is very deep it can get very slow
 * 
 * Dijkstra/Bellman-Ford allows to show the shortest path between 2 nodes in a weighted graph
 * - Bellman-Ford can accomodate negative weights, Dijkstra cannot
 * - Bellman-Ford worst case time complexity O(n^2)
 * - Dijkstra is a bits faster (use over Bellman-Ford when there are no negative weights)
*/ 


//BFS (Breadth First Search) vs DFS (Depth First Search):

// If you know a solution is not far from the root of the tree: BFS
// Correct answer: BFS

// If the tree is very deep and solutions are rare: DFS
// Correct answer: BFS -> (DFS will take more time beacuse the tree is very deep)

// If the tree is very wide: DFS
// Correct answer: DFS (BFS will need too much memory)

// If solutions are frequent but located deep in the tree: DFS
// Correct answer: DFS

// Determining whether a path exists between two nodes: DFS
// Correct answer: DFS

// Finding the shortest path: DFS
// Correct answer: BFS

void test_BreadthFirstSearch() {
    BinarySearchTree::BinarySearchTree<int> tree; 
    tree.insert(9);
    tree.insert(4);
    tree.insert(6);
    tree.insert(20);
    tree.insert(170);
    tree.insert(15);
    tree.insert(1);
    tree.insert(29);
    tree.insert(200);

    tree.print();

    const std::vector<int> data = tree.breadthFirstSearch();
    std::cout << "BreadthFirstSearch -> ";
    for (int value : data) {
        std::cout << value << " ";
    }
    std::cout << std::endl;

    const std::vector<int> data2 = tree.breadthFirstSearchR();
    std::cout << "BreadthFirstSearch recursive -> ";
    for (int value : data2) {
        std::cout << value << " ";
    }
    std::cout << std::endl;

}

void test_DeepFirstSearch() {
    using Tree = BinarySearchTree::BinarySearchTree<int>;

    Tree tree; 
    tree.insert(9);
    tree.insert(4);
    tree.insert(6);
    tree.insert(20);
    tree.insert(170);
    tree.insert(15);
    tree.insert(1);
    tree.insert(29);
    tree.insert(200);
    tree.print();

    {
    const std::vector<int> data = tree.deepFirstSearch(Tree::DeepFirstSearch::inOrder);
    std::cout << "DeepFirstSearch inOrder -> ";
    for (int value : data) {
        std::cout << value << " ";
    }
    std::cout << std::endl;
    }

    {
    const std::vector<int> data = tree.deepFirstSearch(Tree::DeepFirstSearch::preOrder);
    std::cout << "DeepFirstSearch preOrder -> ";
    for (int value : data) {
        std::cout << value << " ";
    }
    std::cout << std::endl;
    }

    {
    const std::vector<int> data = tree.deepFirstSearch(Tree::DeepFirstSearch::postOrder);
    std::cout << "DeepFirstSearch postOrder -> ";
    for (int value : data) {
        std::cout << value << " ";
    }
    std::cout << std::endl;
    }

}

void test_isValidBST() {
    using Tree = BinarySearchTree::BinarySearchTree<int>;

    Tree tree; 
    tree.insert(9);
    tree.insert(4);
    tree.insert(6);
    tree.insert(20);
    tree.insert(170);
    tree.insert(15);
    tree.insert(1);
    tree.insert(29);
    tree.insert(200);
    tree.print();
    std::cout << "Tree is BST: " << tree.isValidBST() << std::endl;
}

void test() {
    //test_BreadthFirstSearch();
    //test_DeepFirstSearch();
    test_isValidBST();

}

}