/*
Copyright (c) 2013, Komodo Does Inc
All rights reserved.

Redistribution and use in source and binary forms, with or without modification, are permitted provided that the following conditions are met:

- Redistributions of source code must retain the above copyright notice, this list of conditions and the following disclaimer.
- Redistributions in binary form must reproduce the above copyright notice, this list of conditions and the following disclaimer in the documentation and/or other materials provided with the distribution.
- Neither the name of the Komodo Does Inc nor the names of its contributors may be used to endorse or promote products derived from this software without specific prior written permission.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

/** \file
 * Test Cases for DoubleLinkedList
 */

#include <stdexcept>
#include <cppunit/extensions/HelperMacros.h>

#include "DoubleLinkedList.h"

using Experiment::DoubleLinkedList;

/** Verify that the ordered data in data matches the data in list.
 *
 * Failures are noted by CPPUNIT_ASSERT macros
 *
 * \param data to compare items to list
 * \param list to compare to items in data
 *
 * \tparam length number of values in data
 * \tparam T type of Data in data and the List
 * \tparam List type of list to compare to
 */
template<size_t length, class T, class List>
void verify(T data[length], List& list) {
  typedef typename List::iterator Iterator;

  Iterator listIter = list.begin();
  const T* dataIter = data;
  size_t count = 0;
  
  if(0 == length) {
    CPPUNIT_ASSERT_MESSAGE("When empty, begin is end", list.end() == listIter);
    
    ++listIter;
    CPPUNIT_ASSERT_MESSAGE("After end is still end", list.end() == listIter);
    
    CPPUNIT_ASSERT(list.isEmpty());
    return;
  }
  
  // list is not empty
  CPPUNIT_ASSERT(!list.isEmpty());
  Iterator listPrev = listIter;
  --listPrev;
  
  for( ; count < length && (data + length) != dataIter && list.end() != listIter;
       ++dataIter, listPrev = listIter, ++listIter, ++count
       ) {
    CPPUNIT_ASSERT_EQUAL(*dataIter, *listIter);
    CPPUNIT_ASSERT(listPrev == listIter - 1);
    CPPUNIT_ASSERT(list.end() != listIter);
  }
  
  CPPUNIT_ASSERT(data + length == dataIter);
  CPPUNIT_ASSERT(list.end() == listIter);
  CPPUNIT_ASSERT_EQUAL(length, count);
  
  for(--listIter, --dataIter; list.begin() != listIter && dataIter != data; --listIter, --dataIter) {
    CPPUNIT_ASSERT(*listIter == *dataIter);
  } 
  CPPUNIT_ASSERT(list.begin() == listIter);
  CPPUNIT_ASSERT(data == dataIter);
  CPPUNIT_ASSERT(*listIter == *dataIter);
}

/** DoubleLinkedList test cases
 *
 * \tparam T the type of Data being tested
 */
template<class T>
class DoubleLinkedListTest : public CppUnit::TestFixture {
  CPPUNIT_TEST_SUITE(DoubleLinkedListTest);
  CPPUNIT_TEST(empty);
  CPPUNIT_TEST(one);
  CPPUNIT_TEST(two);
  CPPUNIT_TEST(many);

  CPPUNIT_TEST(swapSame);
  CPPUNIT_TEST(swapHead);
  CPPUNIT_TEST(swapTail);

  CPPUNIT_TEST(swapTwo);
  CPPUNIT_TEST(swapTwor);
 
  CPPUNIT_TEST(swapThreeAB);
  CPPUNIT_TEST(swapThreeABr);
  CPPUNIT_TEST(swapThreeAC);
  CPPUNIT_TEST(swapThreeACr);
  CPPUNIT_TEST(swapThreeBC);
  CPPUNIT_TEST(swapThreeBCr);

  CPPUNIT_TEST(swapFourAB);
  CPPUNIT_TEST(swapFourABr);
  CPPUNIT_TEST(swapFourAC);
  CPPUNIT_TEST(swapFourACr);
  CPPUNIT_TEST(swapFourAD);
  CPPUNIT_TEST(swapFourADr);
  CPPUNIT_TEST(swapFourBC);
  CPPUNIT_TEST(swapFourBCr);
  CPPUNIT_TEST(swapFourBD);
  CPPUNIT_TEST(swapFourBDr);
  CPPUNIT_TEST(swapFourCD);
  CPPUNIT_TEST(swapFourCDr);

