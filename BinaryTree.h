#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <sstream>

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
    
    /// <summary>
    /// This function is used to create a block of width (we always take 8 cause that is what we put in display)
    /// so that every number no matter there amount of character will be consider as a block of 8 char
    /// and so like that it will be eazy to adjust the spaces for the / and \ to allign well
    /// </summary>
    /// <param name="val"></param>
    /// <param name="width"></param>
    /// <returns></returns>
    std::string reformating(T val, int width) {
        std::stringstream ss;   // we convert the value into an int/double (using only a string with tostring wasn't working because it was putting like 6 decimals after the end)
        ss << val;
        std::string s = ss.str();   //Now we can take it as a normal string because and it will have correct form

        // If the number is too big we return it like it was and it will look like a bad tree,
        // But honestly don't think it is possible to have more than 8 numbers. And if there is too much after the "," it will remove the one that goes a bit too far anyways
        if (s.length() >= width) return s;

        // We calculate the space available in the 8 caracter box we want to do
        int diff = width - s.length();
        // We want to center the number in the box so we put half the spaces on the left
        int spaces_left = diff / 2;
        //And then we put the rest in the right side (note that we didn't do diff/2 again because of the approximation of / could have ended up with 1 more or one less " "
        int spaces_right = diff - spaces_left;

        std::string result = "";

        // we add the left spaces
        for (int i = 0; i < spaces_left; i++) {
            result += " ";
        }

        // we add the number
        result += s;

        // finally we add the right spaces
        for (int i = 0; i < spaces_right; i++) {
            result += " ";
        }

        return result;
    }

    void display() {
        int width = 8; // We define a fix width for the block for the reformating function (8 seems like a nice option)

        //just to don't have the tree all touching each other and have a clearer view
        std::cout << "\n";
        std::cout << "\n";
        std::cout << "Display of the tree : ";
        std::cout << "\n";
        std::cout << "\n";


        // we start from the top at 0 to the bottom which is the depth
        for (int i = 0; i <= depth; ++i) {
            
            //We need to start the tree not at the left but in the middle so we shift it
            // the logic is that if we are at start of a tree with depth 5
            // (5 - 0) * (8 / 2) = 5 * 4 = 20 spaces
            int indent = (depth - i) * (width / 2);

            // Now we print the indent that we calculated
            for (int k = 0; k < indent; ++k) {
                std::cout << " ";
            }

            // We for a for through the level at the current level
            for (size_t j = 0; j < tree[i].size(); ++j) {
                // We put the reformated value (block of 8 character)
                // It centers the number for exemple something like "  3.14  "
                std::cout << reformating(tree[i][j], width);
            }
            std::cout << "\n";

            //need to check if we reached the end of the tree before printing the "/ \"
            if (i < depth) {
                // We need to indent the start of the row of branchs now (similar to first number of the row of numbers)
                for (int k = 0; k < indent - 1; ++k) {
                    std::cout << " ";
                }

                for (size_t j = 0; j < tree[i].size(); ++j) {
                    std::cout << "  /   \\ "; 
                }
                std::cout << "\n";
            }
        }
    }

private:
    std::vector<std::vector<T>> tree;
};
