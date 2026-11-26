#include "project/binary_search_tree.h"

#include <algorithm>
#include <stdexcept>

// Constructor
BinarySearchTree::BinarySearchTree()
    : root_(nullptr), size_(0) {}

// Destructor
BinarySearchTree::~BinarySearchTree() {
    deleteSubtree(root_);
}

// Recursively delete all nodes
void BinarySearchTree::deleteSubtree(TreeNode* node) {
    if (node == nullptr) {
        return;
    }

    deleteSubtree(node->left);
    deleteSubtree(node->right);
    delete node;
}

// Insert a value
bool BinarySearchTree::insert(int value) {
    if (search(value)) {
        return false;
    }

    root_ = insertRecursive(root_, value);
    size_++;
    return true;
}

// Remove a value
bool BinarySearchTree::remove(int value) {
    if (!search(value)) {
        return false;
    }

    root_ = removeRecursive(root_, value);
    size_--;
    return true;
}

// Search for a value
bool BinarySearchTree::search(int value) const {
    return searchRecursive(root_, value);
}

// Check whether a value exists
bool BinarySearchTree::contains(int value) const {
    return search(value);
}

// Check whether the tree is empty
bool BinarySearchTree::empty() const noexcept {
    return size_ == 0;
}

// Return the number of nodes
std::size_t BinarySearchTree::size() const noexcept {
    return size_;
}

// Return the height of the tree
int BinarySearchTree::height() const {
    return heightRecursive(root_);
}

// In-order traversal
std::vector<int> BinarySearchTree::inorderTraversal() const {
    std::vector<int> result;
    inorderRecursive(root_, result);
    return result;
}

// Pre-order traversal
std::vector<int> BinarySearchTree::preorderTraversal() const {
    std::vector<int> result;
    preorderRecursive(root_, result);
    return result;
}

// Post-order traversal
std::vector<int> BinarySearchTree::postorderTraversal() const {
    std::vector<int> result;
    postorderRecursive(root_, result);
    return result;
}

// Find the minimum value
int BinarySearchTree::minimum() const {
    if (empty()) {
        throw std::logic_error("BST is empty");
    }

    return minimumRecursive(root_);
}

// Find the maximum value
int BinarySearchTree::maximum() const {
    if (empty()) {
        throw std::logic_error("BST is empty");
    }

    return maximumRecursive(root_);
}

// Recursive insertion
TreeNode* BinarySearchTree::insertRecursive(
    TreeNode* node, int value) {

    // Base case: create a new node
    if (node == nullptr) {
        return new TreeNode(value);
    }

    // Recursive case: insert into the correct subtree
    if (value < node->value) {
        node->left = insertRecursive(node->left, value);
    }
    else if (value > node->value) {
        node->right = insertRecursive(node->right, value);
    }

    return node;
}

// Recursive removal
TreeNode* BinarySearchTree::removeRecursive(
    TreeNode* node, int value) {

    // Base case: value not found
    if (node == nullptr) {
        return nullptr;
    }

    if (value < node->value) {
        node->left = removeRecursive(node->left, value);
    }
    else if (value > node->value) {
        node->right = removeRecursive(node->right, value);
    }
    else {
        // Case 1: no left child
        if (node->left == nullptr) {
            TreeNode* temp = node->right;
            delete node;
            return temp;
        }

        // Case 2: no right child
        if (node->right == nullptr) {
            TreeNode* temp = node->left;
            delete node;
            return temp;
        }

        // Case 3: node has two children
        // Find the in-order successor
        int successor = minimumRecursive(node->right);

        node->value = successor;

        // Remove the original successor node
        node->right = removeRecursive(
            node->right, successor);
    }

    return node;
}

// Recursive search
bool BinarySearchTree::searchRecursive(
    const TreeNode* node, int value) const {

    // Base case: value not found
    if (node == nullptr) {
        return false;
    }

    // Base case: value found
    if (node->value == value) {
        return true;
    }

    // Recursive case: search the correct subtree
    if (value < node->value) {
        return searchRecursive(node->left, value);
    }

    return searchRecursive(node->right, value);
}

// Recursive in-order traversal
// Left -> Root -> Right
void BinarySearchTree::inorderRecursive(
    const TreeNode* node,
    std::vector<int>& result) const {

    // Base case
    if (node == nullptr) {
        return;
    }

    inorderRecursive(node->left, result);
    result.push_back(node->value);
    inorderRecursive(node->right, result);
}

// Recursive pre-order traversal
// Root -> Left -> Right
void BinarySearchTree::preorderRecursive(
    const TreeNode* node,
    std::vector<int>& result) const {

    // Base case
    if (node == nullptr) {
        return;
    }

    result.push_back(node->value);
    preorderRecursive(node->left, result);
    preorderRecursive(node->right, result);
}

// Recursive post-order traversal
// Left -> Right -> Root
void BinarySearchTree::postorderRecursive(
    const TreeNode* node,
    std::vector<int>& result) const {

    // Base case
    if (node == nullptr) {
        return;
    }

    postorderRecursive(node->left, result);
    postorderRecursive(node->right, result);
    result.push_back(node->value);
}

// Recursive height calculation
int BinarySearchTree::heightRecursive(
    const TreeNode* node) const {

    // Base case: empty tree has height 0
    if (node == nullptr) {
        return 0;
    }

    // Recursive case: longest subtree plus one
    return 1 + std::max(
        heightRecursive(node->left),
        heightRecursive(node->right));
}

// Recursive minimum lookup
int BinarySearchTree::minimumRecursive(
    const TreeNode* node) const {

    // Base case: leftmost node
    if (node->left == nullptr) {
        return node->value;
    }

    // Recursive case
    return minimumRecursive(node->left);
}

// Recursive maximum lookup
int BinarySearchTree::maximumRecursive(
    const TreeNode* node) const {

    // Base case: rightmost node
    if (node->right == nullptr) {
        return node->value;
    }

    // Recursive case
    return maximumRecursive(node->right);
}
