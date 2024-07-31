/*
Copyright (c) 2013, Komodo Does Inc
All rights reserved.

Redistribution and use in source and binary forms, with or without modification, are permitted provided that the following conditions are met:

- Redistributions of source code must retain the above copyright notice, this list of conditions and the following disclaimer.
- Redistributions in binary form must reproduce the above copyright notice, this list of conditions and the following disclaimer in the documentation and/or other materials provided with the distribution.
- Neither the name of the Komodo Does Inc nor the names of its contributors may be used to endorse or promote products derived from this software without specific prior written permission.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

#ifndef DOUBLE_LINKED_LIST_CPP
#define DOUBLE_LINKED_LIST_CPP

/** \file
 *
 * Implementations of longer template methods of the DoubleLinkedList.h file.
 *
 * \note This file to be included at the end of DoubleLinkedList.h
 */

namespace Experiment {

  /** Destroy a list.
   *
   * \note If the value_type is a pointer, the pointers will not be deleted.
   */
  template<typename T>
  DoubleLinkedList<T>::~DoubleLinkedList() {
    // Delete all the Nodes
    clear();
    
    // Delete all the Iterator-containing Nodes
    IterNode* iterNode = iterHead.getNext();
    while(NULL != iterNode) {
      IterNode* tmp = iterNode;
      iterNode = iterNode->getNext();
      delete tmp;
    }
  }
  
  /** Create a new list. */
  template<typename T>
  DoubleLinkedList<T>::DoubleLinkedList()
  {
    // Setup the marker nodes such that head <-> tail and the previous
    // of head is itself and the next of tail is itself.  This allows
    // iterators to move indefinitely "past" the end of a list to itself.
    head.setPrevious(&head);
    head.setNext(&tail);
    tail.setPrevious(&head);
    tail.setNext(&tail);
  }
  
  /** Copy data from another list.
   *
   * @param rhs to copy from
   */
  template<typename T>
  DoubleLinkedList<T>::DoubleLinkedList(const DoubleLinkedList& rhs) {
    // Setup the marker nodes such that head <-> tail and the previous
    // of head is itself and the next of tail is itself.  This allows
    // iterators to move indefinitely "past" the end of a list to itself.
    head.setPrevious(&head);
    head.setNext(&tail);
    tail.setPrevious(&head);
    tail.setNext(&tail);
    
    // Copy all data from rhs
    for(Node* node = rhs.head.getNext(); &rhs.tail != node; node = node->getNext()) {
      push_back(node->operator*());
    }
    
    // Do not copy iterators
  }

  /** Remove all data from this list.
   *
   * \note If the value_type is a pointer, the pointers will not be deleted.
   */
  template<typename T>
  void DoubleLinkedList<T>::clear() {
    // Swap all to tail (as far as the iterators are concerned) and delete Node
    Node* curr = head.getNext();
    while(curr != &tail) {
      Node* tmp = curr;
      notifyItersSwapOccurred(tmp, &tail);
      curr = curr->getNext();
      delete tmp;
    }

    // Link head <-> tail
    head.setNext(&tail);
    tail.setPrevious(&head);
  }

  /** \return true if this list has not data, otherwise false */
  template<typename T>
  bool DoubleLinkedList<T>::isEmpty() const {
    return head.getNext() == &tail;
  }

  /** \return an iterator pointing to the first element of this list
   *
   * \note isEmpty() returns true if begin() == end()
   */
  template<typename T>
  typename DoubleLinkedList<T>::iterator DoubleLinkedList<T>::begin() {
    return iterator(this, head.getNext());
  }
  
  /** \return an iterator pointing beyond the last element of this list
   *
   * \note isEmpty() returns true if begin() == end()
   */
  template<typename T>
  typename DoubleLinkedList<T>::iterator DoubleLinkedList<T>::end() {
    return iterator(this, &tail);
  }

