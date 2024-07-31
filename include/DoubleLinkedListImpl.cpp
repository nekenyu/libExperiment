/*
Copyright (c) 2013, Komodo Does Inc
All rights reserved.

Redistribution and use in source and binary forms, with or without modification, are permitted provided that the following conditions are met:

- Redistributions of source code must retain the above copyright notice, this list of conditions and the following disclaimer.
- Redistributions in binary form must reproduce the above copyright notice, this list of conditions and the following disclaimer in the documentation and/or other materials provided with the distribution.
- Neither the name of the Komodo Does Inc nor the names of its contributors may be used to endorse or promote products derived from this software without specific prior written permission.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

#ifndef DOUBLE_LINKED_LIST_IMPL_CPP
#define DOUBLE_LINKED_LIST_IMPL_CPP

/** \file
 *
 * Implementations of longer template methods of the DoubleLinkedListImpl.h file.
 *
 * \note This file is to be included at the end of DoubleLinkedListImpl.h
 */

namespace Experiment {

  namespace DoubleLinkedListImpl {

    /** Virtual destructor that does not delete its pointers */
    template<typename T>
    Node<T>::~Node<T>() {
      // Not my responsibility to delete the pointers...
      thePrevious = NULL;
      theNext = NULL;
    }
    
    /** Create a Node with the given previous and next pointers.
     *
     * \param previous the Node sequentially before this Node, or NULL for none
     * \param next the Node sequentially after this Node, or NULL for none
     */
    template<typename T>
    Node<T>::Node(Node<T>* previous, Node<T>* next)
      : thePrevious(previous), theNext(next)
    {
    }
    
    /** @return the Node sequentially before this Node, or NULL for none */
    template<typename T>
    Node<T>* Node<T>::getPrevious() const {
      return thePrevious;
    }
    
    /** Set the Node sequentially before this Node, or NULL for none.
     *
     * \param previous the Node to set as the previous node
     */
    template<typename T>
    void Node<T>::setPrevious(Node<T>* previous) {
      thePrevious = previous;
    }
    
    /** @return the Node sequentially after this Node, or NULL for none */
    template<typename T>
    Node<T>* Node<T>::getNext() const {
      return theNext;
    }
    
    /** Set the Node sequentially after this Node, or NULL for none.
     *
     * \param next the Node to set as the next node
     */
    template<typename T>
    void Node<T>::setNext(Node<T>* next) {
      theNext = next;
    }
    
    /** Swap this node with other by appropriately updating previous and next pointers
     *
     * \param other the Node to swap with this node
     *
     * \note The caller of this method is responsible for updating iterators to remain
     * in the correct containers and at the correct positions.
     */
    template<typename T>
    void Node<T>::swapWith(Node<T>* other) {
      // Don't do anything if swapping the same Nodes
      if(this == other) {
	return;
      }
      
      if(other == theNext) {
	// If swapping with next...
	swapWithNext();
      } else if(other == thePrevious) {
	// If swapping with previous
	other->swapWithNext();
      } else {
	// Otherwise, disjoint
	swapWithDisjoint(other);
      }
    }
    
    /** Move this node before other by appropriately updating previous and next pointers.
     *
     * \param other the Node to move before this node
     *
     * \note The caller of this method is responsible for updating iterators to remain
     * in the correct containers and at the correct positions.
     */
    template<typename T>
    void Node<T>::moveBefore(Node<T>* other) {
      if(this == other || theNext == other) {
	return;
      }
      
      this->getPrevious()->setNext(this->getNext());
      this->getNext()->setPrevious(this->getPrevious());
      
      this->setPrevious(other->getPrevious());
      other->getPrevious()->setNext(this);
      this->setNext(other);
      other->setPrevious(this);
    }
    
    /** Swap this node with the one immediately after it */
    template<typename T>
    void Node<T>::swapWithNext() {
      // Special Case: ... -> this -> other -> ...
      //  ... [ preThis  A ] <=> [ B this  C ] <=>  [ F other    G ] <=> [ H postOther ] ...
      
      Node<T>* other = theNext;
      
      // A
      this->thePrevious->theNext = other;
      
      // H
      other->theNext->thePrevious = this;
      
      // F
      other->thePrevious = this->thePrevious;
      
      // B
      this->thePrevious = other;
      
      // C
      this->theNext = other->theNext;
      
      // G
      other->theNext = this;
    }
    
    /** Swap this node with other by appropriately updating previous and next pointers
     * such that this and other are not already next to each other
     *
     * \param other the Node to swap with this node
     */
    template<typename T>
    void Node<T>::swapWithDisjoint(Node<T>* other) {
      // General Case
      //  ... [ preThis  A ] <=> [ B this  C ] <=> [ D postThis    ] ...
      //  ... [ preOther E ] <=> [ F other G ] <=> [ H postOther   ] ...
      // Where postThis is not other, and this is not PreOther
      
      // A
      this->thePrevious->theNext = other;
      
      // D
      this->theNext->thePrevious = other;
      
      // E
      other->thePrevious->theNext = this;
      
      // H
      other->theNext->thePrevious = this;
      
      // B, F
      std::swap(this->thePrevious, other->thePrevious);
      
      // C, G
      std::swap(this->theNext, other->theNext);
    }

    /** Destructor for DataNode.  Does nothing, even if the datatype is a pointer. */
    template<typename T>
    DataNode<T>::~DataNode() {
      // Do nothing
    }


    /** Create a DataNode with the given value t, previous and next pointers.
     *
     * \param t the value to copy into this DataNode
     * \param previous the Node sequentially before this Node, or NULL for none
     * \param next the Node sequentially after this Node, or NULL for none
     */
    template<typename T>
    DataNode<T>::DataNode(const T& t, Node<T>* previous, Node<T>* next)
      : Node<T>(previous, next), theT(t)
    {
    }
    
  } // namespace DoubleLinkedListImpl

} // namespace Experiment

#endif // DOUBLE_LINKED_LIST_IMPL_CPP
