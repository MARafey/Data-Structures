#include <iostream>

template <typename T>
struct Node {
     T data;
     bool color; // true for RED, false for BLACK
     Node<T>* left;
     Node<T>* right;
     Node<T>* parent;

     Node(T data) : data(data), color(true), left(nullptr), right(nullptr), parent(nullptr) {}
};

template <typename T>
class RedBlackTree {
private:
     Node<T>* root;

     Node<T>* insert(Node<T>* node, Node<T>* newNode) {
          if (node == nullptr) {
               return newNode;
          }

          if (newNode->data < node->data) {
               node->left = insert(node->left, newNode);
               node->left->parent = node;
          }
          else if (newNode->data > node->data) {
               node->right = insert(node->right, newNode);
               node->right->parent = node;
          }

          return node;
     }

     void fixTree(Node<T>* node) {
          Node<T>* parent = nullptr;
          Node<T>* grandparent = nullptr;

          while (node != root && node->color != false && node->parent->color == true) {
               parent = node->parent;
               grandparent = parent->parent;

               if (parent == grandparent->left) {
                    Node<T>* uncle = grandparent->right;

                    if (uncle != nullptr && uncle->color == true) {
                         grandparent->color = true;
                         parent->color = false;
                         uncle->color = false;
                         node = grandparent;
                    }
                    else {
                         if (node == parent->right) {
                              rotateLeft(parent);
                              node = parent;
                              parent = node->parent;
                         }

                         rotateRight(grandparent);
                         std::swap(parent->color, grandparent->color);
                         node = parent;
                    }
               }
               else {
                    Node<T>* uncle = grandparent->left;

                    if (uncle != nullptr && uncle->color == true) {
                         grandparent->color = true;
                         parent->color = false;
                         uncle->color = false;
                         node = grandparent;
                    }
                    else {
                         if (node == parent->left) {
                              rotateRight(parent);
                              node = parent;
                              parent = node->parent;
                         }

                         rotateLeft(grandparent);
                         std::swap(parent->color, grandparent->color);
                         node = parent;
                    }
               }
          }

          root->color = false;
     }

     void rotateLeft(Node<T>* node) {
          Node<T>* rightChild = node->right;
          node->right = rightChild->left;

          if (node->right != nullptr) {
               node->right->parent = node;
          }

          rightChild->parent = node->parent;

          if (node->parent == nullptr) {
               root = rightChild;
          }
          else if (node == node->parent->left) {
               node->parent->left = rightChild;
          }
          else {
               node->parent->right = rightChild;
          }

          rightChild->left = node;
          node->parent = rightChild;
     }

     void rotateRight(Node<T>* node) {
          Node<T>* leftChild = node->left;
          node->left = leftChild->right;

          if (node->left != nullptr) {
               node->left->parent = node;
          }

          leftChild->parent = node->parent;

          if (node->parent == nullptr)
          {
               root = leftChild;
          }
          else if (node == node->parent->right) {
               node->parent->right = leftChild;
          }
          else {
               node->parent->left = leftChild;
          }    leftChild->right = node;
          node->parent = leftChild;
     }

     void inorderHelper(Node<T>* node) {
          if (node == nullptr) {
               return;
          }

          inorderHelper(node->left);
          std::cout << node->data << " ";
          inorderHelper(node->right);
     }

     Node<T>* minValueNode(Node<T>* node) {
          while (node->left != nullptr) {
               node = node->left;
          }
          return node;
     }

     Node<T>* deleteNode(Node<T>* node, T data) {
          if (node == nullptr) {
               return node;
          }

          if (data < node->data) {
               node->left = deleteNode(node->left, data);
          }
          else if (data > node->data) {
               node->right = deleteNode(node->right, data);
          }
          else {
               if (node->left == nullptr || node->right == nullptr) {
                    Node<T>* temp = node->left ? node->left : node->right;

                    if (temp == nullptr) {
                         temp = node;
                         node = nullptr;
                    }
                    else {
                         *node = *temp;
                    }

                    delete temp;
               }
               else {
                    Node<T>* temp = minValueNode(node->right);
                    node->data = temp->data;
                    node->right = deleteNode(node->right, temp->data);
               }
          }

          if (node == nullptr) {
               return node;
          }

          fixDelete(node);
          return node;
     }

     void fixDelete(Node<T>* node) {
          if (node == nullptr) {
               return;
          }

          if (node == root) {
               root = nullptr;
               return;
          }

          if (node->color == true || (node->left && node->left->color == true) || (node->right && node->right->color == true)) {
               Node<T>* child = node->left ? node->left : node->right;

               if (node == node->parent->left) {
                    node->parent->left = child;
                    if (child) {
                         child->parent = node->parent;
                    }
                    child->color = false;
               }
               else {
                    node->parent->right = child;
                    if (child) {
                         child->parent = node->parent;
                    }
                    child->color = false;
               }
          }
          else {
               Node<T>* sibling = nullptr;

               while (node != root && (node == nullptr || node->color == false)) {
                    if (node == node->parent->left) {
                         sibling = node->parent->right;

                         if (sibling->color == true) {
                              sibling->color = false;
                              node->parent->color = true;
                              rotateLeft(node->parent);
                              sibling = node->parent->right;
                         }

                         if ((sibling->left == nullptr || sibling->left->color == false) &&
                              (sibling->right == nullptr || sibling->right->color == false)) {
                              sibling->color = true;
                              node = node->parent;
                         }
                         else {
                              if (sibling->right == nullptr || sibling->right->color == false) {
                                   sibling->left->color = false;
                                   sibling->color = true;
                                   rotateRight(sibling);
                                   sibling = node->parent->right;
                              }

                              sibling->color = node->parent->color;
                              node->parent->color = false;
                              if (sibling->right) {
                                   sibling->right->color = false;
                              }
                              rotateLeft(node->parent);
                              node = root;
                         }
                    }
                    else {
                         sibling = node->parent->left;

                         if (sibling->color == true) {
                              sibling->color = false;
                              node->parent->color = true;
                              rotateRight(node->parent);
                              sibling = node->parent->left;
                         }

                         if ((sibling->left == nullptr || sibling->left->color == false) &&
                              (sibling->right == nullptr || sibling->right->color == false)) {
                              sibling->color = true;
                              node = node->parent;
                         }
                         else {
                              if (sibling->left == nullptr || sibling->left->color == false) {
                                   sibling->right->color = false;
                                   sibling->color = true;
                                   rotateLeft(sibling);
                                   sibling = node->parent->left;
                              }

                              sibling->color = node->parent->color;
                              node->parent->color = false;
                              if (sibling->left) {
                                   sibling->left->color = false;
                              }
                              rotateRight(node->parent);
                              node = root;
                         }
                    }
               }

               if (node) {
                    node->color = false;
               }
          }
     }

public:
     RedBlackTree() : root(nullptr) {}
     void insert(const T& data) {
          Node<T>* newNode = new Node<T>(data);
          root = insert(root, newNode);
          fixTree(newNode);
     }
     void deleteNode(const T& data) {
          root = deleteNode(root, data);
     }
     void inorderTraversal() {
          inorderHelper(root);
     }
};