#ifndef ITERATOR_H
#define ITERATOR_H

/** \file
 * Iterator definition.
 */

namespace Experiment {
  
  /** Iterator class that works genericly on a List containing Node elements
   * with data of type T.
   *
   * These are created by the lists themselves.
   *
   * \tparam T the type of data held by the Nodes
   * \tparam List the type of list this iterates
   * \tparam Node the type of Node in the list
   */
  template <class T, class List, class Node>
    class Iterator {
  public:
    ~Iterator();
    
    Iterator(List* theList, Node* at);
    Iterator(const Iterator& rhs);
    Iterator& operator=(const Iterator& rhs);
    
  public:
    
    bool operator==(const Iterator& rhs) const;
    bool operator!=(const Iterator& rhs) const;
    
    Iterator& operator++();
    Iterator operator++(int);
    
    Iterator& operator+=(int positions);
    Iterator operator+(int positions);
    
    Iterator& operator--();
    Iterator operator--(int);
    
    Iterator& operator-=(int positions);
    Iterator operator-(int positions);
    
    void swapWith(Iterator& other);
    void moveBefore(Iterator& other);
    
    T& operator*();
    T* operator->();
    
    void swapOccurred(Node* a, Node* b) ;
    void insertedBefore(Node* after, int count);
    void removedBefore(Node* after, int count);
    
  private:
    /** The list we are iterating to trigger iterator notifications on */
    List* list;

    /** The current Node we are pointing at */
    Node *current;
  };

  /** Swap the values at a and b.
   *
   * \param a the Iterator to swap values with b
   * \param b the Iterator to swap values with a
   *
   * \tparam T the type of data held by the Nodes
   * \tparam List the type of list this iterates
   * \tparam Node the type of Node in the list
   */
  template <class T, class List, class Node>
    void swap(Iterator<T, List, Node>& a, Iterator<T, List, Node>& b ) {
    a.swapWith(b);
  }
  
  /** Move the value at a before b.
   *
   * \param a the Iterator to move the value of before b
   * \param b the Iterator to move the value of a before
   *
   * \tparam T the type of data held by the Nodes
   * \tparam List the type of list this iterates
   * \tparam Node the type of Node in the list
   */
  template <class T, class List, class Node>
    void moveBefore( Iterator<T, List, Node> & a, Iterator<T, List, Node> & b ) {
    a.moveBefore(b);
  }
  
} // namespace Experiment

#include "Iterator.cpp"

#endif // ITERATOR_H