  CPPUNIT_TEST(copyEmpty);
  CPPUNIT_TEST(copyOne);
  CPPUNIT_TEST(copyTwo);
  CPPUNIT_TEST(copyThree);
  CPPUNIT_TEST(clear);
  CPPUNIT_TEST(iterDeref);
  CPPUNIT_TEST(push_frontEmpty);
  CPPUNIT_TEST(push_frontOne);
  CPPUNIT_TEST(push_frontTwo);

  CPPUNIT_TEST(moveInList);
  CPPUNIT_TEST(moveOutOfList);

  CPPUNIT_TEST(nestedList);

  CPPUNIT_TEST_SUITE_END();

private:
  /** Convenience typedef of the type of the DoubleLinkedList */
  typedef DoubleLinkedList<T> List;

  /** Convenience typedef of iterator of List */
  typedef typename DoubleLinkedList<T>::iterator Iterator;

private:
  /** Setup list from the length values in data
   *
   * \param data to read values from to copy into list
   * \param length number of values in data to copy to list
   * \param list to copy length values from data into
   */
  void setup(const T* const data, const size_t length, List& list) {
    for(const T* iter = data; (data + length) != iter; ++iter) {
      list.push_back(*iter);
    }
  }

  /** Test loading N items of type T from data into a list
   *
   * \param data to copy N elements from into a list
   * \tparam N number of items to copy into the list and verify
   */
  template<int N>
  void testLoad(T data[N]) {
    List list;
    setup(data, N, list);
    verify<N>(data, list);
  }

  /** Create a list from the N items in data, swap firstSwapPosition with
   * secondSwapPosition and verify the list matches swapped.
   *
   * \param data to copy into the list
   * \param swapped expected data after swapping
   * \param firstSwapPosition position to swap values with secondSwapPosition
   * \param secondSwapPosition position to swap values with firstSwapPosition
   *
   * \tparam N number of items to examine
   */
  template<int N>
  void testSwap(T data[N], T swapped[N], size_t firstSwapPosition, size_t secondSwapPosition) {
    CPPUNIT_ASSERT(N > 1);

    List list;
    setup(data, N, list);

    Iterator first = list.begin() + firstSwapPosition;
    Iterator second = list.begin() + secondSwapPosition;

    Experiment::swap(first, second);
    verify<N>(swapped, list);
  }

public:
  /*
   *
   * Actual Test Cases
   *
   */

  /*
   * Trivial Cases
   */
  void empty() {
    T data[] = { };
    testLoad<0>(data);
  }

  void one() {
    T data[] = { 1 };
    testLoad<0>(data);
  }

  void two() {
    T data[] = { 1, 2 };
    testLoad<0>(data);
  }

