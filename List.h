#ifndef LIST_H
#define LIST_H
/* List.h
 *
 * doubly-linked, double-ended list with Iterator interface
 * Project UID c1f28c309e55405daf00c565d57ff9ad
 * EECS 280 Project 4
 */

#include <iostream>
#include <cassert> //assert
#include <cstddef> //NULL


template <typename T>
class List {
  //OVERVIEW: a doubly-linked, double-ended list with Iterator interface
public:

  //EFFECTS:  returns true if the list is empty
  bool empty() const;

  //EFFECTS: returns the number of elements in this List
  //HINT:    Traversing a list is really slow.  Instead, keep track of the size
  //         with a private member variable.  That's how std::list does it.
  int size() const;

  //REQUIRES: list is not empty
  //EFFECTS: Returns the first element in the list by reference
  T & front();

  //REQUIRES: list is not empty
  //EFFECTS: Returns the last element in the list by reference
  T & back();

  //EFFECTS:  inserts datum into the front of the list
  void push_front(const T &datum);

  //EFFECTS:  inserts datum into the back of the list
  void push_back(const T &datum);

  //REQUIRES: list is not empty
  //MODIFIES: may invalidate list iterators
  //EFFECTS:  removes the item at the front of the list
  void pop_front();

  //REQUIRES: list is not empty
  //MODIFIES: may invalidate list iterators
  //EFFECTS:  removes the item at the back of the list
  void pop_back();

  //MODIFIES: may invalidate list iterators
  //EFFECTS:  removes all items from the list
  void clear();

  // You should add in a default constructor, destructor, copy constructor,
  // and overloaded assignment operator, if appropriate. If these operations
  // will work correctly without defining these, you can omit them. A user
  // of the class must be able to create, copy, assign, and destroy Lists
  List() : first(nullptr), last(nullptr), sizeofList(0) { }

  List(const List &other)
  : first(nullptr), last(nullptr), sizeofList(0) {
    copy_all(other);
  }

  ~List() {
    clear();
  }

  List<T> & operator=(const List<T> &rhs) {
    first = nullptr;
    last = nullptr;
    sizeofList = 0;

    copy_all(rhs);

    return *this;
  }

private:
  //a private type
  struct Node {
    Node *next;
    Node *prev;
    T datum;
  };

  //REQUIRES: list is empty
  //EFFECTS:  copies all nodes from other to this
  void copy_all(const List<T> &other);

  Node *first;   // points to first Node in list, or nullptr if list is empty
  Node *last;    // points to last Node in list, or nullptr if list is empty
  int sizeofList;
public:
  ////////////////////////////////////////
  class Iterator {
    //OVERVIEW: Iterator interface to List

    // You should add in a default constructor, destructor, copy constructor,
    // and overloaded assignment operator, if appropriate. If these operations
    // will work correctly without defining these, you can omit them. A user
    // of the class must be able to create, copy, assign, and destroy Iterators.

    // Your iterator should implement the following public operators: *,
    // ++ (prefix), default constructor, == and !=.

  public:
    // This operator will be used to test your code. Do not modify it.
    // Requires that the current element is dereferenceable.
    Iterator& operator--() {
      assert(node_ptr);
      node_ptr = node_ptr->prev;
      return *this;
    }

    T & operator*() const {
      assert(node_ptr);
      return node_ptr->datum;
    }

    Iterator & operator++() {
      assert(node_ptr);
      node_ptr = node_ptr->next;
      return *this;
    }

    bool operator==(Iterator rhs) const {
      return node_ptr == rhs.node_ptr;
    }

    bool operator!=(Iterator rhs) const {
      return node_ptr != rhs.node_ptr;
    }


    Iterator()
    : node_ptr(nullptr) { }

  private:
    Node *node_ptr; //current Iterator position is a List node
    // add any additional necessary member variables here

    // add any friend declarations here
    friend class List;
    // construct an Iterator at a specific position
    Iterator(Node *np)
    : node_ptr(np) { }

  };//List::Iterator
  ////////////////////////////////////////

  // return an Iterator pointing to the first element
  Iterator begin() const {
    return Iterator(first);
  }

  // return an Iterator pointing to "past the end"

  Iterator end() const {
    return Iterator();
  }
  
  /*Iterator end() const {
    Iterator iter(first);
    for (int i = 0; i < sizeofList; ++i) {
      ++iter;
    }
    return iter;
  } */

  //REQUIRES: i is a valid, dereferenceable iterator associated with this list
  //MODIFIES: may invalidate other list iterators
  //EFFECTS: Removes a single element from the list container
  void erase(Iterator i);

