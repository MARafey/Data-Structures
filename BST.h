#pragma once
#include <iostream>

using namespace std;

template <typename T>
struct Node {
     T data;
     Node* left;
     Node* right;

     Node(const T& data) : data(data), left(nullptr), right(nullptr) {}
};


template <typename T>
class BST {
public:
     BST() : root_(nullptr) {}

     ~BST() {
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

     Node* insert(Node* node, const T& item) {
          if (node == nullptr) {
               node = new Node(item);
          }
          else if (item < node->data) {
               node->left = insert(node->left, item);
          }
          else if (item > node->data) {
               node->right = insert(node->right, item);
          }
          return node;
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
               if (node->left == nullptr && node->right == nullptr) {
                    delete node;
                    node = nullptr;
               }
               else if (node->left == nullptr) {
                    Node* temp = node;
                    node = node->right;
                    delete temp;
               }
               else if (node->right == nullptr) {
                    Node* temp = node;
                    node = node->left;
                    delete temp;
               }
               else {
                    Node* successor = node->right;
                    while (successor->left != nullptr) {
                         successor = successor->left;
                    }
                    node->data = successor->data;
                    node->right = remove(node->right, successor->data);
               }
          }
          return node;
     }

     void display(Node* node) const {
          if (node != nullptr) {
               display(node->left);
               cout << node->data << " ";
               display(node->right);
          }
     }
};