  void many() {
    T data[] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10,
		 11, 12, 13, 14, 15, 16, 17, 18, 19,20,
		 21, 22, 23, 24, 25, 26, 27, 28, 29, 30,
		 31, 32, 33, 34, 35, 36, 37, 38, 39, 40 };
    testLoad<0>(data);
  }

  void swapSame() {
    T data[] = { 1, 2 };
    testSwap<2>(data, data, 0, 0);
  }

  void swapHead() {
    T data[] = { 1, 2 };
    // Note: -1 would move to rend()
    testSwap<2>(data, data, 0, -1);
  }

  void swapTail() {
    T data[] = { 1, 2 };
    // Note: 2 would move to end()
    testSwap<2>(data, data, 0, 2);
  }


  void swapTwo() {
    T data[] = { 1, 2 };
    T expected[] = { 2, 1 };
    testSwap<2>(data, expected, 0, 1);
  }

  void swapTwor() {
    T data[] = { 1, 2 };
    T expected[] = { 2, 1 };
    testSwap<2>(data, expected, 1, 0);
  }

  void swapThreeAB() {
    T data[] = { 1, 2, 3 };
    T expected[] = { 2, 1, 3 };
    testSwap<3>(data, expected, 0, 1);
  }

  void swapThreeABr() {
    T data[] = { 1, 2, 3 };
    T expected[] = { 2, 1, 3 };
    testSwap<3>(data, expected, 1, 0);
  }

  void swapThreeAC() {
    T data[] = { 1, 2, 3 };
    T expected[] = { 3, 2, 1 };

    testSwap<3>(data, expected, 0, 2);
  }

  void swapThreeACr() {
    T data[] = { 1, 2, 3 };
    T expected[] = { 3, 2, 1 };

    testSwap<3>(data, expected, 2, 0);
  }

  void swapThreeBC() {
    T data[] = { 1, 2, 3 };
    T expected[] = { 1, 3, 2 };

    testSwap<3>(data, expected, 1, 2);
  }

  void swapThreeBCr() {
    T data[] = { 1, 2, 3 };
    T expected[] = { 1, 3, 2 };

    testSwap<3>(data, expected, 2, 1);
  }

  void swapFourAB() {
    T data[] = { 1, 2, 3, 4 };
    T expected[] = { 2, 1, 3, 4 };

    testSwap<4>(data, expected, 0, 1);
  }

  void swapFourABr() {
    T data[] = { 1, 2, 3, 4 };
    T expected[] = { 2, 1, 3, 4 };

    testSwap<4>(data, expected, 1, 0);
  }

  void swapFourAC() {
    T data[] = { 1, 2, 3, 4 };
    T expected[] = { 3, 2, 1, 4 };

    testSwap<4>(data, expected, 0, 2);
  }

  void swapFourACr() {
    T data[] = { 1, 2, 3, 4 };
    T expected[] = { 3, 2, 1, 4 };

    testSwap<4>(data, expected, 2, 0);
  }

  void swapFourAD() {
    T data[] = { 1, 2, 3, 4 };
    T expected[] = { 4, 2, 3, 1 };

    testSwap<4>(data, expected, 0, 3);
  }

  void swapFourADr() {
    T data[] = { 1, 2, 3, 4 };
    T expected[] = { 4, 2, 3, 1 };

    testSwap<4>(data, expected, 3, 0);
  }

  void swapFourBC() {
    T data[] = { 1, 2, 3, 4 };
    T expected[] = { 1, 3, 2, 4 };

    testSwap<4>(data, expected, 1, 2);
  }

  void swapFourBCr() {
    T data[] = { 1, 2, 3, 4 };
    T expected[] = { 1, 3, 2, 4 };

    testSwap<4>(data, expected, 2, 1);
  }

  void swapFourBD() {
    T data[] = { 1, 2, 3, 4 };
    T expected[] = { 1, 4, 3, 2 };

    testSwap<4>(data, expected, 1, 3);
  }

  void swapFourBDr() {
    T data[] = { 1, 2, 3, 4 };
    T expected[] = { 1, 4, 3, 2 };

    testSwap<4>(data, expected, 3, 1);
  }

  void swapFourCD() {
    T data[] = { 1, 2, 3, 4 };
    T expected[] = { 1, 2, 4, 3 };

    testSwap<4>(data, expected, 2, 3);
  }

  void swapFourCDr() {
    T data[] = { 1, 2, 3, 4 };
    T expected[] = { 1, 2, 4, 3 };

    testSwap<4>(data, expected, 3, 2);
  }

  /*
   * Individual tests
   */

  void copyEmpty() {
    List list;

    List copy = list;

    T expected[] = { };
    verify<0>(expected, copy);
  }

  void copyOne() {
    List list;
    list.push_back(0);

    List copy = list;

    T expected[] = { 0 };
    verify<1>(expected, copy);
  }

  void copyTwo() {
    List list;
    list.push_back(0);
    list.push_back(1);

    List copy = list;

    T expected[] = { 0, 1 };
    verify<2>(expected, copy);
  }

  void copyThree() {
    List list;
    list.push_back(0);
    list.push_back(1);
    list.push_back(2);

    List copy = list;

    T expected[] = { 0, 1, 2 };
    verify<3>(expected, copy);
  }

  void clear() {
    List list;
    list.push_back(0);
    list.push_back(1);
    CPPUNIT_ASSERT(list.begin() != list.end());

    list.clear();
    CPPUNIT_ASSERT(list.isEmpty());
    CPPUNIT_ASSERT(list.begin() == list.end());
  }

  void iterDeref() {
    List list;
    list.push_back(0);

    Iterator first = list.begin();
    CPPUNIT_ASSERT(first.operator->() == &first.operator*());
  }

  void push_frontEmpty() {
    List list;

    Iterator first = list.begin();
    CPPUNIT_ASSERT(list.end() == first);
    
    list.push_front(-1);

    CPPUNIT_ASSERT(list.end() == first);

    CPPUNIT_ASSERT(-1 == *list.begin());
  }

  void push_frontOne() {
    List list;
    list.push_back(0);

    Iterator first = list.begin();
    Iterator second = first + 1;
    
    CPPUNIT_ASSERT(0 == *first);
    CPPUNIT_ASSERT(list.end() == second);
    
    list.push_front(-1);

    CPPUNIT_ASSERT(-1 == *first);
    CPPUNIT_ASSERT(list.end() == second);

    CPPUNIT_ASSERT(0 == *(first + 1));
  }

  void push_frontTwo() {
    List list;
    list.push_back(0);
    list.push_back(1);

    Iterator first = list.begin();
    Iterator second = first + 1;
    Iterator third = second + 1;
    
    CPPUNIT_ASSERT(0 == *first);
    CPPUNIT_ASSERT(1 == *second);
    CPPUNIT_ASSERT(list.end() == third);
    
    list.push_front(-1);

    CPPUNIT_ASSERT(-1 == *first);
    CPPUNIT_ASSERT(0 == *second);
    CPPUNIT_ASSERT(list.end() == third);

    CPPUNIT_ASSERT(1 == *(second + 1));
  }

  void moveInList() {
    List list;
    list.push_back(2);
    list.push_back(1);
    list.push_back(0);

    {
      Iterator move = list.begin() + 2;
      Iterator moveBefore = list.begin();
      Experiment::moveBefore(move, moveBefore);
      CPPUNIT_ASSERT(list.end() == move);
      CPPUNIT_ASSERT(*moveBefore == 0);
      
      T expected[] = { 0, 2, 1 };
      verify<3>(expected, list);
    }

    {
      Iterator move = list.begin() + 1;
      Iterator moveBefore = list.end();
      Experiment::moveBefore(move, moveBefore);
      CPPUNIT_ASSERT(list.end() == move);
      CPPUNIT_ASSERT(moveBefore == list.end());
      
      T expected[] = { 0, 1, 2 };
      verify<3>(expected, list);
    }
  }

  void moveOutOfList() {
    List from;
    from.push_back(0);
    from.push_back(3);
    from.push_back(1);
    from.push_back(2);

    List to;
    Iterator toDest = to.end();
   
    // First
    {
      Iterator fromMove = from.begin();
      Experiment::moveBefore(fromMove, toDest);
      CPPUNIT_ASSERT(from.end() == fromMove);

      Iterator fromIter = from.begin();
      CPPUNIT_ASSERT(3 == *fromIter);
      
      T fromExpected[] = { 3, 1, 2 };
      verify<3>(fromExpected, from);

      T toExpected[] = { 0 };
      verify<1>(toExpected, to);
    }

    // Middle
    {
      Iterator fromMove = from.begin() + 1;
      Experiment::moveBefore(fromMove, toDest);
      CPPUNIT_ASSERT(from.end() == fromMove);

      Iterator fromIter = from.begin() + 1;
      CPPUNIT_ASSERT(2 == *fromIter);
      
      T fromExpected[] = { 3, 2 };
      verify<2>(fromExpected, from);

      T toExpected[] = { 0, 1 };
      verify<2>(toExpected, to);
    }

    // Last
    {
      Iterator fromMove = from.begin() + 1;
      Experiment::moveBefore(fromMove, toDest);
      CPPUNIT_ASSERT(from.end() == fromMove);

      Iterator fromIter = from.begin() + 1;
      CPPUNIT_ASSERT(from.end() == fromIter);
      
      T fromExpected[] = { 3 };
      verify<1>(fromExpected, from);

      T toExpected[] = { 0, 1, 2 };
      verify<3>(toExpected, to);
    }

    // Only
    {
      Iterator fromMove = from.begin();
      Experiment::moveBefore(fromMove, toDest);
      CPPUNIT_ASSERT(from.end() == fromMove);

      CPPUNIT_ASSERT(from.isEmpty());

      T toExpected[] = { 0, 1, 2, 3 };
      verify<4>(toExpected, to);
    }
  }

  void nestedList() {
    typedef DoubleLinkedList<List> NestedList;
    typedef typename NestedList::iterator NestedIter;

    NestedList nested;
    CPPUNIT_ASSERT(nested.isEmpty());

    nested.push_back(List());
    CPPUNIT_ASSERT(!nested.isEmpty());
    NestedIter nestedIter = nested.begin();
    CPPUNIT_ASSERT(nestedIter->isEmpty());

    nestedIter->push_back(0);
    CPPUNIT_ASSERT(0 == *nestedIter->begin());
  }
};

/*
 * Templated test cases
 */

typedef DoubleLinkedListTest<int> DoubleLinkedListIntTest;
CPPUNIT_TEST_SUITE_REGISTRATION(DoubleLinkedListIntTest);

typedef DoubleLinkedListTest<float> DoubleLinkedListFloatTest;
CPPUNIT_TEST_SUITE_REGISTRATION(DoubleLinkedListFloatTest);
