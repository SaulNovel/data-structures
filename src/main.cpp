#include <iostream>
#include <Graph/Graph.h>
#include <HashTable/HashTable.h>
#include <LinkedList/LinkedList.h>
#include <LinkedList/DoubleLinkedList.h>
#include <Queue/Queue.h>
#include <Stack/Stack.h>
#include <Tree/BinarySearchTree.h>
#include <RingBuffer/Ring.h>

#include <Graph/AdjacencyList.h>

int main()
{
    Graph_AdjacencyList::test_cycle_directedGraph();
    return 0;
}