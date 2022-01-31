#ifndef TRIE 
#define TRIE 

#include <string>
#include <unordered_map>

using std::string;
using std::unordered_map;

/**
 * Space complexity: O(n) + O(l)
 * Time complexity: O(l) -> l being the length of the word (It does not need to iterate all elements)
 * 
 * - question that requires to quickly look up strings that I need Im storing it and need to pull out
 * - autocomplete filter when looking on a search bar 
 */
class Trie {

    struct Node {
       	bool end;
		// map of connections
		// key: holds a character value (all characters connected to current node)
		// value: next node
		unordered_map<char, Node*> connections;
       	Node() : end(false) {}
    };
    
private:

	Node* root_;
    
    void insert(const string& word, int i, Node* node) {
        
        if (i == word.size()) {
            node->end = true;
            return;
        }
        
        auto& connections = node->connections;
        if (connections.count(word[i]) == 0) {
            connections[word[i]] = new Node;
        }

        insert(word, i+1, connections[word[i]]);
    }
    
	bool search(const string& word, int i, Node* node) {
		if (word.empty()) { return false; }
        
        if (i == word.size()) { return node->end; };
      
        auto& connections = node->connections;
        if (connections.count(word[i]) == 0) {
            return false;
        }
        
        return search(word, i+1, connections[word[i]]);
    }

	bool startsWith(const string& prefix, int i, Node* node) {
		if (prefix.empty()) { return false; }
        
        if (i == prefix.size()) { return true; };
      
        auto& connections = node->connections;
        if (connections.count(prefix[i]) == 0) {
            return false;
        }
        
        return startsWith(prefix, i+1, connections[prefix[i]]);
    }

public:
    
    Trie() : root_(new Node)
    {}
    
	Trie(const string& word) {
      	Trie();
        insert(word);
	}

    void insert(const string& word) {
		if (word.empty()) { return; }
        
        insert(word, 0, root_);
    }

	bool search(const string& word) {
		if (word.empty()) { return false; }
        
        return search(word, 0, root_);
    }

	bool startsWith(const string& prefix) {
		if (prefix.empty()) { return false; }
        
        return startsWith(prefix, 0, root_);
    }
};

#endif