  //REQUIRES: i is a valid iterator associated with this list
  //EFFECTS: inserts datum before the element at the specified position.
  void insert(Iterator i, const T &datum);

};//List


////////////////////////////////////////////////////////////////////////////////
// Add your member function implementations below or in the class above
// (your choice). Do not change the public interface of List, although you
// may add the Big Three if needed.  Do add the public member functions for
// Iterator.

//EFFECTS:  returns true if the list is empty
template <typename T>
bool List<T>::empty() const {
  return sizeofList == 0;
}

//EFFECTS: returns the number of elements in this List
//HINT:    Traversing a list is really slow.  Instead, keep track of the size
//         with a private member variable.  That's how std::list does it.
template <typename T>
int List<T>::size() const {
  return sizeofList;
}

//REQUIRES: list is not empty
//EFFECTS: Returns the first element in the list by reference
template <typename T>
T & List<T>::front() {
  assert(!empty());
  return first->datum;
}

//REQUIRES: list is not empty
//EFFECTS: Returns the last element in the list by reference
template <typename T>
T & List<T>::back() {
  assert(!empty());
  return last->datum;
}

//EFFECTS:  inserts datum into the front of the list
template <typename T>
void List<T>::push_front(const T &datum) {
  Node *p = new Node;
  p->datum = datum;
  p->next = first;
  p->prev = nullptr;

  if (empty()) {
    first = p;
    last = p;
    sizeofList += 1;
  }
  else {
    first->prev = p;
    first = p;
    sizeofList += 1;
  }
}

//EFFECTS:  inserts datum into the back of the list
template <typename T>
void List<T>::push_back(const T &datum) {
  Node *p = new Node;
  p->datum = datum;
  p->next = nullptr;
  p->prev = last;
  if (empty()) {
    first = p;
    last = p;
    sizeofList += 1;
  }
  else {
    last->next = p;
    last = p;
    sizeofList += 1;
  }
}

//REQUIRES: list is not empty
//MODIFIES: may invalidate list iterators
//EFFECTS:  removes the item at the front of the list
template <typename T>
void List<T>::pop_front() {
  assert(!empty());
  Node *victim = first;
  first = first->next;
  if (sizeofList > 1) {
    first->prev = nullptr;
  }
  delete victim;
  sizeofList -= 1;
}

//REQUIRES: list is not empty
//MODIFIES: may invalidate list iterators
//EFFECTS:  removes the item at the back of the list
template <typename T>
void List<T>::pop_back() {
  assert(!empty());
  Node *victim = last;
  last = last->prev;
  if (sizeofList > 1) {
    last->next = nullptr;
  }
  delete victim;
  sizeofList -= 1;
}

//MODIFIES: may invalidate list iterators
//EFFECTS:  removes all items from the list
template <typename T>
void List<T>::clear() {
  while (!empty()) {
    pop_front();
  }
  sizeofList = 0;
}

//REQUIRES: list is empty
//EFFECTS:  copies all nodes from other to this
template <typename T>
void List<T>::copy_all(const List<T> &other) {
  for (Node *np = other.first; np; np = np->next) {
    push_back(np->datum);
  }
  sizeofList = other.size();
}

//REQUIRES: i is a valid, dereferenceable iterator associated with this list
//MODIFIES: may invalidate other list iterators
//EFFECTS: Removes a single element from the list container
template <typename T>
void List<T>::erase(Iterator i) {
  if (i == first) {
    pop_front();
  }
  else if (i == last) {
    pop_back();
  }
  else {
    Node *victim = i.node_ptr;
    Node *N_BforV = victim->prev;
    Node *N_AftrV = victim->next;
    N_BforV->next = N_AftrV;
    N_AftrV->prev = N_BforV;
    delete victim;
    sizeofList -= 1;
  }
}

//REQUIRES: i is a valid iterator associated with this list
//EFFECTS: inserts datum before the element at the specified position.
template <typename T>
void List<T>::insert(Iterator i, const T &datum) {
  Iterator iter;
  if (i == first) {
    push_front(datum);
  }
  else if (i == iter) {
    push_back(datum);
  }
  else {
    Node *provided_node = i.node_ptr;
    Node *prev_node = provided_node->prev;
    Node *p = new Node;
    p->datum = datum;
    p->next = provided_node;
    p->prev = prev_node;
    prev_node->next = p;
    provided_node->prev = p;
    sizeofList += 1;
  }
}

#endif // Do not remove this. Write all your code above this line.
