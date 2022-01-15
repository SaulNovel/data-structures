#include <LinkedListExercises/LinkedList.h>
#include <LinkedListExercises/DoubleLinkedList.h>

#include <string>

namespace LinkedListTest
{
using LinkedList::LinkedList;
using DoubleLinkedList::DoubleLinkedList;


void linkedList_removeTest(LinkedList<std::string>& list) {
    std::cout << "Removing element 'second'" << std::endl;
    list.remove("second");
    list.print();
    std::cout << "list.size(): " << list.size() << std::endl; 

    std::cout << "Removing element 'first'" << std::endl;
    list.remove("first");
    list.print();
    std::cout << "list.size(): " << list.size() << std::endl; 

    std::cout << "Removing element 'fith'" << std::endl;
    list.remove("fith");
    list.print();
    std::cout << "list.size(): " << list.size() << std::endl; 
}

void linkedList_appendTest(LinkedList<std::string>& list) {
    std::cout << "Adding elements to the end" << std::endl;

    const std::vector<std::string> elements = {"second", "third", "fourth", "fith"};
    for (const auto& element : elements) {
        list.append(element);
    }
    list.print();
}

void linkedList_prependTest(LinkedList<std::string>& list) {
    std::cout << "Adding elements to the beginning" << std::endl;
   
    list.prepend("second");
    list.prepend("first");
    list.print();
    std::cout << "list.size(): " << list.size() << std::endl; 
}

void linkedList_insertTest(LinkedList<std::string>& list) {
    list.remove("fourth");
    list.append("fith");

    std::cout << "Inserting elements in the middle" << std::endl;
    list.insert(2, "third");
    list.insert(3, "fourth");

    // expect out of range
    list.insert(120, "something");    

    list.print();
    std::cout << "list.size(): " << list.size() << std::endl; 
}

void linkedList_reverseTest(LinkedList<std::string>& list) {
    std::cout << "Reversing list" << std::endl;
    std::cout << "- initial:" << std::endl;
    list.printChain();
    list.reverse_iterative();
    std::cout << "- reversed iterative:" << std::endl;
    list.printChain();

    list.reverse_recursive();
    std::cout << "- reversed recursive:" << std::endl;
    list.printChain();
}


void linkedListTest() {
    LinkedList<std::string> list("first");

    linkedList_appendTest(list);

    linkedList_removeTest(list);

    linkedList_prependTest(list);

    linkedList_insertTest(list);

    linkedList_reverseTest(list);
}



void doubleLinkedList_appendTest(DoubleLinkedList<std::string>& list) {
    const std::vector<std::string> elements = {"second", "third", "fourth", "fith"};
    for (const auto& element : elements) {
        list.append(element);
    }
    list.print();
    list.printReverse();
}

void doubleLinkedList_prependTest(DoubleLinkedList<std::string>& list) {
    const std::vector<std::string> elements = {"first", "zero"};
    for (const auto& element : elements) {
        list.prepend(element);
    }
    list.print();
    list.printReverse();
}

void doubleLinkedList_removeTest(DoubleLinkedList<std::string>& list) {
    std::cout << "Removing element at index '0'" << std::endl;
    list.remove(0);
    list.print();
    std::cout << "list.size(): " << list.size() << std::endl; 

    std::cout << "Removing element at index '2'" << std::endl;
    list.remove(2);
    list.print();
    std::cout << "list.size(): " << list.size() << std::endl; 

    std::cout << "Removing last element" << std::endl;
    list.remove(static_cast<int>(list.size())-1);
    list.print();
    std::cout << "list.size(): " << list.size() << std::endl; 
}

void doubleLinkedList_insertTest(DoubleLinkedList<std::string>& list)
{
    std::cout << "Insert element at index '2'" << std::endl;
    list.insert(2, "third");
    list.print();
}


void doubleLinkedListTest() {
    DoubleLinkedList<std::string> list;

    doubleLinkedList_appendTest(list);

    doubleLinkedList_prependTest(list);

    doubleLinkedList_removeTest(list);

    doubleLinkedList_insertTest(list);
}


void test() {
    linkedListTest();

    //doubleLinkedListTest();

}

}


