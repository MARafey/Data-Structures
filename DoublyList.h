#pragma once
#include "Node.h"

template <typename T>
class DoublyLinkedList {
public:
     DoublyLinkedList(T val = T()) {
          data = val;
          next = prev = nullptr;
          head = this;
     }

     void Insert_at_head(T val) {
          DoublyLinkedList<T>* new_node = new DoublyLinkedList<T>(val);
          if (this->data == T()) {
               this->data = val;
               return;
          }
          new_node->next = head;
          head->prev = new_node;
          while (head->prev != nullptr) {
               head = head->prev;
          }
     }

     void Insert_at_tail(T val)
     {
          DoublyLinkedList<T>* new_node = new DoublyLinkedList<T>(val);
          if (this->data == T()) {
               this->data = val;
               return;
          }
          while (head->next != nullptr)
          {
               head = head->next;
          }
          head->next = new_node;
          new_node->prev = head;
          while (head->prev != nullptr) {
               head = head->prev;
          }
     }

     void deletion(T val)
     {
          if (Search(val))
          {
               DoublyLinkedList<T>* toDelete;
               if (head->data == val)   // Delete at head
               {
                    toDelete = head;
                    head = head->next;
                    if (head != nullptr) {
                         head->prev = nullptr;
                    }
                    delete toDelete;
                    return;
               }
               DoublyLinkedList<T>* temp = head;
               while (temp->next != nullptr)
               {
                    if (temp->next->data == val) {
                         break;
                    }
                    temp = temp->next;
               }
               if (temp->next->next == nullptr) // Delete at Tail
               {
                    toDelete = temp->next;
                    temp->next = nullptr;
                    delete toDelete;
                    return;
               }
               toDelete = temp->next;
               temp->next = temp->next->next;
               temp->next->prev = temp; // Fix here
               delete toDelete;
          }
          else
          {
               cout << "Value not in List." << endl;
               return;
          }
     }

     bool Search(T val)
     {
          DoublyLinkedList<T>* temp = head;
          while (temp != nullptr)
          {
               if (temp->data == val)
               {
                    return true;
               }
               temp = temp->next;
          }
          return false;
     }

     void display() {
          DoublyLinkedList<T>* temp = head;
          while (temp != nullptr) {
               cout << temp->data << "->";
               temp = temp->next;
          }
          cout << "NULL" << endl;
     }

private:
     T data;
     DoublyLinkedList* next;
     DoublyLinkedList* prev;
     DoublyLinkedList* head;
};
