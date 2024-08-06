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

#include "DoubleLinkedList.h"

#include "SortHelp.h"

#include "gtest/gtest.h"

using Experiment::DoubleLinkedList;

/** Verify that the ordered data in data matches the data in list.
 *
 * Failures are noted by EXPECT_* macros
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
    EXPECT_EQ(list.end(), listIter) << "When empty, begin is end";
    
    ++listIter;
    EXPECT_EQ(list.end(), listIter) << "After end is still end";
    
    EXPECT_TRUE(list.isEmpty());
    return;
  }
  
  // list is not empty
  EXPECT_FALSE(list.isEmpty());
  Iterator listPrev = listIter;
  --listPrev;
  
  for( ; count < length && (data + length) != dataIter && list.end() != listIter;
       ++dataIter, listPrev = listIter, ++listIter, ++count
       ) {
    EXPECT_EQ(*dataIter, *listIter);
    EXPECT_EQ(listPrev, listIter - 1);
    EXPECT_NE(list.end(), listIter);
  }
  
  EXPECT_EQ(data + length, dataIter);
  EXPECT_EQ(list.end(), listIter);
  EXPECT_EQ(length, count);
  
  for(--listIter, --dataIter; list.begin() != listIter && dataIter != data; --listIter, --dataIter) {
    EXPECT_EQ(*listIter, *dataIter);
  } 
  EXPECT_EQ(list.begin(), listIter);
  EXPECT_EQ(data, dataIter);
  EXPECT_EQ(*listIter, *dataIter);
}

/** Setup list from the length values in data
 *
 * \param data to read values from to copy into list
 * \param length number of values in data to copy to list
 * \param list to copy length values from data into
 */
template<typename T, typename List>
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
template<int N, typename T>
void testLoad(T data[N]) {
  DoubleLinkedList<T> list;
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
template<int N, typename T>
void testSwap(T data[N], T swapped[N], size_t firstSwapPosition, size_t secondSwapPosition) {
  ASSERT_GT(N, 1);

  DoubleLinkedList<T> list;
  setup(data, N, list);

  typedef typename DoubleLinkedList<T>::iterator Iterator;
  Iterator first = list.begin() + firstSwapPosition;
  Iterator second = list.begin() + secondSwapPosition;

  Experiment::swap(first, second);
  verify<N>(swapped, list);
}

/** DoubleLinkedList test fixture.
 *
 * \note This class is superfluous. It uses the same googletest
 * strategy as the other tests for consistency only.
 * 
 * \tparam T the type of Data being tested
 */
template<class T>
class DoubleLinkedListTest : public testing::Test {
protected:
  typedef T value_type;

  /** Convenience typedef of the type of the DoubleLinkedList */
  typedef DoubleLinkedList<value_type> List;

  /** Convenience typedef of iterator of List */
  typedef typename DoubleLinkedList<value_type>::iterator Iterator;
};
TYPED_TEST_SUITE_P(DoubleLinkedListTest);

/*
  * Trivial Cases
  */
TYPED_TEST_P(DoubleLinkedListTest, empty) {
  typename TestFixture::value_type data[] = { };
  testLoad<0>(data);
}
TYPED_TEST_P(DoubleLinkedListTest, one) {
  typename TestFixture::value_type data[] = { 1 };
  testLoad<0>(data);
}

TYPED_TEST_P(DoubleLinkedListTest, two) {
  typename TestFixture::value_type data[] = { 1, 2 };
  testLoad<0>(data);
}

TYPED_TEST_P(DoubleLinkedListTest, many) {
  typename TestFixture::value_type data[] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10,
    11, 12, 13, 14, 15, 16, 17, 18, 19,20,
    21, 22, 23, 24, 25, 26, 27, 28, 29, 30,
    31, 32, 33, 34, 35, 36, 37, 38, 39, 40 };
  testLoad<0>(data);
}

TYPED_TEST_P(DoubleLinkedListTest, swapSame) {
  typename TestFixture::value_type data[] = { 1, 2 };
  testSwap<2>(data, data, 0, 0);
}

TYPED_TEST_P(DoubleLinkedListTest, swapHead) {
  typename TestFixture::value_type data[] = { 1, 2 };
  // Note: -1 would move to rend()
  testSwap<2>(data, data, 0, -1);
}

TYPED_TEST_P(DoubleLinkedListTest, swapTail) {
  typename TestFixture::value_type data[] = { 1, 2 };
  // Note: 2 would move to end()
  testSwap<2>(data, data, 0, 2);
}

TYPED_TEST_P(DoubleLinkedListTest, swapTwo) {
  typename TestFixture::value_type data[] = { 1, 2 };
  typename TestFixture::value_type expected[] = { 2, 1 };
  testSwap<2>(data, expected, 0, 1);
}

