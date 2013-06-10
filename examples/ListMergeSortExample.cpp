/** \file
 * Example usage of ListMergeSort of data in a DoubleLinkedList.
 */

#include <stdexcept>
#include <iostream>

#include "DoubleLinkedList.h"
#include "ListMergeSort.h"

int main(int argc, char**argv) {
  // Convenience typedef
  typedef Experiment::DoubleLinkedList<int> List;

  // Create and populate
  List list;
  list.push_back(2);
  list.push_back(1);
  list.push_back(0);

  // Sort
  Experiment::ListMergeSort<int, List::iterator> sort;
  sort.sort(list);
 
  // Iterate across the list printing the results
  std::cout << "Sorted [ ";
  for(List::iterator iter = list.begin(); iter != list.end(); ++iter) {
    std::cout << *iter << " ";
  }
  std::cout << "]" << std::endl;

  return 0;
}
