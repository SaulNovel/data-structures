
namespace DoubleLinkedList
{

template<class T>
class DoubleLinkedList {
public:

    DoubleLinkedList() :
        head_(nullptr), 
        tail_(head_),
        size_(0)
    {
    }

    DoubleLinkedList(const T& value) :
        head_(new Node(value)),
        tail_(head_),
        size_(1)
    {
    }


    void append(const T& value) {
        Node* node = new Node(value);

        if (!head_) {
            head_ = node;
            tail_ = node;
            size_++;
            return;
        }

        node->prev = tail_;
        tail_->next = node;
        tail_ = node;
        size_++;
    }

    void prepend(const T& value) {
        Node* node = new Node(value);
    
        if (!head_) {
            head_ = node;
            tail_ = node;
            size_++;
            return;
        }

        node->next = head_;
        head_->prev = node;
        head_ = node;
        size_++;
    }

    /**
     * On the current implementation insert needs to loop
     * elements till reach the index given
     * - Time complexity -> O(n)
     * Index starts from 0
    */ 
    void insert(size_t index, const T& value) {
        if (index <= 0) {
            prepend(value);
            size_++;
            return;
        }

        int lastIndex = static_cast<int>(size_ -1);
        if (static_cast<int>(index) > lastIndex) {
            append(value);
            size_++;
            return;
        }

        // Normally there is no need to handle prevNode/prevNode.next == nullptr
        Node* node = new Node(value);
        Node* prevNode = getNodeAtIndex(static_cast<int>(index)-1);
        
        node->next = prevNode->next;
        prevNode->next->prev = node;
        node->prev = prevNode;
        prevNode->next = node;

        size_++;
    }

    // * Index starts from 0
    void remove(int index) {
        // Check if it is the first node
        if (head_ == nullptr) {
            std::cout << "cannot remove node at index '" << index << "', the list is empty" << std::endl; 
            return;
        }
        if (index > static_cast<int>(size_)) {
            std::cout << "Index '" << index << "' is out of range {0, " << size_ << "}" << std::endl; 
            return;
        }
        
        if (index == 0) {
            Node* temp = head_;
            head_ = head_->next;
            delete temp;
            size_--;
            return;
        }

        if (index == (static_cast<int>(size_)-1)) {
            Node* temp = tail_;
            tail_ = tail_->prev;
            // do not point anyware
            tail_->next = nullptr;
            delete temp;
            size_--;
            return;
        }

        Node* node = getNodeAtIndex(index);
        node->prev->next = node->next;
        node->next->prev = node->prev;
        delete node;
        size_--;
    }

    size_t size() { return size_; }

    void print() {      
        std::cout << "list:" << std::endl;

        Node* it = head_;
        int counter = 0;
        while(it != nullptr) {            
            std::cout << "- Node[" << counter++ << "] -> " << it->value << std::endl;
            it = it->next;
        }
    }

    void printReverse() {   
        std::cout << "list reverse order:" << std::endl;

        Node* it = tail_;
        int counter = static_cast<int>(size_) - 1;
        while(it != nullptr) {            
            std::cout << "- Node[" << counter-- << "] -> " << it->value << std::endl;
            it = it->prev;
        }
    }

    ~DoubleLinkedList() {
        Node* it = head_;
        while(it != nullptr) {
            Node* temp = it;
            it = it->next;
            delete temp;
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

    Node* head_;
    Node* tail_;
    size_t size_;

    Node* getNodeAtIndex(int index) {
        int distFromTail = static_cast<int>(size_) - index;
        if (distFromTail > index) {
            return lookUp(index);
        }

         return reverseLookUp(distFromTail);
    }

    Node* lookUp(int index) {

        Node* it = head_;
        int counter = 0;
        while(it != nullptr) {
            //previous node
            if (counter == index) {
                return it;
            }

            counter++;
            it = it->next;
        }

        return nullptr;

    }

    Node* reverseLookUp(int index) {
        Node* it = tail_;
        int counter = 0;
        while(it != nullptr) {
            //previous node
            if (counter == index) {
                return it;
            }

            counter++;
            it = it->prev;
        }

        return nullptr;
    }

};

}


