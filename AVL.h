#pragma once
#include <iostream>
#include <algorithm>

using namespace std;

template <typename T>
struct Node {
     T data;
     Node* left;
     Node* right;
     int height;

     Node(const T& data) : data(data), left(nullptr), right(nullptr), height(0) {}
};


template <typename T>
class AVLTree {
public:
     AVLTree() : root_(nullptr) {}

     ~AVLTree() {
          clear(root_);
     }

     void insert(const T& item) {
          root_ = insert(root_, item);
     }

     bool contains(const T& item) const {
          return contains(root_, item);
     }

     void remove(const T& item) {
          root_ = remove(root_, item);
     }

     void display() const {
          display(root_);
          cout << endl;
     }

private:
     Node* root_;

     Node* clear(Node* node) {
          if (node != nullptr) {
               node->left = clear(node->left);
               node->right = clear(node->right);
               delete node;
               node = nullptr;
          }
          return node;
     }

     int height(Node* node) const {
          return node == nullptr ? -1 : node->height;
     }

     int balanceFactor(Node* node) const {
          return height(node->right) - height(node->left);
     }

     void fixHeight(Node* node) {
          node->height = 1 + max(height(node->left), height(node->right));
     }

     Node* rotateRight(Node* node) {
          Node* leftChild = node->left;
          node->left = leftChild->right;
          leftChild->right = node;
          fixHeight(node);
          fixHeight(leftChild);
          return leftChild;
     }

     Node* rotateLeft(Node* node) {
          Node* rightChild = node->right;
          node->right = rightChild->left;
          rightChild->left = node;
          fixHeight(node);
          fixHeight(rightChild);
          return rightChild;
     }

     Node* balance(Node* node) {
          fixHeight(node);
          if (balanceFactor(node) == 2) {
               if (balanceFactor(node->right) < 0) {
                    node->right = rotateRight(node->right);
               }
               return rotateLeft(node);
          }
          else if (balanceFactor(node) == -2) {
               if (balanceFactor(node->left) > 0) {
                    node->left = rotateLeft(node->left);
               }
               return rotateRight(node);
          }
          return node;
     }

     Node* insert(Node* node, const T& item) {
          if (node == nullptr) {
               return new Node(item);
          }
          else if (item < node->data) {
               node->left = insert(node->left, item);
          }
          else if (item > node->data) {
               node->right = insert(node->right, item);
          }
          return balance(node);
     }

     bool contains(Node* node, const T& item) const {
          if (node == nullptr) {
               return false;
          }
          else if (item == node->data) {
               return true;
          }
          else if (item < node->data) {
               return contains(node->left, item);
          }
          else {
               return contains(node->right, item);
          }
     }

     Node* findMin(Node* node) const {
          if (node->left == nullptr) {
               return node;
          }
          else {
               return findMin(node->left);
          }
     }

     Node* remove(Node* node, const T& item) {
          if (node == nullptr) {
               return node;
          }
          else if (item < node->data) {
               node->left = remove(node->left, item);
          }
          else if (item > node->data) {
               node->right = remove(node->right, item);
          }
          else {
               Node* leftChild = node->left;
               Node* rightChild = node->right;
               delete node;
               if (rightChild == nullptr) {
                    return leftChild;
               }
               Node* minNode = findMin(rightChild);
               minNode->right = removeMin(rightChild);
               minNode->left = leftChild;
               return balance(minNode);
          }
          return balance(node);
     }

     void display(Node* node) const {
          if (node != nullptr) {
               display(node->left);
               cout << node->data << " ";
               display(node->right);
          }
     }

};