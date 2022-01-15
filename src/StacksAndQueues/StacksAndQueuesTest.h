#include <StacksAndQueues/Stack.h>
#include <StacksAndQueues/Queue.h>
#include <StacksAndQueues/QueueUsingStacks.h>

#include <string>
#include <type_traits>

namespace StacksAndQueuesTest
{

using Queue::Queue;
using QueueUsingStacks::MyQueue;

template<typename ContainerType>
void printLastItem(const ContainerType& container) {

    constexpr bool queue = std::is_same<ContainerType, Queue<std::string>>::value;

    if (container.isEmpty()) {
        std::cout << "Container is empty, expected exception" << std::endl;
    }
    try {
        const auto& item = container.peek();
        std::cout << (queue ? "- firstItem: " : "- topItem: ") << item << std::endl; 
    } catch (std::out_of_range& e) {
        std::cout << "- Error -> " << e.what() << std::endl;
    }
}

template<typename StackType>
void stack_APITest(StackType& stack) {

    stack.pop();
    printLastItem(stack);

    stack.push("Google ");
    stack.push(" Udemy ");
    stack.push("Discord");

    stack.print();

    printLastItem(stack);

    stack.pop();
    stack.pop();

    std::cout << "Stack after popping 2 elements: " << std::endl;

    stack.print();

    printLastItem(stack);  
}

void stack_test() {
    Stack::Stack<std::string> stack;
    stack_APITest(stack);

    Stack::StackArray<std::string> stackArray;
    stack_APITest(stackArray);
}

void queue_APITest(Queue<std::string>& queue) {

    queue.dequeue();
    printLastItem(queue);

    queue.enqueue("Joy");
    queue.enqueue("Matt");
    queue.enqueue("Pavel");
    queue.enqueue("Samir");

    queue.print();

    printLastItem(queue);

    queue.dequeue();
    queue.dequeue();
    queue.dequeue();
    queue.dequeue();

    std::cout << "Queue after popping 2 elements: " << std::endl;

    queue.print();

    printLastItem(queue);
}



void queue_test() {
    Queue<std::string> queue;
    
    queue_APITest(queue);
}

void queueUsingStacks_test() {
    MyQueue<std::string> queue;

    queue.pop();

    std::cout << "first element: " << queue.peek() << std::endl;

    queue.push("Joy");
    queue.push("Matt");
    queue.push("Pavel");
    queue.push("Samir");

    queue.print();

    std::cout << "first element: " << queue.peek() << std::endl;

    queue.pop();
    queue.pop();
    queue.pop();
    queue.pop();

    std::cout << "Queue after popping 2 elements: " << std::endl;

    queue.print();

    std::cout << "first element: " << queue.peek() << std::endl;

}

void test() {

    //stack_test();
    //queue_test();

    queueUsingStacks_test();

}

}


