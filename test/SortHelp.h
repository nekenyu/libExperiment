#ifndef SORT_HELP_H
#define SORT_HELP_H

/** \file
 * Helper file providing methods of testing Sort algorithms per container type
 */

using Experiment::DoubleLinkedList;

/** Template Test methods for array of type T to be sorted by Sort
 *
 * \tparam T data type in Array
 * \tparam Sort Sort Algorithm to use
 */
template<class T, class Sort>
class ArrayTester {
 public:
  /** Test Sort of an empty container */
  void testEmpty() {
    T* array = NULL;

    Sort sort;
    sort.sort(array, array);
  }

  /** Test with input data to match expected
   *
   * \param data ordered values of length as input to sort
   * \param exected ordered values of length after sort
   *
   * \tparam length of data and expected
   */
  template<size_t length>
    void test(T (&data)[length], T (&expected)[length]) {
    Sort sort;
    sort.sort(data, data + length);
    
    // Assumes data type not susceptable to instability
    for(size_t index = 0; index < length; ++index) {
      CPPUNIT_ASSERT_EQUAL(data[index], expected[index]);
    }
  }
};

/** Template Test methods for array of pointer of type T to be sorted by Sort
 *
 * \tparam T data type in Array of pointer
 * \tparam Sort Sort Algorithm to use
 */
template<class T, class Sort>
class ArrayOfPointerTester {
 public:
  /** Test Sort of an empty container */
  void testEmpty() {
    T** arrayOfPointers = NULL;
      
    // Do the Sort
    Sort sort;
    sort.sort(arrayOfPointers, arrayOfPointers);
  }

  /** Test with input data to match expected
   *
   * \param data ordered values of length as input to sort
   * \param exected ordered values of length after sort
   *
   * \tparam length of data and expected
   */
  template<size_t length>
    void test(T (&data)[length], T (&expected)[length]) {
    // Initialize Array Of Pointers
    T* arrayOfPointers[length];
    {
      T* iter = data;
      for(int i = 0; i < length; ++i, ++iter) {
	arrayOfPointers[i] = new T(*iter);
      }
    }

    // Do the Sort
    Sort sort;
    sort.sort(arrayOfPointers, arrayOfPointers + length);
    
    // Test Array Of Pointers
    // Assumes data type not susceptable to instability
    for(size_t index = 0; index < length; ++index) {
      CPPUNIT_ASSERT_EQUAL(*arrayOfPointers[index], expected[index]);
    }

    // Delete pointers in arrayOfPointers
    {
      T* iter = data;
      for(int i = 0; i < length; ++i, ++iter) {
	delete arrayOfPointers[i];
      }
    }
  }
};

/** Template Test methods for vector of type T to be sorted by Sort
 *
 * \tparam T data type in vector
 * \tparam Sort Sort Algorithm to use
 */
template<class T, class Sort>
  class VectorTester {
 public:
  /** Test Sort of an empty container */
  void testEmpty() {
    std::vector<T> dataVec;

    Sort sort;
    sort.sort(dataVec.begin(), dataVec.end());

    CPPUNIT_ASSERT(dataVec.empty());
  }

  /** Test with input data to match expected
   *
   * \param data ordered values of length as input to sort
   * \param exected ordered values of length after sort
   *
   * \tparam length of data and expected
   */
  template<size_t length>
    void test(T (&data)[length], T (&expected)[length]) {
    std::vector<T> dataVec;
    dataVec.insert(dataVec.begin(), data, data + length);

    Sort sort;
    sort.sort(dataVec.begin(), dataVec.end());
    
    // Assumes data type not susceptable to instability
    typename std::vector<T>::iterator dataIter = dataVec.begin();
    T* expectedIter = expected;
    for( ; dataVec.end() != dataIter && (expected + length) != expectedIter; ++dataIter, ++expectedIter) {
      CPPUNIT_ASSERT_EQUAL(*dataIter, *expectedIter);
    }
 
    CPPUNIT_ASSERT(dataVec.end() == dataIter);
    CPPUNIT_ASSERT(expected + length == expectedIter);
  }
};

/** Template Test methods for DoubleLinkedList of type T to be sorted by Sort
 *
 * \tparam T data type in DoubleLinkedList
 * \tparam Sort Sort Algorithm to use
 */
template<class T, class Sort>
  class DoubleLinkedListTester {
 public:
  /** Test Sort of an empty container */
  void testEmpty() {
    DoubleLinkedList<T> dataList;
    
    Sort sort;
    sort.sort(dataList.begin(), dataList.end());
    
    CPPUNIT_ASSERT(dataList.isEmpty());
  }

  /** Test with input data to match expected
   *
   * \param data ordered values of length as input to sort
   * \param exected ordered values of length after sort
   *
   * \tparam length of data and expected
   */
  template<size_t length>
    void test(T (&data)[length], T (&expected)[length]) {
    DoubleLinkedList<T> dataList;
    for(T* iter = data; (data + length) != iter; ++iter) {
      dataList.push_back(*iter);
    }

    Sort sort;
    sort.sort(dataList.begin(), dataList.end());

    // Assumes data type not susceptable to instability
    typename DoubleLinkedList<T>::iterator dataIter = dataList.begin();
    T* expectedIter = expected;
    for( ; dataList.end() != dataIter && (expected + length) != expectedIter; ++dataIter, ++expectedIter) {
      CPPUNIT_ASSERT_EQUAL(*dataIter, *expectedIter);
    }
 
    CPPUNIT_ASSERT(dataList.end() == dataIter);
    CPPUNIT_ASSERT(expected + length == expectedIter);
  }
};

#endif // SORT_HELP_H
