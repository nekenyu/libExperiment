/*
Copyright (c) 2013, Komodo Does Inc
All rights reserved.

Redistribution and use in source and binary forms, with or without modification, are permitted provided that the following conditions are met:

- Redistributions of source code must retain the above copyright notice, this list of conditions and the following disclaimer.
- Redistributions in binary form must reproduce the above copyright notice, this list of conditions and the following disclaimer in the documentation and/or other materials provided with the distribution.
- Neither the name of the Komodo Does Inc nor the names of its contributors may be used to endorse or promote products derived from this software without specific prior written permission.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

#ifndef LIST_MERGE_SORT_H
#define LIST_MERGE_SORT_H

/** \file
 * DoubleLinkedList-based Merge Sort
 */

#ifndef DOUBLE_LINKED_LIST_H
#include "DoubleLinkedList.h"
#endif // DOUBLE_LINKED_LIST_H

namespace Experiment {
  
  /** Do-nothing Metric-collector for major actions done by ListMergeSort.
   *
   * This serves as a placeholder should you wish to perform metrics on a sort.
   *
   * \tparam type of data being sorted
   */
  template<class T>
    class NoSortMetrics {
  public:
    /** a and b are compared */
    void compare(const T& a, const T&b) { }

    /** Two items were swapped */
    void swap() { }

    /** The sort completed */
    void done() { }

    /** Metrics should be reset due to starting a new sort */
    void reset() { }
  };
  
  /** Merge Sort algorithm using lists to hold the data.
   *
   * The real advantage of this class is that sort() taking a DoubleLinkedList
   * will sort without copying the values in the List -- the list will be
   * disassembled and reassembled in the correct order.
   *
   * \tparam T the data type being sorted
   * \tparam Lessor to compare items
   * \tparam Metrics to collect metrics on the sort -- \see NoSortMetrics as an example
   */
  template<class T, class Iterator = T*, class Lessor = std::less<T>, class Metrics = NoSortMetrics<T> >
    class ListMergeSort {
  public:
  /** Convenience typedef of the type of data in the list */
  typedef T value_type;

  /** Convenience typedef of the type of list used in this sort */
  typedef DoubleLinkedList<T> DataList;

  /** Convenience typedef of the iterator of DataList */
  typedef typename DataList::iterator DataIter;
  
  private:
  /** Convenience typedef of the type of a list of DataList used in this sort */  
  typedef DoubleLinkedList<DataList> ListList;

  /** Convenience typedef of the iterator of ListList */
  typedef typename ListList::iterator ListIter;
  
  public:
  
  /** Sort from begin to end by copying.
   *
   * First, this copies all values to temporary storage.  Then it stores.
   * Finally, it copies the results back.
   *
   * This avoids copying values at each stage of the sort as an array-based
   * merge sort would; however, it still copies the values twice.
   *
   * \param begin first value to sort
   * \param end the position after the last value to sort
   */ 
  void sort(const Iterator begin, const Iterator end) {
    if(end == begin) {
      return;
    }
    
    // Load initial list
    ListList listA;
    for(Iterator iter = begin; iter != end; ++iter) {
      listA.push_back(DataList());
      ListIter added = listA.end() - 1;
      added->push_back(*iter);
    }
    
    // Create second ListList, location flag, and merge
    ListList listB;
    bool dataInListA = true;
    DataList& sorted = mergeSort(listA, listB, dataInListA);
    // NOTE: listA, listB and dataInListA must stay in scope with sorted
    
    // Overwrite original list
    {
      Iterator originalIter = begin;
      DataIter sortedIter = sorted.begin();
      for( ; originalIter != end && sorted.end() != sortedIter; ++originalIter, ++sortedIter) {
	*originalIter = *sortedIter; 
      }

      // We should do something to ensure we ddidn't lose values...
    }
    metrics.done();
  }

  /** Sort the values in data in constant memory by removing the disassembling
   * data, sorting the values and reassembling it.
   */
  void sort(DataList& data) {
    if(data.isEmpty() || data.end() == data.begin() + 1) {
      return;
    }
    
    // Remove from argument
    ListList listA;
    for(Iterator iter = data.begin(); data.end() != data.begin(); iter = data.begin()) {
      listA.push_back(DataList());
      ListIter added = listA.end() - 1;
      DataIter dest = added->end();
      moveBefore(iter, dest);
    }

    // Create second ListList, location flag, and merge
    ListList listB;
    bool dataInListA = true;
    DataList& sorted = mergeSort(listA, listB, dataInListA);
    // NOTE: listA, listB and dataInListA must stay in scope with sorted

    // Populate argument
    moveAll(sorted, data);
  }

