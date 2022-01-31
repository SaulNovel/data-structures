#ifndef LINKED_LIST
#define LINKED_LIST

namespace LinkedList
{

template<class T>
class LinkedList {
public:

    LinkedList() :
        head_(nullptr), 
        tail_(head_)
    {
    }

    LinkedList(const T& value) {
        head_ = new Node;
        head_->value = value;
        head_->next = nullptr;
        tail_ = head_;
    }


    void append(const T& value) {
        Node* node = new Node;
        node->value = value;
        node->next = nullptr;
    
        if (!head_) {
            head_ = node;
            tail_ = node;
            return;
        }
    
        tail_->next = node;
        tail_ = node;
    }

    void prepend(const T& value) {
        Node* node = new Node;
        node->value = value;
        node->next = nullptr;
    
        if (!head_) {
            head_ = node;
            tail_ = node;
            return;
        }

        node->next = head_;
        head_ = node;
    }

    /**
     * On the current implementation insert needs to loop
     * elements till reach the index given
     * - Time complexity -> O(n)
    */ 
    void insert(size_t index, const T& value) {
        Node* it = head_;
        if (index == 0) {
            prepend(value);
            return;
        }

        Node* node = new Node;
        node->value = value;
        node->next = nullptr;
        size_t counter = 0;

        while(it != nullptr) {
            //previous node
            if (counter == index-1) {
                node->next = it->next;
                it->next = node;
                return;
            }

            counter++;
            it = it->next;
        }
        // Index is too big, add it at the end
        append(value);
    }

    void remove(const T& value) {
        // Check if it is the first node
        if (head_ == nullptr) {
            std::cout << "cannot remove value '" << value << "', the list is empty" << std::endl; 
            return;
        }
        
        if (head_->value == value) {
            Node* temp = head_;
            head_ = head_->next;
            delete temp;
            return;
        }
        
        Node* node = head_;
        while(node != nullptr) {
            Node* next = node->next;
            if (next == nullptr) {
                break;
            }

            if (next->value == value) {
                node->next = next->next;
                delete next;
                return;
            }

            node = next;
        }
        std::cout << "cannot remove value '" << value << "'" << std::endl; 
    }


    /**
     *   100        200
     * |1|200| -> |2|300|
     * - 3 pointers: next, prev, current
     * - initial state: next=NULL, prev=NULL, current=head
     * - break link between current and next and make current point to prev
     * - store next in a temp, at the end of the iteration current=next
     * 
    */ 
    void reverse_iterative() {

        if (head_ == nullptr || head_->next == nullptr) {
            return;
        }

        Node* next = nullptr;
        Node* prev = nullptr;
        Node* current = head_;

        while (current != nullptr) {
            // save next link
            next = current->next;
            // break link with next node
            // make link with previous node
            current->next = prev;
            // Prepare nodes for next iteration
            prev = current;
            current = next;
        }
        // move head to tail and tail to head
        Node* temp = tail_;
        tail_ = head_;
        head_ = temp;

    }

    void reverse_recursive() {

        if (head_ == nullptr) { return; }

        Node* next = head_->next;

        if (next == nullptr) { return; }

        /**
         * simpler:
         * int length = static_cast<int>(size());
         *  if (length < 2) { return; } 
        */ 

        reverse(head_, next);
    }

    void print() {       
        Node* it = head_;
        int counter = 0;
        while(it != nullptr) {            
            std::cout << "Node[" << counter++ << "] -> " << it->value << std::endl;
            it = it->next;
        }
    }


    void printChain() {       
        Node* it = head_;
        while(it != nullptr) {            
            std::cout << "|" << it << "|" << it->value << "| -> ";
            it = it->next;
        }
        // last node
        std::cout << "NULL" << std::endl;
    }

    size_t size() {       
        Node* it = head_;
        int counter = 0;
        while(it != nullptr) {            
            counter++;
            it = it->next;
        }
        
        return counter;
    }


    ~LinkedList() {
        Node* it = head_;
        while(it != nullptr) {
            Node* temp = it;
            it = it->next;
            delete temp;
        }
    }

private:

    struct Node {
        T value;
        Node* next;
    };

    Node* head_;
    Node* tail_;


    /**
     * The idea i to move a given node till the end
     * This function works when there are at least 2 nodes
    */ 
    void reverse(Node* current, Node* next) {
        Node* temp = next->next;
        if (temp == nullptr) {
            /**
             * third is the end of the linked list
             *    100               200
             * |current|PREV|   |next|NULL|
             * make third point to second and update head_
             *    100               200
             * |current|PREV| <- |next|100|
            */
            head_->next = nullptr;
            head_ = next;
            next->next = current;
            return;
        }

        // Make next node point to current
        next->next = current;
        reverse(next, temp);
    }

};

}

#endif


