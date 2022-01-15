#ifndef __BINARY_SEARCH_TREE__   // if x.h hasn't been included yet...
#define __BINARY_SEARCH_TREE__   //   #define this so the compiler knows it has been included

#include <string>
#include <vector>
#include <queue>
#include <stack>

/**
 * Binary Search Tree:
 * - All child nodes to the right of the root node must be greater than the current node
 *    -> Moving to the right increases
 *    -> Moving to the left decreases
 * - A node can only have up to 2 children
 * - lookup -> Average: O(log(n)) Worst: O(n)
 * - insert -> Average: O(log(n)) Worst: O(n)
 * - delete -> Average: O(log(n)) Worst: O(n)
*/
namespace BinarySearchTree
{

template <class T>
class BinarySearchTree
{

public:
    BinarySearchTree() : 
        root_(nullptr)
    {}

    BinarySearchTree(const T &value)
    {
        root_ = new Node(value);
    }

    void insert(const T& value) {
        Node* child = new Node(value);
        if (root_ == nullptr) {
            root_ = child;
            return;
        }
        Node** node = find_insert_node(root_, value);
        *node = child;
    }

    bool lookup(const T& value) {
        return find_value(root_, value);
    }

    /**
     * - Find node
     * - move to right child
     * - move to left childs till find the latest
     * - last child:
     *   -> Pointed by root node of the one removed
     *   -> Points to the childs of the removed node 
    */ 
    void remove(const T& value) {

        // Special case for one 1 element
        Node* it = root_;

        if (it == nullptr) { return; }

        if (it->left == nullptr && it->right == nullptr) {
            if (it->value == value) { 
                delete it; 
                root_ = nullptr;
            }

            return;
        }

        Node* prev = nullptr;
        bool left = false;

        while(it != nullptr) {
            if (it->value == value) {

                Node** replacement = find_replacement(it);
                Node* replacementCopy = *replacement;

                if (replacementCopy == nullptr) {
                    left ? (prev->left = nullptr) : (prev->right = nullptr); 
                    delete it;

                    return;
                }

                // avoid loops with pointers
                (replacementCopy == it->right) ? (replacementCopy->right = nullptr) : (replacementCopy->right = it->right);
                (replacementCopy == it->left) ? (replacementCopy->left = nullptr) : (replacementCopy->left = it->left);

                if (it == root_) {
                    root_ = replacementCopy;
                }

                else {
                    left ? (prev->left = replacementCopy) : (prev->right = replacementCopy);
                }

                delete it;
                return;
            }

            // Path taken form previous node to it
            prev = it;
            left = it->value > value;
            it = left ? it->left : it->right;
        }

        std::cout << "value '" << value << "' was not removed" << std::endl;
    }

    void print() const {
        print_level("", root_, false);
    }

    /**
     * Searching: BreadthFirstSearch iterative
     * 
     * Implements BreadthFirstSearch in an iterative way
     * The vector returned contains all node values ordered byt the algorithm Breadth first search
    */
    const std::vector<T> breadthFirstSearch() {
        
        std::vector<T> nodes;

        std::queue<Node*> childs;
        queue_push_node(childs, root_);

        while (!childs.empty()) {
            // Get first node inserted
            Node* node = childs.front();
            // insert their children
            queue_push_node(childs, node->left);
            queue_push_node(childs, node->right);

            nodes.push_back(node->value);

            // remove node
            childs.pop();
        }

        return nodes;
    }


    const std::vector<T> breadthFirstSearchR() {
        std::vector<T> nodes;
        std::queue<Node*> childs;
        queue_push_node(childs, root_);
        breadthFirstSearch_recursive(childs, nodes);

        return nodes;
    }

    // InOrder - [1, 4, 6, 9, 15, 20, 170]
    // PreOrder - [9, 4, 1, 6, 20, 15, 170]
    // PostOrder - [1, 6, 4, 15, 170, 20, 9]

    enum class DeepFirstSearch {
        inOrder,
        preOrder,
        postOrder,
    };

    /**
     * If implemented with recursion the space 
     * complexity is the high of the tree
    */
    const std::vector<T> deepFirstSearch(const DeepFirstSearch& mode) {

        std::stack<Node*> stack;
        std::vector<T> nodes;

        stack.push(root_);

        switch (mode)
        {
        case DeepFirstSearch::inOrder:
            //deepFirstSearch_inOrder(stack, nodes);
            deepFirstSearch_inOrder(root_, nodes);
            break;
        case DeepFirstSearch::preOrder:
            deepFirstSearch_preOrder(root_, nodes);
            break;
        default:
            deepFirstSearch_postOrder(root_, nodes);
            break;
        }

        return nodes;
    }


    /**
     * 
     * Validate Binary Search Tree
     * Given the root of a binary tree, determine if it is a valid binary search tree (BST).
     * A valid BST is defined as follows:
     * - The left subtree of a node contains only nodes with keys less than the node's key.
     * - The right subtree of a node contains only nodes with keys greater than the node's key.
     * - Both the left and right subtrees must also be binary search trees
     * 
     * Example 1:
     * - Input: root = [2,1,3]
     * - Output: true
     * 
     * Example 1:
     * - Input: root = [5,1,4,null,null,3,6]
     * - Output: false
     * - Explanation: The root node's value is 5 but its right child's value is 4.
     * 
     * Constraints:
     * - The number of nodes in the tree is in the range [1, 104].
     * - -2^31 <= Node.val <= 2^31 - 1
    */ 
    bool isValidBST() {
        return isValidBST(root_);
    }


