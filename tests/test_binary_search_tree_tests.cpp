#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "project/binary_search_tree.h"

TEST_CASE("BST starts empty and rejects duplicate values", "[bst]") {
    BinarySearchTree tree;
    REQUIRE(tree.empty());
    REQUIRE(tree.size() == 0);
    REQUIRE(tree.height() == 0);
    REQUIRE_FALSE(tree.search(10));

    REQUIRE(tree.insert(10));
    REQUIRE_FALSE(tree.insert(10));
    REQUIRE(tree.size() == 1);
    REQUIRE_FALSE(tree.empty());
}

TEST_CASE("BST supports insertion, search, minimum, and maximum", "[bst]") {
    BinarySearchTree tree;
    REQUIRE(tree.insert(50));
    REQUIRE(tree.insert(30));
    REQUIRE(tree.insert(70));
    REQUIRE(tree.insert(20));
    REQUIRE(tree.insert(40));

    REQUIRE(tree.search(40));
    REQUIRE(tree.contains(70));
    REQUIRE_FALSE(tree.search(999));
    REQUIRE(tree.minimum() == 20);
    REQUIRE(tree.maximum() == 70);
    REQUIRE(tree.size() == 5);
}

TEST_CASE("BST returns the three traversal orders", "[traversal]") {
    BinarySearchTree tree;
    for (int value : {50, 30, 70, 20, 40, 60, 80}) {
        tree.insert(value);
    }

    REQUIRE(tree.inorderTraversal() == std::vector<int>{20, 30, 40, 50, 60, 70, 80});
    REQUIRE(tree.preorderTraversal() == std::vector<int>{50, 30, 20, 40, 70, 60, 80});
    REQUIRE(tree.postorderTraversal() == std::vector<int>{20, 40, 30, 60, 80, 70, 50});
}

TEST_CASE("BST removal handles all node shapes", "[remove]") {
    BinarySearchTree tree;
    for (int value : {50, 30, 70, 20, 40, 60, 80}) {
        tree.insert(value);
    }

    REQUIRE(tree.remove(20));
    REQUIRE(tree.remove(30));
    REQUIRE(tree.remove(50));
    REQUIRE_FALSE(tree.remove(50));

    REQUIRE(tree.inorderTraversal() == std::vector<int>{40, 60, 70, 80});
    REQUIRE(tree.size() == 4);
}

TEST_CASE("BST calculates height and throws on empty extrema", "[height]") {
    BinarySearchTree tree;
    REQUIRE(tree.height() == 0);
    REQUIRE_THROWS_AS(tree.minimum(), std::logic_error);
    REQUIRE_THROWS_AS(tree.maximum(), std::logic_error);

    tree.insert(10);
    REQUIRE(tree.height() == 1);
    tree.insert(5);
    tree.insert(15);
    REQUIRE(tree.height() == 2);

    BinarySearchTree copy(tree);
    REQUIRE(copy.inorderTraversal() == std::vector<int>{5, 10, 15});
    REQUIRE(copy.remove(10));
    REQUIRE(copy.size() == 2);
    REQUIRE(tree.size() == 3);
}
