#pragma once
#include "Node.h"

template <typename T>
class LinkList {
public:
     LinkList() {
          data = Node<T>();
          next = nullptr;
     }

     LinkList(Node<T> d) {
          data = d;
          next = nullptr;
     }

     void insert(Node<T> d) {
          LinkList<T>* newdata = new LinkList<T>(d);
          LinkList<T>* temp = this;
          if (temp->data == INT_MIN) {
               temp->data = d;
               return;
          }
          while (temp->next != nullptr) {
               temp = temp->next;
          }
          temp->next = newdata;
     }

     void delete_from_List(Node<T> d) {
          LinkList<T>* temp = this;
          while (temp->next != nullptr) {
               if (temp->next->data == d) {
                    LinkList<T>* toDelete = temp->next;
                    temp->next = temp->next->next;
                    delete toDelete;
                    return;
               }
               temp = temp->next;
          }
     }

     bool Search(T val)
     {
          LinkList<T>* temp = this;
          while (temp->next != nullptr) {
               if (temp->data.get() == val) {
                    return true;
               }
               temp = temp->next;
          }
          return false;
     }

     void display() {
          LinkList<T>* temp = this;
          while (temp != nullptr) {
               temp->data.display();
               cout << "->";
               temp = temp->next;
          }
          cout << "NULL" << endl;
     }

private:
     Node<T> data;
     LinkList<T>* next;
};