TYPED_TEST_P(DoubleLinkedListTest, swapTwor) {
  typename TestFixture::value_type data[] = { 1, 2 };
  typename TestFixture::value_type expected[] = { 2, 1 };
  testSwap<2>(data, expected, 1, 0);
}

TYPED_TEST_P(DoubleLinkedListTest, swapThreeAB) {
  typename TestFixture::value_type data[] = { 1, 2, 3 };
  typename TestFixture::value_type expected[] = { 2, 1, 3 };
  testSwap<3>(data, expected, 0, 1);
}

TYPED_TEST_P(DoubleLinkedListTest, swapThreeABr) {
  typename TestFixture::value_type data[] = { 1, 2, 3 };
  typename TestFixture::value_type expected[] = { 2, 1, 3 };
  testSwap<3>(data, expected, 1, 0);
}

TYPED_TEST_P(DoubleLinkedListTest, swapThreeAC) {
  typename TestFixture::value_type data[] = { 1, 2, 3 };
  typename TestFixture::value_type expected[] = { 3, 2, 1 };

  testSwap<3>(data, expected, 0, 2);
}

TYPED_TEST_P(DoubleLinkedListTest, swapThreeACr) {
  typename TestFixture::value_type data[] = { 1, 2, 3 };
  typename TestFixture::value_type expected[] = { 3, 2, 1 };

  testSwap<3>(data, expected, 2, 0);
}

TYPED_TEST_P(DoubleLinkedListTest, swapThreeBC) {
  typename TestFixture::value_type data[] = { 1, 2, 3 };
  typename TestFixture::value_type expected[] = { 1, 3, 2 };

  testSwap<3>(data, expected, 1, 2);
}

TYPED_TEST_P(DoubleLinkedListTest, swapThreeBCr) {
  typename TestFixture::value_type data[] = { 1, 2, 3 };
  typename TestFixture::value_type expected[] = { 1, 3, 2 };

  testSwap<3>(data, expected, 2, 1);
}

TYPED_TEST_P(DoubleLinkedListTest, swapFourAB) {
  typename TestFixture::value_type data[] = { 1, 2, 3, 4 };
  typename TestFixture::value_type expected[] = { 2, 1, 3, 4 };

  testSwap<4>(data, expected, 0, 1);
}

TYPED_TEST_P(DoubleLinkedListTest, swapFourABr) {
  typename TestFixture::value_type data[] = { 1, 2, 3, 4 };
  typename TestFixture::value_type expected[] = { 2, 1, 3, 4 };

  testSwap<4>(data, expected, 1, 0);
}

TYPED_TEST_P(DoubleLinkedListTest, swapFourAC) {
  typename TestFixture::value_type data[] = { 1, 2, 3, 4 };
  typename TestFixture::value_type expected[] = { 3, 2, 1, 4 };

  testSwap<4>(data, expected, 0, 2);
}

TYPED_TEST_P(DoubleLinkedListTest, swapFourACr) {
  typename TestFixture::value_type data[] = { 1, 2, 3, 4 };
  typename TestFixture::value_type expected[] = { 3, 2, 1, 4 };

  testSwap<4>(data, expected, 2, 0);
}

TYPED_TEST_P(DoubleLinkedListTest, swapFourAD) {
  typename TestFixture::value_type data[] = { 1, 2, 3, 4 };
  typename TestFixture::value_type expected[] = { 4, 2, 3, 1 };

  testSwap<4>(data, expected, 0, 3);
}

TYPED_TEST_P(DoubleLinkedListTest, swapFourADr) {
  typename TestFixture::value_type data[] = { 1, 2, 3, 4 };
  typename TestFixture::value_type expected[] = { 4, 2, 3, 1 };

  testSwap<4>(data, expected, 3, 0);
}

TYPED_TEST_P(DoubleLinkedListTest, swapFourBC) {
  typename TestFixture::value_type data[] = { 1, 2, 3, 4 };
  typename TestFixture::value_type expected[] = { 1, 3, 2, 4 };

  testSwap<4>(data, expected, 1, 2);
}

TYPED_TEST_P(DoubleLinkedListTest, swapFourBCr) {
  typename TestFixture::value_type data[] = { 1, 2, 3, 4 };
  typename TestFixture::value_type expected[] = { 1, 3, 2, 4 };

  testSwap<4>(data, expected, 2, 1);
}

TYPED_TEST_P(DoubleLinkedListTest, swapFourBD) {
  typename TestFixture::value_type data[] = { 1, 2, 3, 4 };
  typename TestFixture::value_type expected[] = { 1, 4, 3, 2 };

  testSwap<4>(data, expected, 1, 3);
}

