#pragma once
#include <iostream>
#include <vector>

template <typename T>

class BinaryTree
{
public:
    T data;
    int depth;
    BinaryTree() = default;
    explicit BinaryTree(int n) { setDepth(n); } // constructor

    // getter Node
    T getNode(int n, int index) {
        return tree[n][index];
    }

    // setter depth 
    void setDepth(int n) {
        depth = n;
        tree.resize(n + 1);
        for (int i = 0; i <= n; i++)
            tree[i].resize(i + 1);
    }

    // setter for a node
    void setNode(int level, int index, T value) {
        tree[level][index] = value;
    }

    // display method to show binary tree
    void display() {
        for (int i = 0; i <= depth; i++) {
            for (size_t j = 0; j < tree[i].size(); j++)
                std::cout << tree[i][j] << " ";
            std::cout << std::endl;
        }

        std::cout << std::endl;
        for (int i = 0; i <= depth; ++i) {
            // spaces to move the line 
            for (int s = 0; s < (depth - i) * 2; ++s)
                std::cout << " ";

            // prints every node of level i
            for (size_t j = 0; j < tree[i].size(); ++j) {
                std::cout << " " << tree[i][j] << "  "; // fixed space between nodes
            }
            // Final separation between trees
            std::cout << "\n";

            // Prints branches / \ except for last level
            if (i < depth) {
                for (int s = 0; s < (depth - i) * 2; ++s)
                    std::cout << " ";
                for (size_t j = 0; j < tree[i].size(); ++j) {
                    std::cout << "/ \\ ";
                }
                // Final separation between trees
            }
            std::cout << "\n";
        }
    }

private:
    std::vector<std::vector<T>> tree;
};

