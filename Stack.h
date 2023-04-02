#pragma once
#include"Node.h"

template <typename T>
class STACK {
public:
     STACK() {
          // Initialize data to default constructed Node and next to nullptr
          data = Node<T>();
          next = nullptr;
     }

     STACK(Node<T> d) {
          // Initialize data to the provided Node and next to nullptr
          data = d;
          next = nullptr;
     }

     void push(Node<T> d) {
          // Create a new STACK object with the provided Node as data
          STACK<T>* newdata = new STACK<T>(d);
          // Make the new object point to the current top of the stack
          newdata->next = this;
          // Update the top of the stack to be the new object
          data = newdata->data;
          next = newdata->next;
     }


     void pop() {
          // Check if there is anything to pop
          if (this != nullptr) {
               // Get the next object in the stack
               STACK<T>* temp = this->next;
               // Delete the current object (which is being popped)
               delete this;
               // Update the top of the stack to be the next object
               this = temp;
          }
     }

     void display() {
          // Start at the top of the stack
          STACK<T>* temp = this;
          // Traverse the stack, printing each element's data
          while (temp != nullptr) {
               temp->data.display();
               cout << "->";
               temp = temp->next;
          }
          cout << "NULL" << endl;
     }

private:
     Node<T> data;
     STACK<T>* next;
};
