// Copyright 2021 NNTU-CS
#ifndef INCLUDE_BST_H_
#define INCLUDE_BST_H_

#include <iostream>
#include <string>
#include <vector>
#include <utility>

template <typename T>
class BST {
 private:
    struct Node {
        T key;
        int count;
        Node* left;
        Node* right;
        Node(T k) : key(k), count(1), left(nullptr), right(nullptr) {}
    };

    Node* root;

    Node* insert(Node* node, T key) {
        if (node == nullptr) {
            return new Node(key);
        }
        if (key < node->key) {
            node->left = insert(node->left, key);
        } else if (key > node->key) {
            node->right = insert(node->right, key);
        } else {
            node->count++;
        }
        return node;
    }

    int depth(Node* node) const {
        if (node == nullptr) {
            return 0;
        }
        int leftDepth = depth(node->left);
        int rightDepth = depth(node->right);
        return 1 + (leftDepth > rightDepth ? leftDepth : rightDepth);
    }

    int search(Node* node, T key) const {
        if (node == nullptr) {
            return 0;
        }
        if (key < node->key) {
            return search(node->left, key);
        } else if (key > node->key) {
            return search(node->right, key);
        } else {
            return node->count;
        }
    }

    void collectNodes(Node* node, std::vector<std::pair<T, int>>& nodes) const {
        if (node != nullptr) {
            collectNodes(node->left, nodes);
            nodes.emplace_back(node->key, node->count);
            collectNodes(node->right, nodes);
        }
    }

 public:
    BST() : root(nullptr) {}

    void insert(T key) {
        root = insert(root, key);
    }

    int depth() const {
        return depth(root);
    }

    int search(T key) const {
        return search(root, key);
    }

    std::vector<std::pair<T, int>> getAllNodes() const {
        std::vector<std::pair<T, int>> nodes;
        collectNodes(root, nodes);
        return nodes;
    }
};

#endif  // BST_H
