#ifndef QUEUE 
#define QUEUE 

namespace Queue
{

/**
 * Queue implementation: Array vs Linked list 
 * 
 * - Array:
 * -> Push operations happen at (Array.size() -1), O(1) 
 *    (might imply to allozate more memory and 
 *    copy the prev elemts into a new Array, O(n))
 * -> Pop implies shifting all elements, O(n)
 *  
 * - LinkedList:
 * -> Push operations happen on tail's node, O(1)
 * -> Pop operations happen on head's node, O(1)
 * 
 * LinkedList are the best option
 * 
*/

template<class T>
class Queue {
public:

    Queue() : 
        first_(nullptr), 
        last_(nullptr),
        length_(0)
    {
    }

    Queue(const T& value) {
        first_ = new Node(value); 
        last_ = first_;
        length_ = 1;
    }

    /**
     * Returns reference to first element 
    */
    const T& peek() const {
        if (first_ == nullptr) {
            throw std::out_of_range("Queue is empty");
        }

        return first_->value;
    }

    /**
     * Adds element to the end of the queue
    */
    void enqueue(const T& value) {

        Node* node = new Node(value);

        if (first_ == nullptr) {
            first_ = node;
            last_ = node;
            length_++;
            return;
        }

        last_->next = node;
        last_ = node;
        length_++;
    }

    /**
     * Removes first element from the queue
     * Removes from front
    */
    void dequeue() {
        if (first_ == nullptr) { return; }

        Node* temp = first_;
        first_ = first_->next;
        delete temp;
        length_--;
    }

    void print() {       
        Node* it = first_;
        while(it != nullptr) {
            std::cout << it->value << " -> ";
            it = it->next;
        }
        std::cout << "nullptr" << std::endl;
    }

    const bool isEmpty() const { return length_ == 0; }

    ~Queue() {
        Node* it = first_;
        while (it != nullptr) {
            it = it->next;
            dequeue();
        }
        first_ = nullptr;
        last_ = nullptr;
    }

private:

    class Node {
        public:
        T value;
        Node* prev;
        Node* next;

        Node(const T& value) {
            this->value= value;
            this->prev = nullptr;
            this->next = nullptr;
        }

        Node(const T& value, Node* prev, Node* next) {
            this->value= value;
            this->prev = prev;
            this->next = next;
        }
    };

    Node* first_;
    Node* last_;
    size_t length_;
};

}

#endif

