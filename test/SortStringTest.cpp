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
 * Test Cases with string data for Sort algorithms.  Currently: ListMergeSort.
 */


#include <stdexcept>

#include "DoubleLinkedList.h"
#include "ListMergeSort.h"
#include "Predicates.h"

#include "SortHelp.h"

#include "gtest/gtest.h"

using Experiment::DoubleLinkedList;
using Experiment::ListMergeSort;
using Experiment::PointerLess;

/** Template test::Test providing the test data string-based Sort
 * algorithms.
 *
 * This is used by creating a typedef with the template parameters specified and
 * providing it to googletest definition later.
 *
 * This class is applied to a Tester type, which must have a
 * type Tester::value_type.
 * 
 * \tparam Tester the container-specific test code
 */
template<class Tester>
class SortStringTest : public testing::Test {
protected:
  typedef Tester tester_type;
  typedef typename Tester::value_type value_type;

  /** Known empty string value */
  const value_type empty;

  tester_type tester;

  // All constructors, destructors, and assignment operators = default
};
TYPED_TEST_SUITE_P(SortStringTest);

/*
  * Trivial Cases
  */
TYPED_TEST_P(SortStringTest, sortNone) {
  this->tester.testEmpty();
}

TYPED_TEST_P(SortStringTest, sortOne) {
  typename TestFixture::value_type data[] = { "a" };
  typename TestFixture::value_type expected[] = { "a" };

  this->tester.test(data, expected);
}

/*
  * Two elements
  */

TYPED_TEST_P(SortStringTest, sortTwoIn) {
  typename TestFixture::value_type data[] = { "a", "b" };
  typename TestFixture::value_type expected[] = { "a", "b" };

  this->tester.test(data, expected);
}

TYPED_TEST_P(SortStringTest, sortTwoRev) {
  typename TestFixture::value_type data[] = { "b", "a" };
  typename TestFixture::value_type expected[] = { "a", "b" };

  this->tester.test(data, expected);
}

/*
  * Three unique element permutations
  */
TYPED_TEST_P(SortStringTest, sortThreeABC) { // In Order
  typename TestFixture::value_type data[] = { "a", "b", "c" };
  typename TestFixture::value_type expected[] = { "a", "b", "c" };

  this->tester.test(data, expected);
}

TYPED_TEST_P(SortStringTest, sortThreeACB) {
  typename TestFixture::value_type data[] = { "a", "c", "b" };
  typename TestFixture::value_type expected[] = { "a", "b", "c" };

  this->tester.test(data, expected);
}

TYPED_TEST_P(SortStringTest, sortThreeBAC) {
  typename TestFixture::value_type data[] = { "b", "a", "c" };
  typename TestFixture::value_type expected[] = { "a", "b", "c" };

  this->tester.test(data, expected);
}

TYPED_TEST_P(SortStringTest, sortThreeBCA) {
  typename TestFixture::value_type data[] = { "b", "c", "a" };
  typename TestFixture::value_type expected[] = { "a", "b", "c" };

  this->tester.test(data, expected);
}

TYPED_TEST_P(SortStringTest, sortThreeCAB) {
  typename TestFixture::value_type data[] = { "c", "a", "b" };
  typename TestFixture::value_type expected[] = { "a", "b", "c" };

  this->tester.test(data, expected);
}

TYPED_TEST_P(SortStringTest, sortThreeCBA) { // reverse
  typename TestFixture::value_type data[] = { "c", "b", "a" };
  typename TestFixture::value_type expected[] = { "a", "b", "c" };

  this->tester.test(data, expected);
}

/*
  * Duplicates
  */

TYPED_TEST_P(SortStringTest, sortTwoOfTwoEqual) {
  typename TestFixture::value_type data[] = { "a", "a" };
  typename TestFixture::value_type expected[] = { "a", "a" };

  this->tester.test(data, expected);
}

