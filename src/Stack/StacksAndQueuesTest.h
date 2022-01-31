#include <Stack/Stack.h>
#include <Queue/Queue.h>

#include <string>
#include <type_traits>

namespace StacksAndQueuesTest
{

using Queue::Queue;

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

void test() {

    //stack_test();
    //queue_test();

}

}


