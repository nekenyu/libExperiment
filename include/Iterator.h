/*
Copyright (c) 2013, Komodo Does Inc
All rights reserved.

Redistribution and use in source and binary forms, with or without modification, are permitted provided that the following conditions are met:

- Redistributions of source code must retain the above copyright notice, this list of conditions and the following disclaimer.
- Redistributions in binary form must reproduce the above copyright notice, this list of conditions and the following disclaimer in the documentation and/or other materials provided with the distribution.
- Neither the name of the Komodo Does Inc nor the names of its contributors may be used to endorse or promote products derived from this software without specific prior written permission.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

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
