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
 * Test Cases with int and float data for Sort algorithms.  Currently: ListMergeSort.
 */

#include <limits>
#include <stdexcept>

#include "DoubleLinkedList.h"
#include "ListMergeSort.h"
#include "Predicates.h"

#include "SortHelp.h"

#include "gtest/gtest.h"

using Experiment::DoubleLinkedList;
using Experiment::ListMergeSort;
using Experiment::PointerLess;

/** Template test::Test providing the test data numeric Sort
 * algorithms.
 *
 * This class is applied to a Tester type, which must have a
 * type Tester::value_type.
 * 
 * \tparam Tester the container-specific test code
 */
template<class Tester>
class SortNumericTest : public testing::Test {
protected:
  typedef Tester tester_type;
  typedef typename Tester::value_type value_type;

  tester_type tester;

  /** Known maximum value for our data type */
  const value_type max;

  /** Known minimum value for our data type */
  const value_type min;

  /** Known big value for our data type such that 0 < big < max */
  const value_type big;

  /** Known small value for our data type such that min < small < 0 */
  const value_type small;

  /** Construct test with some constants that might be helpful */
  SortNumericTest()
    : max(std::numeric_limits<value_type>::max()),
      min(std::numeric_limits<value_type>::is_integer ? std::numeric_limits<value_type>::min() : - max), 
      big(max / 2),
      small(min / 4)
  {
  }

  // All other constructors, destructors, and assignment operators = default
};
TYPED_TEST_SUITE_P(SortNumericTest);

/*
  * Trivial Cases
  */
TYPED_TEST_P(SortNumericTest, sortNone) {
  this->tester.testEmpty();
}

TYPED_TEST_P(SortNumericTest, sortOne) {
  typename TestFixture::value_type data[] = { 1 };
  typename TestFixture::value_type expected[] = { 1 };

  this->tester.test(data, expected);
}

/*
  * Two elements
  */

TYPED_TEST_P(SortNumericTest, sortTwoIn) {
  typename TestFixture::value_type data[] = { 0, 1 };
  typename TestFixture::value_type expected[] = { 0, 1 };

  this->tester.test(data, expected);
}

TYPED_TEST_P(SortNumericTest, sortTwoRev) {
  typename TestFixture::value_type data[] = { 1, 0 };
  typename TestFixture::value_type expected[] = { 0, 1 };

  this->tester.test(data, expected);
}

/*
  * Three unique element permutations
  */
TYPED_TEST_P(SortNumericTest, sortThreeABC) {
  typename TestFixture::value_type data[] = { 0, 1, 2 };
  typename TestFixture::value_type expected[] = { 0, 1, 2 };

  this->tester.test(data, expected);
}

TYPED_TEST_P(SortNumericTest, sortThreeACB) {
  typename TestFixture::value_type data[] = { 0, 2, 1 };
  typename TestFixture::value_type expected[] = { 0, 1, 2 };

  this->tester.test(data, expected);
}

TYPED_TEST_P(SortNumericTest, sortThreeBAC) {
  typename TestFixture::value_type data[] = { 1, 0, 2 };
  typename TestFixture::value_type expected[] = { 0, 1, 2 };

  this->tester.test(data, expected);
}

TYPED_TEST_P(SortNumericTest, sortThreeBCA) {
  typename TestFixture::value_type data[] = { 1, 2, 0 };
  typename TestFixture::value_type expected[] = { 0, 1, 2 };

  this->tester.test(data, expected);
}

TYPED_TEST_P(SortNumericTest, sortThreeCAB) {
  typename TestFixture::value_type data[] = { 2, 0, 1 };
  typename TestFixture::value_type expected[] = { 0, 1, 2 };

  this->tester.test(data, expected);
}

TYPED_TEST_P(SortNumericTest, sortThreeCBA) {
  typename TestFixture::value_type data[] = { 2, 1, 0 };
  typename TestFixture::value_type expected[] = { 0, 1, 2 };

  this->tester.test(data, expected);
}

/*
  * Duplicates
  */

TYPED_TEST_P(SortNumericTest, sortTwoOfTwoEqual) {
  typename TestFixture::value_type data[] = { 1, 1 };
  typename TestFixture::value_type expected[] = { 1, 1 };

  this->tester.test(data, expected);
}

TYPED_TEST_P(SortNumericTest, sortTwoOfThreeEqual) {
  typename TestFixture::value_type data[] = { 1, 0, 1 };
  typename TestFixture::value_type expected[] = { 0, 1, 1 };

  this->tester.test(data, expected);
}

TYPED_TEST_P(SortNumericTest, sortThreeOfThreeEqual) {
  typename TestFixture::value_type data[] = { 1, 1, 1 };
  typename TestFixture::value_type expected[] = { 1, 1, 1 };

  this->tester.test(data, expected);
}

/*
  * MAX/MIN Values
  */

TYPED_TEST_P(SortNumericTest, sortLimitValues) {
  typename TestFixture::value_type data[] = { this->max, 0, this->max, this->min };
  typename TestFixture::value_type expected[] = { this->min, 0, this->max, this->max };

  this->tester.test(data, expected);
}

/*
  * Other tests
  */ 
TYPED_TEST_P(SortNumericTest, sortLargeA) {
  typename TestFixture::value_type data[] = { 37, this->min, this->big, -2, 231, this->small, this->big, this->max, 0, this->min };
  typename TestFixture::value_type expected[] = { this->min, this->min, this->small, -2, 0, 37, 231, this->big, this->big, this->max };   

  this->tester.test(data, expected);
}

REGISTER_TYPED_TEST_SUITE_P(SortNumericTest,
  sortNone,
  sortOne,
  sortTwoIn,
  sortTwoRev,
  sortThreeABC,
  sortThreeACB,
  sortThreeBAC,
  sortThreeBCA,
  sortThreeCAB,
  sortThreeCBA,
  sortTwoOfTwoEqual,
  sortTwoOfThreeEqual,
  sortThreeOfThreeEqual,
  sortLimitValues,
  sortLargeA
);

typedef testing::Types<
  ArrayTester<int, ListMergeSort<int> >,
  ArrayOfPointerTester<int, ListMergeSort<int*, int**, PointerLess<int> > >,
  VectorTester<int, ListMergeSort<int, std::vector<int>::iterator> >,
  DoubleLinkedListTester<int, ListMergeSort<int, DoubleLinkedList<int>::iterator> >,
  ArrayTester<float, ListMergeSort<float> >,
  ArrayOfPointerTester<float, ListMergeSort<float*, float**, PointerLess<float> > >,
  VectorTester<float, ListMergeSort<float, std::vector<float>::iterator> >,
  DoubleLinkedListTester<float, ListMergeSort<float, DoubleLinkedList<float>::iterator> >
> SortNumericTestTypes;

INSTANTIATE_TYPED_TEST_SUITE_P(
  MainSortNumericTest,
  SortNumericTest,
  SortNumericTestTypes);