  private:

  /** merge listA and listB such that which list data is in at the start and
   * end is determined by dataInListA.
   *
   * listA and listB each contain DataLists.
   *
   * At the start of each round of merging, the one used for input has N > 1 
   * DataLists with the first N-1 of length M and the last of length <M. 
   * Merging will move the data back and for between each of listA
   * and listB.  After each pass of merging, the one merged into will have N/2
   * (rounded up) DataLists.
   * 
   * Upon completion, the list with data will have one DataList -- the results.
   *
   * \param listA to be used in merge sorting and, if dataInListA contains the data to be merged
   * \param listB to be used in merge sorting and, if dataInListB contains the data to be merged
   *
   * \return convenience reference to the final DataList which is the only
   * element contained in (dataIsInListA ? listA or listB).
   *
   * \note The return value is \code *(dataInListA ? listA : listB).begin(); \endcode
   * This means that all three arguments must remain in scope for the return value to
   * remain valid.
   */
  DataList& mergeSort(ListList& listA, ListList& listB, bool& dataInListA) {
    metrics.reset();
    while(true) {
      ListList& input = dataInListA ? listA : listB;
      ListList& output = dataInListA ? listB : listA;
       
      if(input.end() == input.begin() + 1) {
	break;
      }
       
      dataInListA = ! dataInListA;
      mergeLists(input, output);
    }
     
    return *(dataInListA ? listA : listB).begin();
  }

  /** Perform one iteration of merging of sequential pairs of lists in input
   * to ouput.
   *
   * Each pair of lists in input is merged to a single list in output.  If 
   * input has an odd number of lists, the last list is moved in without
   * any merge necessary.
   *
   * \param input List of sequential pairs of sorted DataList to merge together
   * \param output the list to write the output DataLists to.
   */
  void mergeLists(ListList& input, ListList& output) {
    output.clear();
    // Pass across input list
    ListIter listIter = input.begin();
    while(input.end() != listIter) {
      // Create new DataList for merge(DataList, DataList) -> DataList
      output.push_back(DataList());
      ListIter current = output.end() - 1;
     
      // Grab next one or two (if available) from input
      ListIter first = listIter;
      ++listIter;
     
      ListIter second = listIter;
      ++listIter;
     
      // Merge the one and possible second list together
      if(input.end() == second) {
	// No second list, copy first as new entry in output
	moveAll(*first, *current);
      } else {
	// Two lists, just merge them
	mergeTwo(*first, *second, *current);
      }
    }
  }

  /** Merge two sorted DataList elements, first and second, into out
   *
   * \param first DataList to merge with second into out
   * \param second DataList to merge with first into out
   * \param out DataList containing the merge sort of first and second
   */
  void mergeTwo(DataList& first, DataList& second, DataList& out) {
    // Merge first and second into new entry in output
    DataIter dest = out.end();
    while(!first.isEmpty() && !second.isEmpty()) {
      DataIter firstIter = first.begin();
      DataIter secondIter = second.begin();
      metrics.compare(*firstIter, *secondIter);
      if(lessor(*firstIter, *secondIter)) {
	metrics.swap();
	moveBefore(firstIter, dest);
      } else {
	moveBefore(secondIter, dest);
      }
    }

    // When first or second is empty, we 'merge' by moving the remaining values
    // of the other to the end of out.
    moveAll(first, out);
    moveAll(second, out);
  }

  /** Move all values from from to the end of to
   *
   * \param from to move all values, if any, to the end of to
   * \param to to move all values, if any, from from to the end of
   */
  void moveAll(DataList& from, DataList& to) {
    while(!from.isEmpty()) {
      DataIter iter = from.begin();
      DataIter dest = to.end();
      moveBefore(iter, dest);
    }
  }

  private:
  /** Comparator to decide if one value is less than another */
  Lessor lessor;
 
  public:
  /** Collection of metrics for the caller to inspect details of the sort */
  Metrics metrics;
  };

} // namespace Experiment

#endif // LIST_MERGE_SORT_H
