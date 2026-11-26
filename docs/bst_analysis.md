# Binary Search Tree Analysis

## Core operations

This implementation stores each integer in a `TreeNode` and maintains the binary
search ordering invariant: every value in the left subtree is smaller than the
node value, and every value in the right subtree is larger.

| Operation | Balanced BST | Skewed BST | Notes |
|---|---:|---:|---|
| Insert | O(log n) | O(n) | Duplicate values are rejected |
| Search | O(log n) | O(n) | Uses the BST ordering invariant |
| Remove | O(log n) | O(n) | Uses the in-order successor for two children |
| In-order traversal | O(n) | O(n) | Visits every node once |
| Height | O(n) | O(n) | Every node is visited recursively |
| Minimum / maximum | O(log n) | O(n) | Follows only one child chain |

## Average and worst cases

For a randomly constructed balanced BST, the average search path is O(log n).
The worst case occurs when values are inserted in sorted order or otherwise
create a chain. The height is then n, so insertion, search, removal, and
extrema lookup can require O(n) time.

## Recursive and iterative implementations

The implementation uses recursion because the BST is defined recursively. Each
operation changes the current node or explores exactly one child subtree. An
iterative implementation is possible for insertion, search, and minimum or
maximum lookup, and can avoid recursive call-stack use. Traversal and height
can also be implemented iteratively with explicit stacks or queues, but the
recursive implementations are shorter and map directly to the tree structure.

## Height convention

The public `height()` method reports 0 for an empty tree and 1 for a single
node. This convention is used consistently by `heightRecursive()`.

## Memory management

The destructor recursively deletes the complete subtree. Removal deletes nodes
with zero or one child directly and replaces a two-child node with the value of
its in-order successor before removing that successor. Copy construction,
copy assignment, and move construction or assignment are also provided so BST
ownership remains safe in normal C++ use.
