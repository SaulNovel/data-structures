#include <TreeExercises/BinarySearchTree.h>

#include <string>

namespace TreeTest
{

using BinarySearchTree::BinarySearchTree;


/**
 * Example:
 *    9
 *  4    20
 * 1 6 15  170
 * 
 * tree.insert(9)
 * tree.insert(4)
 * tree.insert(6)
 * tree.insert(20)
 * tree.insert(170)
 * tree.insert(15)
 * tree.insert(1)
 * tree.insert(29)
 */ 
void test_insert() {
    BinarySearchTree<int> tree; 
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

    std::cout << "tree has value '100': " << tree.lookup(100) << std::endl;
    std::cout << "tree has value '1000': " << tree.lookup(1000) << std::endl;
    std::cout << "tree has value '2000': " << tree.lookup(2000) << std::endl;
    std::cout << "tree has value '200': " << tree.lookup(200) << std::endl;
    std::cout << "tree has value '29': " << tree.lookup(29) << std::endl;

    tree.remove(15);
    tree.remove(1);
    tree.remove(29);
    tree.remove(200);
    tree.remove(9);
    tree.remove(4);
    tree.remove(6);
    tree.remove(20);
    tree.print();

    tree.insert(60);
    tree.insert(30);
    tree.insert(72);
    tree.insert(1);
    tree.insert(55);
    tree.insert(38);
    tree.insert(44);
    tree.insert(73);
    tree.insert(78);
    tree.insert(85);
    tree.insert(86);
    tree.insert(90);
    tree.insert(99);
    tree.print();

    tree.remove(30);
    tree.print();
}

void test() {

    test_insert();
}

}