TYPED_TEST_P(DoubleLinkedListTest, swapFourBDr) {
  typename TestFixture::value_type data[] = { 1, 2, 3, 4 };
  typename TestFixture::value_type expected[] = { 1, 4, 3, 2 };

  testSwap<4>(data, expected, 3, 1);
}

TYPED_TEST_P(DoubleLinkedListTest, swapFourCD) {
  typename TestFixture::value_type data[] = { 1, 2, 3, 4 };
  typename TestFixture::value_type expected[] = { 1, 2, 4, 3 };

  testSwap<4>(data, expected, 2, 3);
}

TYPED_TEST_P(DoubleLinkedListTest, swapFourCDr) {
  typename TestFixture::value_type data[] = { 1, 2, 3, 4 };
  typename TestFixture::value_type expected[] = { 1, 2, 4, 3 };

  testSwap<4>(data, expected, 3, 2);
}

/*
  * Individual tests
  */

TYPED_TEST_P(DoubleLinkedListTest, copyEmpty) {
  typename TestFixture::List list;

  typename TestFixture::List copy = list;

  typename TestFixture::value_type expected[] = { };
  verify<0>(expected, copy);
}

TYPED_TEST_P(DoubleLinkedListTest, copyOne) {
  typename TestFixture::List list;
  list.push_back(0);

  typename TestFixture::List copy = list;

  typename TestFixture::value_type expected[] = { 0 };
  verify<1>(expected, copy);
}

TYPED_TEST_P(DoubleLinkedListTest, copyTwo) {
  typename TestFixture::List list;
  list.push_back(0);
  list.push_back(1);

  typename TestFixture::List copy = list;

  typename TestFixture::value_type expected[] = { 0, 1 };
  verify<2>(expected, copy);
}

TYPED_TEST_P(DoubleLinkedListTest, copyThree) {
  typename TestFixture::List list;
  list.push_back(0);
  list.push_back(1);
  list.push_back(2);

  typename TestFixture::List copy = list;

  typename TestFixture::value_type expected[] = { 0, 1, 2 };
  verify<3>(expected, copy);
}

TYPED_TEST_P(DoubleLinkedListTest, clear) {
  typename TestFixture::List list;
  list.push_back(0);
  list.push_back(1);
  EXPECT_NE(list.begin(), list.end());

  list.clear();
  EXPECT_TRUE(list.isEmpty());
  EXPECT_EQ(list.begin(), list.end());
}

TYPED_TEST_P(DoubleLinkedListTest, iterDeref) {
  typename TestFixture::List list;
  list.push_back(0);

  typename TestFixture::Iterator first = list.begin();
  EXPECT_EQ(first.operator->(), &first.operator*());
}

TYPED_TEST_P(DoubleLinkedListTest, push_frontEmpty) {
  typename TestFixture::List list;

  typename TestFixture::Iterator first = list.begin();
  EXPECT_EQ(list.end(), first);
  
  list.push_front(-1);

  EXPECT_EQ(list.end(), first);

  EXPECT_EQ(-1, *list.begin());
}

TYPED_TEST_P(DoubleLinkedListTest, push_frontOne) {
  typename TestFixture::List list;
  list.push_back(0);

  typename TestFixture::Iterator first = list.begin();
  typename TestFixture::Iterator second = first + 1;
  
  EXPECT_EQ(*list.begin(), *first);
  EXPECT_EQ(list.end(), second);
  
  list.push_front(-1);

  EXPECT_EQ(-1, *first);
  EXPECT_EQ(list.end(), second);

  EXPECT_EQ(0, *(first + 1));
}

TYPED_TEST_P(DoubleLinkedListTest, push_frontTwo) {
  typename TestFixture::List list;
  list.push_back(0);
  list.push_back(1);

  typename TestFixture::Iterator first = list.begin();
  typename TestFixture::Iterator second = first + 1;
  typename TestFixture::Iterator third = second + 1;
  
  EXPECT_EQ(0, *first);
  EXPECT_EQ(1, *second);
  EXPECT_EQ(list.end(), third);
  
  list.push_front(-1);

  EXPECT_EQ(-1, *first);
  EXPECT_EQ(0, *second);
  EXPECT_EQ(list.end(), third);

  EXPECT_EQ(1, *(second + 1));
}