    ~BinarySearchTree() {
        remove_nodes(root_);
        root_ = nullptr;
    }

private:

    class Node
    {
    public:
        T value;
        Node* left;
        Node* right;

        Node(const T& value)
        {
            this->value = value;
            this->left = nullptr;
            this->right = nullptr;
        }
    };

    Node* root_;


    /**
     *
     * Returns a pointer to the pointer where to insert the new node
     * Check side:
     * - value > current node's value -> right
     * - value < current node's value -> left
    */  
    Node** find_insert_node(Node* currentNode, const T& value) {

        const T& currentValue = currentNode->value;
        // double pointer (pointer to pointer) points to the address of the pointer 
        Node** childNode = (value > currentValue) ? &(currentNode->right) : &(currentNode->left);

        // if pointer pointed is null
        if (*childNode == nullptr) {
            return childNode;
        }
        // continue looking a place to insert
        return find_insert_node(*childNode, value);
    }

    /**
     *
     * Returns true if value found in the tree
     * Check side:
     * - value > current node's value -> right
     * - value < current node's value -> left
    */
    bool find_value(Node* currentNode, const T& value) {

        if (currentNode == nullptr) {
            return false;
        }

        const T& currentValue = currentNode->value;
        if (currentValue == value) {
            return true;
        }

        Node* childNode = (value > currentValue) ? currentNode->right : currentNode->left;
        // continue looking a place to insert
        return find_value(childNode, value);
    }

    /**
     * - Move to next node to the right
     * - Find last node to the left
     * - breaks the link between the previous node and the node returned
     * 
     * @param current node to replace
     * @return pointer to replacement node, if no replacement was found returns nullptr
    */ 
    Node** find_replacement(Node* current) {

        if (current == nullptr) { return nullptr; }

        Node* right = current->right;
        if (right == nullptr) {
            // return next node to the left
            Node** leftPtr = &(current->left);
            return leftPtr;
        }
        
        // replacement node
        Node* nextLeft = right->left;
        if (nextLeft == nullptr) {
            Node** rightPtr = &right;
            return rightPtr;
        }

        // Keep previous node (needed to break the link with latest left node)
        Node* prev = right;
        while (nextLeft->left != nullptr) {

            prev = nextLeft;
            nextLeft = nextLeft->left;
        }

        // It could be either null, either a nother node
        prev->left = nextLeft->right;

        Node** lastLeftPtr = &nextLeft;

        return lastLeftPtr;
    }


    void print_level(const std::string& prefix, const Node* node, bool left) const {
        if( node != nullptr ) {
            std::cout << prefix;

            if (node == root_) {
                std::cout << "└──";
            }

            else {
                std::cout << (left ? "├──(l)" : "└──(r)" );
            }

            // print the value of the node
            std::cout << node->value << std::endl;
            // enter the next tree level - left and right branch
            print_level(prefix + (left ? "│   " : "    "), node->left, true);
            print_level(prefix + (left ? "│   " : "    "), node->right, false);
        }
    }

    void remove_nodes(Node* node) {

        if (node != nullptr) {
            Node* right = node->right;
            Node* left = node->left;

            Node* temp = node;
            delete temp;

            remove_nodes(right);
            remove_nodes(left);
        }
    }

    void queue_push_node(std::queue<Node*>& queue, Node* node) {
        if (node != nullptr) {
            queue.push(node);
        }
    }

    void breadthFirstSearch_recursive(std::queue<Node*>& childs, std::vector<T>& nodes) {
        // base case
        if (childs.empty()) { return; }

        // Get first node inserted
        Node* node = childs.front();
        // insert their children
        queue_push_node(childs, node->left);
        queue_push_node(childs, node->right);

        nodes.push_back(node->value);

        // remove node
        childs.pop();

        breadthFirstSearch_recursive(childs, nodes);
    }

    /*
    void deepFirstSearch_inOrder(std::stack<Node*>& stack, std::vector<T>& nodes) {

        Node* node = stack.top();

        if (node == nullptr) { return; }

        // Node has no childs
        bool last = node->left == nullptr && node->right == nullptr;
        if (last) {
            nodes.push_back(node->value);
            stack.pop();
            return;
        }

        // Node has left child
        if (node->left != nullptr) {
            stack.push(node->left);
            deepFirstSearch_inOrder(stack, nodes);
        }

        nodes.push_back(node->value);
        stack.pop();

        // Node has right child
        if (node->right != nullptr) {
            stack.push(node->right);
            deepFirstSearch_inOrder(stack, nodes);
        }

    }
    */

