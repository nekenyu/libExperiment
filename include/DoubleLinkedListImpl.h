/*
Copyright (c) 2013, Komodo Does Inc
All rights reserved.

Redistribution and use in source and binary forms, with or without modification, are permitted provided that the following conditions are met:

- Redistributions of source code must retain the above copyright notice, this list of conditions and the following disclaimer.
- Redistributions in binary form must reproduce the above copyright notice, this list of conditions and the following disclaimer in the documentation and/or other materials provided with the distribution.
- Neither the name of the Komodo Does Inc nor the names of its contributors may be used to endorse or promote products derived from this software without specific prior written permission.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

#ifndef DOUBLE_LINKED_LIST_IMPL_H
#define DOUBLE_LINKED_LIST_IMPL_H

/** \file
 * Implementation details of a DoubleLinkedList
 */

namespace Experiment {

  namespace DoubleLinkedListImpl {

    /** DoubleLinkedList internal Node base class.
     *
     * This is a common implementation with DataNode which adds the data value.
     *
     * DoubleLinkedList and/or Iterator is responsible for allocation, deallocation
     * and management of a Node's next and previous nodes.  Node simply provides the
     * ability to set these pointers.
     *
     * \tparam T the type of the value this Node works on
     *
     * \note This class is not accessible to the users of DoubleLinkedList.
     */
    template<typename T>
      class Node {
    public:
      /** The type of value this Node works on */
      typedef T value_type;
      
      virtual ~Node();
      Node(Node* previous = NULL, Node* next = NULL);
      
    private:
      Node(const Node& rhs);
      Node& operator=(const Node& rhs);
      
    public:
      Node* getPrevious() const;
      void setPrevious(Node* previous);
      
      Node* getNext() const;
      void setNext(Node* next);
      
      void swapWith(Node* other);
      
      void moveBefore(Node* other);
      
      /** \return a reference to the value of this node
       *
       * \throw invalid_argument if data is not available such as marker nodes
       */
      virtual value_type& operator*() {
	throw std::invalid_argument("Dereferencing at invalid position");
      }
      
      /** \return a const reference to the value of this node
       *
       * \throw invalid_argument if data is not available such as marker nodes
       */
      virtual const value_type& operator*() const {
	throw std::invalid_argument("Dereferencing at invalid position");
      }
      
      /** @return true if this is a valid note for which operator*() may be called,
       * otherwise false such as marker nodes.
       */
      virtual bool valid() const {
	return false;
      }
      
    private:
      void swapWithNext();
      void swapWithDisjoint(Node* other);
      
    private:
      /** The Node before this such that this == thePrevious->theNext or NULL for none. */
      Node* thePrevious;

      /** The Node after this such that this == theNext->thePrevious or NULL for none. */
      Node* theNext;
    };

    /** DoubleLinkedList internal Node holding Data.
     *
     * This provides a Node with a valid data type.
     *
     * This class will hold a copy of the value given to it.  That value will be
     * destructed, of course; however, DataNode is not responsible for deleting
     * the values of pointers.
     * 
     * \tparam T the type of the value this Node works on
     *
     * \note This class is not accessible to the users of DoubleLinkedList.
     */
    template<typename T>
      class DataNode : public Node<T> {
    public:
      /** The type of value this Node works on */
      typedef T value_type;

      virtual ~DataNode();
      
      DataNode(const value_type& t, Node<T>* previous = NULL, Node<T>* next = NULL);

    private:
      DataNode(const DataNode& rhs);
      DataNode& operator=(const DataNode& rhs);

    public:
      /** \return a reference to the value of this none */
      virtual value_type& operator*() {
	return theT;
      }
      
      /** \return a const reference to the value of this none */
      virtual const value_type& operator*() const {
	return theT;
      }
      
      /** @return true as this is a valid data node */
      virtual bool valid() const {
	return true;
      }
      
    private:
      /** The value in this node */
      value_type theT;
    };
    
  } // namespace DoubleLinkedListImpl

} // namespace Experiment

#include "DoubleLinkedListImpl.cpp"

#endif // DOUBLE_LINKED_LIST_IMPL_H
