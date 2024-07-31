/*
Copyright (c) 2013, Komodo Does Inc
All rights reserved.

Redistribution and use in source and binary forms, with or without modification, are permitted provided that the following conditions are met:

- Redistributions of source code must retain the above copyright notice, this list of conditions and the following disclaimer.
- Redistributions in binary form must reproduce the above copyright notice, this list of conditions and the following disclaimer in the documentation and/or other materials provided with the distribution.
- Neither the name of the Komodo Does Inc nor the names of its contributors may be used to endorse or promote products derived from this software without specific prior written permission.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

#ifndef ITERATOR_CPP
#define ITERATOR_CPP

/**
 * This file is to be included at the end of Iterator.h
 */

namespace Experiment {

  /** Destroy iterator */
  template<typename T, typename List, typename Node>
  Iterator<T, List, Node>::~Iterator() {
    list->removeIterator(this);
  }

  /** Create Iterator for theList at the value of at
   *
   * \param theList to iterate
   * \param at start iterating from at
   */
  // \todo Concel from public access
  template<typename T, typename List, typename Node>
  Iterator<T, List, Node>::Iterator(List* theList, Node* at)
    : list(theList), current(at)
  {
    list->addIterator(this);
  }

  /** Create Iterator at the same position of the same list as rhs
   *
   * \param rhs to create at the same position of the same list as
   */
  template<typename T, typename List, typename Node>
  Iterator<T, List, Node>::Iterator(const Iterator& rhs)
    : list(rhs.list), current(rhs.current)
  {
    list->addIterator(this);
  }

  /** Update Iterator to be at the same position of the same list as rhs
   *
   * \param rhs to update to the the same position of the same list as
   */
  template<typename T, typename List, typename Node>
  Iterator<T, List, Node>& Iterator<T, List, Node>::operator=(const Iterator& rhs)
  {
    list->removeIterator(this);

    list = rhs.list;
    current = rhs.current;

    list->addIterator(this);

    return *this;
  }
  
  /** \return true if this iterator is at the same position in the same list as rhs,
   * otherwise false
   *
   * \param rhs to compare position against
   */
  template<typename T, typename List, typename Node>
  bool Iterator<T, List, Node>::operator==(const Iterator& rhs) const {
    return rhs.current == current;
  }
  
  /** \return true if this iterator is not at the same position in the same list as rhs,
   * otherwise false
   *
   * \param rhs to compare position against
   */
  template<typename T, typename List, typename Node>
  bool Iterator<T, List, Node>::operator!=(const Iterator& rhs) const {
    return !(*this == rhs);
  }

  /** Advance this iterator one position and return this iterator.
   *
   * \return this iterator after advancement
   */
  template<typename T, typename List, typename Node>
  Iterator<T, List, Node>& Iterator<T, List, Node>::operator++() {
    current = current->getNext();
    return *this;
  }
  
  /** Advance this iterator one position and return a temporary iterator at the
   * original position.
   *
   * \return the temporary iterator at the original position
   */
  template<typename T, typename List, typename Node>
  Iterator<T, List, Node> Iterator<T, List, Node>::operator++(int) {
    Iterator copy(list, current);
    current = current->getNext();
    return copy;
  }

  /** Advance this iterator positions, if possible, and return this iterator
   *
   * \param positions to advance
   *
   * \return this iterator
   */
  template<typename T, typename List, typename Node>
  Iterator<T, List, Node>& Iterator<T, List, Node>::operator+=(int positions) {
    if(positions < 0) {
      positions = -positions;
      for(int i = 0; i < positions; ++i) {
	current = current->getPrevious();
      }
    } else {
      for(int i = 0; i < positions; ++i) {
	current = current->getNext();
      }
    }
    return *this;
  }

  /** \return an Iterator advanced positions from this iterator
   *
   * \param positions to advance the returned iterator
   */
  template<typename T, typename List, typename Node>
  Iterator<T, List, Node> Iterator<T, List, Node>::operator+(int positions) {
    Iterator<T, List, Node> iter(list, current);
    iter += positions;
    return iter;
  }
    
