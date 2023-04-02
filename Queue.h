#pragma once
#include <iostream>
using namespace std;

template <typename T>
struct Node {
     T data;
     Node* next;

     Node(const T& data) : data(data), next(nullptr) {}
};

template <typename T>
class Queue {
public:
     Queue() : size_(0), front_(nullptr), back_(nullptr) {}

     ~Queue() {
          while (!empty()) {
               dequeue();
          }
     }

     void enqueue(const T& item) {
          Node* new_node = new Node(item);
          if (empty()) {
               front_ = back_ = new_node;
          }
          else {
               back_->next = new_node;
               back_ = new_node;
          }
          ++size_;
     }

     T dequeue() {
          if (empty()) {
               cout << "Error: queue is empty" << endl;
               return;
          }
          T item = front_->data;
          Node* temp = front_;
          front_ = front_->next;
          delete temp;
          --size_;
          if (empty()) {
               back_ = nullptr;
          }
          return item;
     }

     bool empty()  {
          return size_ == 0;
     }

     int size()  {
          return size_;
     }

     T front()  {
          if (empty()) {
               cout << "Error: queue is empty" << endl;
               exit(1);
          }
          return front_->data;
     }

     T back()  {
          if (empty()) {
               cout << "Error: queue is empty" << endl;
               exit(1);
          }
          return back_->data;
     }

     void display()  {
          Node* current = front_;
          while (current != nullptr) {
               cout << current->data << " ";
               current = current->next;
          }
          cout << endl;
     }

private:
     int  size_;
     Node* front_;
     Node* back_;
};
