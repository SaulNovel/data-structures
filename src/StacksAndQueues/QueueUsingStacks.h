#include <stack>

namespace QueueUsingStacks
{

/**
 * Implement a first in first out (FIFO) queue using only two stacks. 
 * The implemented queue should support all the functions of a normal queue (push, peek, pop, and empty).
 * 
 * Implement the MyQueue class:
 * - void push(int x) Pushes element x to the back of the queue.
 * - int pop() Removes the element from the front of the queue and returns it.
 * - int peek() Returns the element at the front of the queue.
 * - boolean empty() Returns true if the queue is empty, false otherwise.
 * 
 * Notes:
 * - You must use only standard operations of a stack, which means only push to top, 
 *   peek/pop from top, size, and is empty operations are valid.
 * - Depending on your language, the stack may not be supported natively. 
 *   You may simulate a stack using a list or deque (double-ended queue) 
 *   as long as you use only a stack's standard operations.
 * 
 * Example 1:
 * Input -> ["MyQueue", "push", "push", "peek", "pop", "empty"]
 * [[], [1], [2], [], [], []]
 * Output -> [null, null, null, 1, 1, false]
 * 
 * Explanation:
 * MyQueue myQueue = new MyQueue();
 * myQueue.push(1); // queue is: [1]
 * myQueue.push(2); // queue is: [1, 2] (leftmost is front of the queue)
 * myQueue.peek(); // return 1
 * myQueue.pop(); // return 1, queue is [2]
 * myQueue.empty(); // return false
 * 
 * Constraints:
 * - 1 <= x <= 9
 * - At most 100 calls will be made to push, pop, peek, and empty.
 * - All the calls to pop and peek are valid.
 * 
 * Follow-up: Can you implement the queue such that each operation is amortized O(1) time complexity? 
 * In other words, performing n operations will take overall O(n) time even if one of those operations may take longer.
 * 
*/

template<class T>
class MyQueue {
public:
    MyQueue() {
        front_ = T();
    }
    
    void push(const T& x) {
        if (stack1_.empty()) {
            front_ = x;
        }
        
        stack1_.push(x);
    }
    
    const T pop() {

        if (stack1_.empty() && stack2_.empty()) {
            // Throw
            return T();
        }

        if (stack2_.empty()) {
            move_reverse(stack1_, stack2_);
        }

        T item = stack2_.top();
        stack2_.pop();

        return item;
    }
    
    const T peek() {
        if (!stack2_.empty()) {
            return stack2_.top(); 
        }

        if (!stack1_.empty()) {
            return front_;
        }

        // Throw
        return T();

    }
    
    bool empty() {
        return stack1_.empty() && stack2_.empty();
    }

    // Debug
    void print() {

        // stack2 contains oldest elements
        std::stack<T> temp(stack2_);
        // stack1 contains newest elements, needs inversion
        std::stack<T> temp2(stack1_);

        print_temp_stack(temp);
        move_reverse(temp2, temp);
        print_temp_stack(temp);

        std::cout << "NULL" << std::endl;
    }

private:
    std::stack<T> stack1_;
    std::stack<T> stack2_;
    T front_;
 
    void move_reverse(std::stack<T>& stack1, std::stack<T>& stack2) {
        while (!stack1.empty()) {
            T item = stack1.top();
            stack1.pop();
            stack2.push(item);
        }
    }

    void print_temp_stack(std::stack<T>& stack) {
        while (!stack.empty()) {
            T item = stack.top();
            stack.pop();
            std::cout << item << " -> ";
        }
    }
};

/**
 * Your MyQueue object will be instantiated and called as such:
 * MyQueue* obj = new MyQueue();
 * obj->push(x);
 * int param_2 = obj->pop();
 * int param_3 = obj->peek();
 * bool param_4 = obj->empty();
 */

}


