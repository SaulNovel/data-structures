#include <unordered_map>
#include <list>

using std::unordered_map;
using std::list;

class LRUCache {
    
private:    
    struct Node {
	    int key;
	    int val;
        
        Node(int key, int val) {
            this->key = key;
            this->val = val;
        }
    };
    
    using ListAddr = list<Node>::iterator;

    unordered_map<int, ListAddr> table_;
    list<Node> l_;
    const int capacity_;

public:
    LRUCache(int capacity) : 
        capacity_(capacity)
    {
    }
    
    int get(int key) {
        if (table_.count(key) == 0) {
            return -1;
        }
        
        ListAddr it = table_[key];
        
        l_.push_front(*it);
        l_.erase(it);
        table_[key] = l_.begin();
        
        return  l_.begin()->val;        
    }
    
    void put(int key, int value) {
        
        if (table_.count(key) > 0) {
            ListAddr it = table_[key];
            it->val = value;
            // move it to the front            
            l_.push_front(*it);
            l_.erase(it);
            table_[key] = l_.begin();

            return;
        }
        
        if (l_.size() >= capacity_) {
            int last = l_.back().key;
            table_.erase(last);
            l_.pop_back();
        }

        l_.push_front({key, value});
        int first = l_.front().key;
        table_[first] = l_.begin();
    }
    
    int getMostRecentKey() {
        return  l_.front().key;  
    }
};