TYPED_TEST_P(SortStringTest, sortTwoOfThreeEqual) {
  typename TestFixture::value_type data[] = { "b", "a", "b" };
  typename TestFixture::value_type expected[] = { "a", "b", "b" };

  this->tester.test(data, expected);
}

TYPED_TEST_P(SortStringTest, sortThreeOfThreeEqual) {
  typename TestFixture::value_type data[] = { "a", "a", "a" };
  typename TestFixture::value_type expected[] = { "a", "a", "a" };

  this->tester.test(data, expected);
}

/*
  * Other tests
  */
// Note: We already tested copies of the same stirng

TYPED_TEST_P(SortStringTest, sortEmptyFirst) {
  typename TestFixture::value_type data[] = { "a", this->empty };
  typename TestFixture::value_type expected[] = { this->empty, "a" };

  this->tester.test(data, expected);
}    

TYPED_TEST_P(SortStringTest, sortShorterMatchFirst) {
  typename TestFixture::value_type data[] = { "aaaaaa", "aa" };
  typename TestFixture::value_type expected[] = { "aa", "aaaaaa" };

  this->tester.test(data, expected);
}    

TYPED_TEST_P(SortStringTest, sortFirstCharsFirst) {
  typename TestFixture::value_type data[] = { "ab", "aaaaaa" };
  typename TestFixture::value_type expected[] = { "aaaaaa", "ab" };

  this->tester.test(data, expected);
}    

TYPED_TEST_P(SortStringTest, sortUppercaseFirst) {
  typename TestFixture::value_type data[] = { "aaaaaa", "aA" };
  typename TestFixture::value_type expected[] = { "aA", "aaaaaa" };

  this->tester.test(data, expected);
}    

TYPED_TEST_P(SortStringTest, sortNumbersFirst) {
  typename TestFixture::value_type data[] = { "a", "A", "1" };
  typename TestFixture::value_type expected[] = { "1", "A", "a" };

  this->tester.test(data, expected);
}

TYPED_TEST_P(SortStringTest, sortNumbersAsStrings) {
  typename TestFixture::value_type data[] = { "100", "99", "10", "1", "11" };
  typename TestFixture::value_type expected[] = { "1", "10", "100", "11", "99" };

  this->tester.test(data, expected);
}

TYPED_TEST_P(SortStringTest, sortSpecial) {
  typename TestFixture::value_type data[] = { "a\"b", "a^b", "a(b", "aab", "a%b", "aAb" };
  typename TestFixture::value_type expected[] = { "a\"b", "a%b", "a(b", "aAb", "a^b", "aab" };

  this->tester.test(data, expected);
}

TYPED_TEST_P(SortStringTest, sortLargeA) {
  typename TestFixture::value_type data[] = { "apple", this->empty, "100", "Apple", this->empty, "9", "App", "1", "9", "APPLE", "apples and oranges" };
  typename TestFixture::value_type expected[] = { this->empty, this->empty, "1", "100", "9", "9", "APPLE", "App", "Apple", "apple", "apples and oranges" };

  this->tester.test(data, expected);
}

REGISTER_TYPED_TEST_SUITE_P(SortStringTest,
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

  sortEmptyFirst,
  sortShorterMatchFirst,
  sortFirstCharsFirst,
  sortUppercaseFirst,
  sortNumbersFirst,
  sortNumbersAsStrings,
  sortSpecial,
  sortLargeA
);

typedef testing::Types<
  ArrayTester<std::string, ListMergeSort<std::string> >,
  ArrayOfPointerTester<std::string, ListMergeSort<std::string*, std::string**, PointerLess<std::string> > >,
  VectorTester<std::string, ListMergeSort<std::string, std::vector<std::string>::iterator> >,
  DoubleLinkedListTester<std::string, ListMergeSort<std::string, DoubleLinkedList<std::string>::iterator> >
> SortStringTestTypes;

INSTANTIATE_TYPED_TEST_SUITE_P(
  MainSortStringTest,
  SortStringTest,
  SortStringTestTypes);