  /** Insert value as the first item in this list and udpate iterators to remain
   * at same position.
   *
   * \param value to insert at the start of the list
   */
  template<typename T>
  void DoubleLinkedList<T>::push_front(const value_type& value) {
    DataNode* created = new DataNode(value, &head, head.getNext());
    head.getNext()->setPrevious(created);
    head.setNext(created);
    
    notifyItersInsertedBefore(1, created->getNext());
  }

  /** Insert value as the last item in this list */
  template<typename T>
  void DoubleLinkedList<T>::push_back(const value_type& value) {
    DataNode* created = new DataNode(value, tail.getPrevious(), &tail);
    tail.getPrevious()->setNext(created);
    tail.setPrevious(created);

    // No need to notify of inserts since there were no elements we added before
  }

  /** Record that iter has been created as an iterator of this list.
   *
   * \param iter to add
   *
   * \todo Conceal this from public access
   */
  template<typename T>
  void DoubleLinkedList<T>::addIterator(iterator* iter) {
    IterDataNode* created = new IterDataNode(iter, &iterHead, iterHead.getNext());
    if(NULL != iterHead.getNext()) {
      iterHead.getNext()->setPrevious(created);
    }
    iterHead.setNext(created);
  }

  /** Record that iter that is being destroyed as an iterator of this list.
   *
   * \param iter to remove
   *
   * \todo Conceal this from public access
   */
  template<typename T>
  void DoubleLinkedList<T>::removeIterator(iterator* iter) {
    for(IterNode* curr = iterHead.getNext(); NULL != curr; curr = curr->getNext()) {
      iterator* atCurr = curr->operator*();
      if(iter == atCurr) {
	curr->getPrevious()->setNext(curr->getNext());
	if(NULL != curr->getNext()) {
	  curr->getNext()->setPrevious(curr->getPrevious());
	}
	delete curr;
	return;
      }
    }
  }

  /** Notify all iterators that a swap occurred of nodes a and b so that they can update
   * themselves to keep the same position.
   *
   * Since only a and b are altered, we note this so all other iterators can disregard.
   *
   * \param a that swapped position with b
   * \param b that swapped position with a
   *
   * \note This comes from iter rather than Node because Node doesn't know about list
   *
   * \todo Conceal this from public access
   */
  template<typename T>
  void DoubleLinkedList<T>::notifyItersSwapOccurred(Node* a, Node* b) const {
     for(IterNode* curr = iterHead.getNext(); NULL != curr; curr = curr->getNext()) {
       curr->operator*()->swapOccurred(a, b);
     }
  }

  /** Notify all iterators that count Nodes were inserted before firstAfter.
   *
   * Notifies each iterator that each node from firstAfter that has been moved count times.
   *
   * \param count number of nodes added
   * \param firstAfter first node after the added nodes to update from
   *
   * \note This comes from iter rather than Node because Node doesn't know about list
   *
   * \todo Conceal this from public access
   */
  template<typename T>
  void DoubleLinkedList<T>::notifyItersInsertedBefore(int count, Node* firstAfter) const {
    for(Node* node = firstAfter; node != &tail; node=node->getNext()) {
      for(IterNode* curr = iterHead.getNext(); NULL != curr; curr = curr->getNext()) {
	curr->operator*()->insertedBefore(node, count);
      }
    }
  }

  /** Notify all iterators that count Nodes were removed before firstAfter.
   *
   * Notifies each iterator that each node from firstAfter to move count times.
   *
   * \param count number of nodes removed
   * \param firstAfter first node after the removed nodes to update from
   *
   * \note This comes from iter rather than Node because Node doesn't know about list
   *
   * \todo Conceal this from public access
   */
  template<typename T>
  void DoubleLinkedList<T>::notifyItersRemovedBefore(int count, Node* firstAfter) const {
    for(Node* node = firstAfter; node != &tail; node=node->getNext()) {
      for(IterNode* curr = iterHead.getNext(); NULL != curr; curr = curr->getNext()) {
	curr->operator*()->removedBefore(node, count);
      }
    }
  }

} // namespace Experiment

#endif // DOUBLE_LINKED_LIST_CPP
