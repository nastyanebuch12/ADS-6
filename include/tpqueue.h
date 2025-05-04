// Copyright 2022 NNTU-CS
#ifndef INCLUDE_TPQUEUE_H_
#define INCLUDE_TPQUEUE_H_
#pragma once
#include <stdexcept>

template<typename T>
class TPQueue {
 private:
  struct Item {
   T data;
   Item *next;
   explicit Item(T data) : data(data), next(nullptr) {}
  };
  Item *head, *tail;

 public:
  TPQueue() : head(nullptr), tail(nullptr) {}
  ~TPQueue() {
    while (head) {
      Item *temp = head;
      head = head->next;
      delete temp;
    }
  }

  void push(T value) {
    Item* newItem = new Item(value);
    if (!head || value.prior > head->data.prior) {
      newItem->next = head;
      head = newItem;
      if (!tail) tail = head;
      return;
    }
    Item* current = head;
    while (current->next && current->next->data.prior >= value.prior) {
      current = current->next;
    }
    newItem->next = current->next;
    current->next = newItem;
    if (!newItem->next) {
      tail = newItem;
    }
  }

  T pop() {
    if (!head) {
      throw std::runtime_error("Empty!");
    }
    Item* temp = head;
    T result = temp->data;
    head = head->next;
    if (!head) {
      tail = nullptr;
    }
    delete temp;
    return result;
  }
};

struct SYM {
  char ch;
  int prior;
};

#endif  // INCLUDE_TPQUEUE_H_
