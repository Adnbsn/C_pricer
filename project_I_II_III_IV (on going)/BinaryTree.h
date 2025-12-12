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
    explicit BinaryTree(int n) { setDepth(n); }

    T getNode(int n, int index) {
        return tree[n][index];
    }

    void setDepth(int n) {
        depth = n;
        tree.resize(n + 1);
        for (int i = 0; i <= n; i++)
            tree[i].resize(i + 1);
    }

    void setNode(int level, int index, T value) {
        tree[level][index] = value;
    }




    void display() {
        for (int i = 0; i <= depth; i++) {
            for (size_t j = 0; j < tree[i].size(); j++)
                std::cout << tree[i][j] << " ";
            std::cout << std::endl;
        }

        std::cout << std::endl;
        for (int i = 0; i <= depth; ++i) {
            // Espaces pour décaler la ligne
            for (int s = 0; s < (depth - i) * 2; ++s)
                std::cout << " ";

            // Affiche tous les nœuds du niveau i
            for (size_t j = 0; j < tree[i].size(); ++j) {
                std::cout << " " << tree[i][j] << "  "; // espace fixe entre les nœuds
            }
            // Final separation between trees
            std::cout << "\n";

            // Affiche les branches / \ sauf pour le dernier niveau
            if (i < depth) {
                for (int s = 0; s < (depth - i) * 2; ++s)
                    std::cout << " ";
                for (size_t j = 0; j < tree[i].size(); ++j) {
                    std::cout << "/ \\ ";
                }
                // Final separation between trees
                //std::cout << "\n";
            }
            std::cout << "\n";
        }
    }

private:
    std::vector<std::vector<T>> tree;
};