TYPED_TEST_P(DoubleLinkedListTest, moveInList) {
  typename TestFixture::List list;
  list.push_back(2);
  list.push_back(1);
  list.push_back(0);

  {
    typename TestFixture::Iterator move = list.begin() + 2;
    typename TestFixture::Iterator moveBefore = list.begin();
    Experiment::moveBefore(move, moveBefore);
    EXPECT_EQ(list.end(), move);
    EXPECT_EQ(*moveBefore, 0);
    
    typename TestFixture::value_type expected[] = { 0, 2, 1 };
    verify<3>(expected, list);
  }

  {
    typename TestFixture::Iterator move = list.begin() + 1;
    typename TestFixture::Iterator moveBefore = list.end();
    Experiment::moveBefore(move, moveBefore);
    EXPECT_EQ(list.end(), move);
    EXPECT_EQ(moveBefore, list.end());
    
    typename TestFixture::value_type expected[] = { 0, 1, 2 };
    verify<3>(expected, list);
  }
}

TYPED_TEST_P(DoubleLinkedListTest, moveOutOfList) {
  typename TestFixture::List from;
  from.push_back(0);
  from.push_back(3);
  from.push_back(1);
  from.push_back(2);

  typename TestFixture::List to;
  typename TestFixture::Iterator toDest = to.end();
  
  // First
  {
    typename TestFixture::Iterator fromMove = from.begin();
    Experiment::moveBefore(fromMove, toDest);
    EXPECT_EQ(from.end(), fromMove);

    typename TestFixture::Iterator fromIter = from.begin();
    EXPECT_EQ(3, *fromIter);
    
    typename TestFixture::value_type fromExpected[] = { 3, 1, 2 };
    verify<3>(fromExpected, from);

    typename TestFixture::value_type toExpected[] = { 0 };
    verify<1>(toExpected, to);
  }

  // Middle
  {
    typename TestFixture::Iterator fromMove = from.begin() + 1;
    Experiment::moveBefore(fromMove, toDest);
    EXPECT_EQ(from.end(), fromMove);

    typename TestFixture::Iterator fromIter = from.begin() + 1;
    EXPECT_EQ(2, *fromIter);
    
    typename TestFixture::value_type fromExpected[] = { 3, 2 };
    verify<2>(fromExpected, from);

    typename TestFixture::value_type toExpected[] = { 0, 1 };
    verify<2>(toExpected, to);
  }

  // Last
  {
    typename TestFixture::Iterator fromMove = from.begin() + 1;
    Experiment::moveBefore(fromMove, toDest);
    EXPECT_EQ(from.end(), fromMove);

    typename TestFixture::Iterator fromIter = from.begin() + 1;
    EXPECT_EQ(from.end(), fromIter);
    
    typename TestFixture::value_type fromExpected[] = { 3 };
    verify<1>(fromExpected, from);

    typename TestFixture::value_type toExpected[] = { 0, 1, 2 };
    verify<3>(toExpected, to);
  }

  // Only
  {
    typename TestFixture::Iterator fromMove = from.begin();
    Experiment::moveBefore(fromMove, toDest);
    EXPECT_EQ(from.end(), fromMove);

    EXPECT_TRUE(from.isEmpty());

    typename TestFixture::value_type toExpected[] = { 0, 1, 2, 3 };
    verify<4>(toExpected, to);
  }
}

TYPED_TEST_P(DoubleLinkedListTest, nestedList) {
  typedef DoubleLinkedList<DoubleLinkedList<typename TestFixture::value_type>> NestedList;
  typedef typename NestedList::iterator NestedIter;

  NestedList nested;
  EXPECT_TRUE(nested.isEmpty());

  nested.push_back(typename TestFixture::List());
  EXPECT_FALSE(nested.isEmpty());
  NestedIter nestedIter = nested.begin();
  EXPECT_TRUE(nestedIter->isEmpty());

  nestedIter->push_back(0);
  EXPECT_EQ(0, *nestedIter->begin());
}

REGISTER_TYPED_TEST_SUITE_P(DoubleLinkedListTest,
  empty,
  one,
  two,
  many,

  swapSame,
  swapHead,
  swapTail,

  swapTwo,
  swapTwor,

  swapThreeAB,
  swapThreeABr,
  swapThreeAC,
  swapThreeACr,
  swapThreeBC,
  swapThreeBCr,

  swapFourAB,
  swapFourABr,
  swapFourAC,
  swapFourACr,
  swapFourAD,
  swapFourADr,
  swapFourBC,
  swapFourBCr,
  swapFourBD,
  swapFourBDr,
  swapFourCD,
  swapFourCDr,

  copyEmpty,
  copyOne,
  copyTwo,
  copyThree,
  clear,
  iterDeref,

  push_frontEmpty,
  push_frontOne,
  push_frontTwo,

  moveInList,
  moveOutOfList,

  nestedList
);

typedef testing::Types<
  int,
  float
> DoubleLinkedListTestTypes;

INSTANTIATE_TYPED_TEST_SUITE_P(
  MainDoubleLinkedListTest,
  DoubleLinkedListTest,
  DoubleLinkedListTestTypes);
