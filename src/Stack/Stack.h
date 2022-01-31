#ifndef STACK
#define STACK

namespace Stack
{

/**
 * Stack implementation: Array vs Linked list 
 * 
 * - Array:
 * -> Push/Pop operations happen at (Array.size() -1),  O(1)
 * -> Push might imply to allozate more memory and 
 *    copy the prev elemts into a new Array, O(n)
 *  
 * - LinkedList:
 * -> Push/Pop operations happen on tail's node, O(1)
 * 
 * Both are going to work well: Arrays allow direct access, 
 * linked list they have more dynamic memory
 * 
*/ 
template<class T>
class Stack {
public:

    Stack() : 
        top_(nullptr), 
        bottom_(nullptr),
        length_(0)
    {
    }

    Stack(const T& value) {
        top_ = new Node(value); 
        bottom_ = bottom_;
        length_ = 1;
    }

    /**
     * Returns reference to very top element 
    */
    const T& peek() const {
        if (top_ == nullptr) {
            throw std::out_of_range("Stack is empty");
        }

        return top_->value;
    }

    /**
     * Adds element to the top of the stack 
    */
    void push(const T& value) {

        Node* node = new Node(value);

        if (top_ == nullptr) {
            top_ = node;
            bottom_ = node;
            length_++;
            return;
        }

        node->next = top_;
        top_ = node;
        length_++;
    }

    /**
     * Removes element from the top of the stack
    */
    void pop() {
        if (top_ == nullptr) { return; }

        Node* temp = top_;
        top_ = top_->next;
        bottom_ = (top_ == nullptr) ? top_ : bottom_;
        delete temp;
        length_--;
    }

    void print() {       
        Node* it = top_;
        int counter = static_cast<int>(length_);
        const std::string separator =  "------------------";
        while(it != nullptr) {
            std::cout << separator << std::endl;  
            std::cout << "[" << counter << "] -> | " << it->value << " |" << std::endl;
            std::cout << (counter == 0 ? separator : "");  
            it = it->next;
            counter--;
        }
        std::cout << std::endl;
    }

    const bool isEmpty() const { return length_ == 0; }

    ~Stack() {
        Node* it = top_;
        while (it != nullptr) {
            it = it->next;
            pop();
        }
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

    Node* top_;
    Node* bottom_;
    size_t length_;


};

template<class T>
class StackArray {
public:

    StackArray() {
        data_ = {};
    }

    StackArray(const T& value) {
        data_ = { value };
    }

    /**
     * Returns reference to very top element 
    */
    const T& peek() const {
        if (data_.empty()) {
            throw std::out_of_range("Stack is empty");
        }

        return data_.back();
    }

    /**
     * Adds element to the top of the stack 
    */
    void push(const T& value) {
        data_.push_back(value);
    }

    /**
     * Removes element from the top of the stack
    */
    void pop() {
        if (data_.empty()) { return; }

        data_.pop_back();
    }

    void print() {
        int last = static_cast<int>(data_.size()) -1;
        const std::string separator =  "------------------";
        
        for (int i=last; i>=0; i--) {
            std::cout << separator << std::endl;
            std::cout << "[" << i << "] -> | " << data_[i] << " |" << std::endl;
            std::cout << (i == 0 ? separator : "");  
        }
        std::cout << std::endl;
    }

    const bool isEmpty() const { return data_.empty(); }

private:
    std::vector<T> data_;
};


}

#endif
