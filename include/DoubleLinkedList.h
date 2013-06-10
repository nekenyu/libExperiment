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
