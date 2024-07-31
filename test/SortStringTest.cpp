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
#include <cppunit/extensions/HelperMacros.h>

#include "DoubleLinkedList.h"
#include "SortHelp.h"

/** Template CppUnit::Fixture providing the test data string-based Sort
 * algorithms.
 *
 * This is used by creating a typedef with the template parameters specified and
 * providing it to CPPUNIT_TEST_SUITE_REGISTRATION.
 *
 * \tparam T the actual data type being tested
 * \tparam Tester the container-specific test code
 */
template<class T, class Tester>
class SortStringTest : public CppUnit::TestFixture {
  CPPUNIT_TEST_SUITE(SortStringTest);
  CPPUNIT_TEST(sortNone);
  CPPUNIT_TEST(sortOne);

  CPPUNIT_TEST(sortTwoIn);
  CPPUNIT_TEST(sortTwoRev);

  CPPUNIT_TEST(sortThreeABC); // in
  CPPUNIT_TEST(sortThreeACB);
  CPPUNIT_TEST(sortThreeBAC);
  CPPUNIT_TEST(sortThreeBCA);
  CPPUNIT_TEST(sortThreeCAB);
  CPPUNIT_TEST(sortThreeCBA); // reverse

  CPPUNIT_TEST(sortTwoOfTwoEqual); 
  CPPUNIT_TEST(sortTwoOfThreeEqual); 
  CPPUNIT_TEST(sortThreeOfThreeEqual); 

  CPPUNIT_TEST(sortEmptyFirst);
  CPPUNIT_TEST(sortShorterMatchFirst);
  CPPUNIT_TEST(sortFirstCharsFirst);
  CPPUNIT_TEST(sortUppercaseFirst);
  CPPUNIT_TEST(sortNumbersFirst);
  CPPUNIT_TEST(sortNumbersAsStrings);
  CPPUNIT_TEST(sortSpecial);
  CPPUNIT_TEST(sortLargeA); 

  CPPUNIT_TEST_SUITE_END();

private:
  /** Container-specific test code */
  Tester tester;

public:
  /*
   *
   * Actual Test Cases
   *
   */

  /*
   * Trivial Cases
   */
  void sortNone() {
    tester.testEmpty();
  }

  void sortOne() {
    T data[] = { "a" };
    T expected[] = { "a" };

    tester.test(data, expected);
  }

  /*
   * Two elements
   */

  void sortTwoIn() {
    T data[] = { "a", "b" };
    T expected[] = { "a", "b" };

    tester.test(data, expected);
  }

  void sortTwoRev() {
    T data[] = { "b", "a" };
    T expected[] = { "a", "b" };

    tester.test(data, expected);
  }

  /*
   * Three unique element permutations
   */
  void sortThreeABC() { // In Order
    T data[] = { "a", "b", "c" };
    T expected[] = { "a", "b", "c" };

    tester.test(data, expected);
  }
  
  void sortThreeACB() {
    T data[] = { "a", "c", "b" };
    T expected[] = { "a", "b", "c" };

    tester.test(data, expected);
  }

  void sortThreeBAC() {
    T data[] = { "b", "a", "c" };
    T expected[] = { "a", "b", "c" };

    tester.test(data, expected);
  }

  void sortThreeBCA() {
    T data[] = { "b", "c", "a" };
    T expected[] = { "a", "b", "c" };

    tester.test(data, expected);
  }

  void sortThreeCAB() {
    T data[] = { "c", "a", "b" };
    T expected[] = { "a", "b", "c" };

    tester.test(data, expected);
  }

  void sortThreeCBA() { // reverse
    T data[] = { "c", "b", "a" };
    T expected[] = { "a", "b", "c" };

    tester.test(data, expected);
  }

  /*
   * Duplicates
   */

  void sortTwoOfTwoEqual() {
    T data[] = { "a", "a" };
    T expected[] = { "a", "a" };

    tester.test(data, expected);
  }

  void sortTwoOfThreeEqual() {
    T data[] = { "b", "a", "b" };
    T expected[] = { "a", "b", "b" };

    tester.test(data, expected);
  }

  void sortThreeOfThreeEqual() {
    T data[] = { "a", "a", "a" };
    T expected[] = { "a", "a", "a" };

    tester.test(data, expected);
  }

  /*
   * Other tests
   */
  // Note: We already tested copies of the same stirng

  void sortEmptyFirst() {
    T data[] = { "a", empty };
    T expected[] = { empty, "a" };

    tester.test(data, expected);
  }    

  void sortShorterMatchFirst() {
    T data[] = { "aaaaaa", "aa" };
    T expected[] = { "aa", "aaaaaa" };

    tester.test(data, expected);
  }    

  void sortFirstCharsFirst() {
    T data[] = { "ab", "aaaaaa" };
    T expected[] = { "aaaaaa", "ab" };

    tester.test(data, expected);
  }    

  void sortUppercaseFirst() {
    T data[] = { "aaaaaa", "aA" };
    T expected[] = { "aA", "aaaaaa" };

    tester.test(data, expected);
  }    

  void sortNumbersFirst() {
    T data[] = { "a", "A", "1" };
    T expected[] = { "1", "A", "a" };

    tester.test(data, expected);
  }

  void sortNumbersAsStrings() {
    T data[] = { "100", "99", "10", "1", "11" };
    T expected[] = { "1", "10", "100", "11", "99" };

    tester.test(data, expected);
  }

  void sortSpecial() {
    T data[] = { "a\"b", "a^b", "a(b", "aab", "a%b", "aAb" };
    T expected[] = { "a\"b", "a%b", "a(b", "aAb", "a^b", "aab" };

    tester.test(data, expected);
  }

  void sortLargeA() {
    T data[] = { "apple", empty, "100", "Apple", empty, "9", "App", "1", "9", "APPLE", "apples and oranges" };
    T expected[] = { empty, empty, "1", "100", "9", "9", "APPLE", "App", "Apple", "apple", "apples and oranges" };

    tester.test(data, expected);
  }

private:
  /** Known empty string value */
  const T empty;
};

/*
 * Templated test cases
 */

#include <string>

#include "Predicates.h"
#include "ListMergeSort.h"
using Experiment::ListMergeSort;
using Experiment::PointerLess;

typedef SortStringTest<std::string, ArrayTester<std::string, ListMergeSort<std::string> > > ListMergeSortStringArrayTest;
CPPUNIT_TEST_SUITE_REGISTRATION(ListMergeSortStringArrayTest);

typedef SortStringTest<std::string, ArrayOfPointerTester<std::string, ListMergeSort<std::string*, std::string**, PointerLess<std::string> > > > ListMergeSortStringArrayOfPointerTest;
CPPUNIT_TEST_SUITE_REGISTRATION(ListMergeSortStringArrayOfPointerTest);

typedef SortStringTest<std::string, VectorTester<std::string, ListMergeSort<std::string, std::vector<std::string>::iterator> > > ListMergeSortStringVectorTest;
CPPUNIT_TEST_SUITE_REGISTRATION(ListMergeSortStringVectorTest);

typedef SortStringTest<std::string, DoubleLinkedListTester<std::string, ListMergeSort<std::string, DoubleLinkedList<std::string>::iterator> > > ListMergeSortStringDoubleLinkedListTest;
CPPUNIT_TEST_SUITE_REGISTRATION(ListMergeSortStringDoubleLinkedListTest);
