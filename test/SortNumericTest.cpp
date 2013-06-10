/** \file
 * Test Cases with int and float data for Sort algorithms.  Currently: ListMergeSort.
 */
#include <limits>
#include <stdexcept>
#include <cppunit/extensions/HelperMacros.h>

#include "DoubleLinkedList.h"
#include "SortHelp.h"

/** Template CppUnit::Fixture providing the test data numeric Sort
 * algorithms.
 *
 * This is used by creating a typedef with the template parameters specified and
 * providing it to CPPUNIT_TEST_SUITE_REGISTRATION.
 *
 * \tparam T the actual data type being tested
 * \tparam Tester the container-specific test code
 */
template<class T, class Tester>
class SortNumericTest : public CppUnit::TestFixture {
  CPPUNIT_TEST_SUITE(SortNumericTest);
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

  CPPUNIT_TEST(sortLargeA);

  CPPUNIT_TEST(sortLimitValues);

  CPPUNIT_TEST_SUITE_END();

private:
  /** Container-specific test code */
  Tester tester;

public:
  /** Construct test with some constants that might be helpful */
  SortNumericTest()
    : max(std::numeric_limits<T>::max()),
      min(std::numeric_limits<T>::is_integer ? std::numeric_limits<T>::min() : - max), 
      big(max / 2), small(min / 4)
  {
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
  void sortNone() {
    tester.testEmpty();
  }

  void sortOne() {
    T data[] = { 1 };
    T expected[] = { 1 };

    tester.test(data, expected);
  }

  /*
   * Two elements
   */

  void sortTwoIn() {
    T data[] = { 0, 1 };
    T expected[] = { 0, 1 };

    tester.test(data, expected);
  }

  void sortTwoRev() {
    T data[] = { 1, 0 };
    T expected[] = { 0, 1 };

    tester.test(data, expected);
  }

  /*
   * Three unique element permutations
   */
  void sortThreeABC() { // In Order
    T data[] = { 0, 1, 2 };
    T expected[] = { 0, 1, 2 };

    tester.test(data, expected);
  }
  
  void sortThreeACB() {
    T data[] = { 0, 2, 1 };
    T expected[] = { 0, 1, 2 };

    tester.test(data, expected);
  }

  void sortThreeBAC() {
    T data[] = { 1, 0, 2 };
    T expected[] = { 0, 1, 2 };

    tester.test(data, expected);
  }

  void sortThreeBCA() {
    T data[] = { 1, 2, 0 };
    T expected[] = { 0, 1, 2 };

    tester.test(data, expected);
  }

  void sortThreeCAB() {
    T data[] = { 2, 0, 1 };
    T expected[] = { 0, 1, 2 };

    tester.test(data, expected);
  }

  void sortThreeCBA() { // reverse
    T data[] = { 2, 1, 0 };
    T expected[] = { 0, 1, 2 };

    tester.test(data, expected);
  }

  /*
   * Duplicates
   */

  void sortTwoOfTwoEqual() {
    T data[] = { 1, 1 };
    T expected[] = { 1, 1 };

    tester.test(data, expected);
  }

  void sortTwoOfThreeEqual() {
    T data[] = { 1, 0, 1 };
    T expected[] = { 0, 1, 1 };

    tester.test(data, expected);
  }

  void sortThreeOfThreeEqual() {
    T data[] = { 1, 1, 1 };
    T expected[] = { 1, 1, 1 };

    tester.test(data, expected);
  }

  /*
   * MAX/MIN Values
   */

  void sortLimitValues() {
    T data[] = { max, 0, max, min  };
    T expected[] = { min, 0, max, max };

    tester.test(data, expected);
  }

  /*
   * Other tests
   */ 
  void sortLargeA() {
    T data[] = { 37, min, big, -2, 231, small, big, max, 0, min };
    T expected[] = { min, min, small, -2, 0, 37, 231, big, big, max };   

    tester.test(data, expected);
  }

private:
  /** Known maximum value for our data type */
  const T max;

  /** Known minimum value for our data type */
  const T min;

  /** Known big value for our data type such that 0 < big < max */
  const T big;

  /** Known small value for our data type such that min < small < 0 */
  const T small;
};

/*
 * Templated test cases
 */

#include "Predicates.h"
#include "ListMergeSort.h"
using Experiment::ListMergeSort;
using Experiment::PointerLess;

typedef SortNumericTest<int, ArrayTester<int, ListMergeSort<int> > > ListMergeSortIntArrayTest;
CPPUNIT_TEST_SUITE_REGISTRATION(ListMergeSortIntArrayTest);

typedef SortNumericTest<int, ArrayOfPointerTester<int, ListMergeSort<int*, int**, PointerLess<int> > > > ListMergeSortIntArrayOfPointerTest;
CPPUNIT_TEST_SUITE_REGISTRATION(ListMergeSortIntArrayOfPointerTest);

typedef SortNumericTest<int, VectorTester<int, ListMergeSort<int, std::vector<int>::iterator> > > ListMergeSorIntVectorTest;
CPPUNIT_TEST_SUITE_REGISTRATION(ListMergeSorIntVectorTest);

typedef SortNumericTest<int, DoubleLinkedListTester<int, ListMergeSort<int, DoubleLinkedList<int>::iterator> > > ListMergeSortIntDoubleLinkedListTest;
CPPUNIT_TEST_SUITE_REGISTRATION(ListMergeSortIntDoubleLinkedListTest);


typedef SortNumericTest<float, ArrayTester<float, ListMergeSort<float> > > ListMergeSortFloatArrayTest;
CPPUNIT_TEST_SUITE_REGISTRATION(ListMergeSortFloatArrayTest);

typedef SortNumericTest<float, ArrayOfPointerTester<float, ListMergeSort<float*, float**, PointerLess<float> > > > ListMergeSortFloatArrayOfPointerTest;
CPPUNIT_TEST_SUITE_REGISTRATION(ListMergeSortFloatArrayOfPointerTest);

typedef SortNumericTest<float, VectorTester<float, ListMergeSort<float, std::vector<float>::iterator> > > ListMergeSortFloatVectorTest;
CPPUNIT_TEST_SUITE_REGISTRATION(ListMergeSortFloatVectorTest);

typedef SortNumericTest<float, DoubleLinkedListTester<float, ListMergeSort<float, DoubleLinkedList<float>::iterator> > > ListMergeSortFloatDoubleLinkedListTest;
CPPUNIT_TEST_SUITE_REGISTRATION(ListMergeSortFloatDoubleLinkedListTest);
