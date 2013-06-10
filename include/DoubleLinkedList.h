/*
Copyright (c) 2013, Komodo Does Inc
All rights reserved.

Redistribution and use in source and binary forms, with or without modification, are permitted provided that the following conditions are met:

- Redistributions of source code must retain the above copyright notice, this list of conditions and the following disclaimer.
- Redistributions in binary form must reproduce the above copyright notice, this list of conditions and the following disclaimer in the documentation and/or other materials provided with the distribution.
- Neither the name of the Komodo Does Inc nor the names of its contributors may be used to endorse or promote products derived from this software without specific prior written permission.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

#ifndef DOUBLE_LINKED_LIST_H
#define DOUBLE_LINKED_LIST_H

/** \file
 * Double Linked List defintion.
 */

#ifndef DOUBLE_LINKED_LIST_IMPL_H
#include "DoubleLinkedListImpl.h"
#endif // DOUBLE_LINKED_LIST_IMPL_H

#ifndef ITERATOR_H
#include "Iterator.h"
#endif // ITERATOR_H

namespace Experiment {
  
  /** DoubleLinkedList which can be iterated via DoubleLinkedList::iterator
   *
   * \tparam T the type of Data this DoubleLinkedList will hold
   */
  template<class T>
    class DoubleLinkedList {
  private:
    /** Convenience typedef of Nodes contained in this list */
    typedef DoubleLinkedListImpl::Node<T> Node;
    /** Convenience typedef of Nodes with valid data contained in this list */
    typedef DoubleLinkedListImpl::DataNode<T> DataNode;
    
  public:
    /** Convenience typedef of the type of values in this list */
    typedef T value_type;
    
    /** Convenience typedef of iterators of this list */
    typedef Experiment::Iterator<value_type, DoubleLinkedList<value_type>, Node> iterator;
    
  private: 
    /** Convenience typedef of Nodes for iterators for keeping this lists's iterators
     * at the correct position when Nodes are inserted, moved and removed.
     *
     * Yes, IterNodes could be single-linked, but that means writing the code for single
     * linked Nodes.  We are keeping the code simple.
     */
    typedef DoubleLinkedListImpl::Node<iterator*> IterNode;

    /** Convenience typedef of DataNodes containing iterators for keeping this lists's
     * iterators at the correct position when nodes are inserted, moved and removed.
     *
     * \see IterNode
     */
    typedef DoubleLinkedListImpl::DataNode<iterator*> IterDataNode;
    
  public:
    ~DoubleLinkedList();
    
    DoubleLinkedList();
    
    DoubleLinkedList(const DoubleLinkedList& rhs);
    
    void clear();
    
    bool isEmpty() const;
    
    iterator begin();
    
    iterator end();
    
    void push_front(const value_type& value);
    
    void push_back(const value_type& value);
    
    /// \todo add erase method

    /// \todo add insert method
    
  public:
    void addIterator(iterator* iter);
    
    void removeIterator(iterator* iter);
    
  public:
    // Note: This comes from iter rather than Node because Node doesn't know about list
    void notifyItersSwapOccurred(Node* a, Node* b) const;
    
    void notifyItersInsertedBefore(int count, Node* firstAfter) const;
    
    void notifyItersRemovedBefore(int count, Node* firstAfter) const;
    
  private:
    /** First element in the list, or NULL for none */
    Node head;
    
    /** Last element in the list, who's next is NULL, or NULL for none */
    Node tail;
    
    /** List of iterators */
    IterNode iterHead;
  };
  
} // namespace Experiment

#include "DoubleLinkedList.cpp"

#endif // DOUBLE_LINKED_LIST_H