  /** Decrement this iterator one position and return this iterator.
   *
   * \return this iterator after decrement
   */
  template<typename T, typename List, typename Node>
  Iterator<T, List, Node>& Iterator<T, List, Node>::operator--() {
    current = current->getPrevious();
    return *this;
  }
    
  /** Decrement this iterator one position and return a temporary iterator at the
   * original position.
   *
   * \return the temporary iterator at the original position
   */
  template<typename T, typename List, typename Node>
  Iterator<T, List, Node> Iterator<T, List, Node>::operator--(int) {
    Iterator copy(list, current);
    current = current->getPrevious();
    return copy;
  }
    
  /** Decrement this iterator positions, if possible, and return this iterator
   *
   * \param positions to advance
   *
   * \return this iterator
   */
  template<typename T, typename List, typename Node>
  Iterator<T, List, Node>& Iterator<T, List, Node>::operator-=(int positions) {
    (*this) += -positions;
    return *this;
  }
    
  /** \return an Iterator decremented positions from this iterator
   *
   * \param positions to decrement the returned iterator
   */
  template<typename T, typename List, typename Node>
  Iterator<T, List, Node> Iterator<T, List, Node>::operator-(int positions) {
    Iterator iter(list, current);
    iter -= positions;
    return iter;
  }
  
  /** Swap the values at this and other iterators
   *
   * \param other iterator to swap values with
   */
  template<typename T, typename List, typename Node>
  void Iterator<T, List, Node>::swapWith(Iterator<T, List, Node>& other) {
    if(!current->valid() || !other.current->valid()) {
      return;
    }
      
    current->swapWith(other.current);
    list->notifyItersSwapOccurred(current, other.current);
  }
    
  /** Move the value at this itherator before the value at other
   *
   * \param other iterator to move the value of this iterator before
   */
  template<typename T, typename List, typename Node>
  void Iterator<T, List, Node>::moveBefore(Iterator<T, List, Node>& other) {
    if(!current->valid()) {
      return;
    }
      
    Node* next = current->getNext();
    current->moveBefore(other.current);
      
    other.list->notifyItersInsertedBefore(1, current->getNext());
    list->notifyItersRemovedBefore(1, next);

    *this = list->end();
  }
   
  /** @return the value at this iterator, if any
   *
   * \throw std::out_of_range if this is not at a valid position
   */
  template<typename T, typename List, typename Node>
  T& Iterator<T, List, Node>::operator*() {
    if(NULL == current) {
      throw std::out_of_range("this position has no value");
    }
      
    return **current;
  }
  
  /** @return a pointer to the value at this iterator, if any
   *
   * \throw std::out_of_range if this is not at a valid position
   */
  template<typename T, typename List, typename Node>
  T* Iterator<T, List, Node>::operator->() {
    return &operator*();
  }

  /** Update this iterator, if appropriate, that the values at a and b
   * swapped positions.
   *
   * \param a Node that swapped with b
   * \param b Node that swapped with a
   *
   * \todo Conceal from public access.
   */
  template<typename T, typename List, typename Node>
  void Iterator<T, List, Node>::swapOccurred(Node* a, Node* b) {
    if(a == current) {
      current = b;
    } else if(b == current) {
      current = a;
    }
  }
    
  /** Update this iterator, if appropriate, that count positions were added before
   * after
   *
   * \param count of items inserted before after
   * \param after node that has had count items added before it
   *
   * \todo Conceal from public access.
   */
  template<typename T, typename List, typename Node>
  void Iterator<T, List, Node>::insertedBefore(Node* after, int count) {
    if(after == current) {
      (*this) -= count;
    }
  }
    
  /** Update this iterator, if appropriate, that count positions were removed before
   * after
   *
   * \param count of items removed before after
   * \param after node that has had count items removed before it
   *
   * \todo Conceal from public access.
   */
  template<typename T, typename List, typename Node>
  void Iterator<T, List, Node>::removedBefore(Node* after, int count) {
    if(after == current) {
      (*this) += count;
    }
  }

} // namespace Experiment

#endif // ITERATOR_CPP
