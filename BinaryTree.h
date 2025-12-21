#pragma once
#include <iostream>
#include <vector>

// to set one class that works for all types
template <typename T>

class BinaryTree
{
public:
    T data;
    // To set the depth of the tree (levels)
    int depth;

    // Default constructor
    BinaryTree() = default;
    explicit BinaryTree(int n) { setDepth(n); }

    // To get the value of a node
    T getNode(int n, int index) {
        return tree[n][index];
    }

    // To initialize the tree with a depth
    void setDepth(int n) {
        depth = n;
        tree.resize(n + 1);
        for (int i = 0; i <= n; i++)
            tree[i].resize(i + 1);
    }

    // To set the value of a node
    void setNode(int level, int index, T value) {
        tree[level][index] = value;
    }

    // To display the tree values for each level
    void display() {
        for (int i = 0; i <= depth; i++) {
            for (size_t j = 0; j < tree[i].size(); j++)
                std::cout << tree[i][j] << " ";
            std::cout << std::endl;
        }

        std::cout << std::endl;

        // Creation of the tree display
        for (int i = 0; i <= depth; ++i) {
            // Spaces to shift the line
            for (int s = 0; s < (depth - i) * 2; ++s)
                std::cout << " ";

            // Display all nodes at level i
            for (size_t j = 0; j < tree[i].size(); ++j) {
                std::cout << " " << tree[i][j] << "  "; // fixed space between two nodes
            }
            // Final separation between trees
            std::cout << "\n";

            // Display branches / \ except for the last level
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