   /**
    * - No need to keep a stack
    * - Follow up the line where the recursive call returns and the following lines
    */ 
    void deepFirstSearch_inOrder(Node* node, std::vector<T>& nodes) {

        if (node == nullptr) { return; }

        if (node->left != nullptr) {
            deepFirstSearch_inOrder(node->left, nodes);
        }

        nodes.push_back(node->value);

        if (node->right != nullptr) {
            deepFirstSearch_inOrder(node->right, nodes);
        }
    }

    void deepFirstSearch_preOrder(Node* node, std::vector<T>& nodes) {

        if (node == nullptr) { return; }

        nodes.push_back(node->value);

        if (node->left != nullptr) {
            deepFirstSearch_preOrder(node->left, nodes);
        }

        if (node->right != nullptr) {
            deepFirstSearch_preOrder(node->right, nodes);
        }
    }

    /** Example:
     *    9
     *  4    20
     * 1 6 15  170
     * 
     * Steps:
     * - 9 (node->left != nullptr) -> 4 (node->left != nullptr) -> 1 (node->left == nullptr) && (node->right == nullptr), nodes.push_back(1)
     * - return to 4 line (node->right == nullptr) -> 6 (node->left == nullptr) && (node->right == nullptr), nodes.push_back(6)
     * - return to 4 line nodes.push_back(4)
     * - return to 9 line (node->right == nullptr) -> 20 (node->left == nullptr) -> 15 (node->left == nullptr) && (node->right == nullptr), nodes.push_back(15)
     * - return to 20 line (node->right == nullptr) -> 170 (node->left == nullptr), nodes.push_back(170)
     * - return to 20 line nodes.push_back(20)
     * - return to 20 line nodes.push_back(9)
     * 
    */ 
    void deepFirstSearch_postOrder(Node* node, std::vector<T>& nodes) {

        if (node == nullptr) { return; }

        if (node->left != nullptr) {
            deepFirstSearch_postOrder(node->left, nodes);
        }

        if (node->right != nullptr) {
            deepFirstSearch_postOrder(node->right, nodes);
        }

        nodes.push_back(node->value);
    }
 
    /**
     * Inefficient solution
     * isValidBST
     * isSubTreeLesser(Node* node, const T& value)
     * isSubTreeGreater(Node* node, const T& value)
     * 
     * Needs to compare top value on each subtree
    */ 
    bool isSubTreeLesser(Node* node, const T& value) {

        if (node == nullptr) { return true; }

        bool lesser = (node->value < value);
        if (!lesser) { return false; }

        bool subTreeLeftLesser = isSubTreeLesser(node->left, value);
        if (!subTreeLeftLesser) { return false; }

        bool subTreeRightLesser = isSubTreeLesser(node->right, value);
        if (!subTreeRightLesser) { return false; }
        
        return true;
    }

    bool isSubTreeGreater(Node* node, const T& value) {

        if (node == nullptr) { return true; }

        bool greater = (node->value > value);
        if (!greater) { return false; }

        bool subTreeLeftGreater = isSubTreeGreater(node->left, value);
        if (!subTreeLeftGreater) { return false; }

        bool subTreeRightGreater = isSubTreeGreater(node->right, value);
        if (!subTreeRightGreater) { return false; }
        
        return true;
    }

    bool isValidBST(Node* root) {
        
        if (root == nullptr) { return true; }

        const T& value = root->value;

        bool leftValidBST = isSubTreeLesser(root->left, value);
        if (!leftValidBST) { return false; }

        bool rightValidBST = isSubTreeGreater(root->right, value);
        if (!rightValidBST) { return false; }

        // Check value for next node on the left
        bool nextValueLeftCheck = isValidBST(root->right);
        if (!nextValueLeftCheck) { return false; }

        // Check value for next node on the left
        bool nextValueRightCheck = isValidBST(root->left);
        if (!nextValueRightCheck) { return false; }

        return true;
    }

/**
 * Better Solution (only valid for integers)
 * Check that the value of each node is within a valid range
*/

/*
    bool isValidBST(TreeNode* node) {
                
        if (node == nullptr) { return true; }
        
        bool leftBTS = isBST(node->left, std::numeric_limits<int64_t>::min(), node->val);
        if (!leftBTS) { return false; }
        
        bool rightBTS = isBST(node->right, node->val, std::numeric_limits<int64_t>::max());
        if (!rightBTS) { return false; }

        return leftBTS && rightBTS;
    }
    
    bool isSubTreeValid(TreeNode* node, const int64_t lowerThreshold, const int64_t uppThresHold) {

        if (node == nullptr) { return true; }
                
        return (node->val > lowerThreshold) && (node->val < uppThresHold);
    }
    
    bool isBST(TreeNode* node, const int64_t lowerThreshold, const int64_t upperThreshold) {

        if (node == nullptr) { return true; }
        
        // First check the node
        bool valid = isSubTreeValid(node, lowerThreshold, upperThreshold);
        if (!valid) { return false; }
        
        // Thresholds for left/right
        bool leftBST = isBST(node->left, lowerThreshold, node->val);
        if (!leftBST) { return false; }        
        
        bool rightBST = isBST(node->right, node->val, upperThreshold);
        if (!rightBST) { return false; }        

        return true;
    }
    */
};

}

#endif
