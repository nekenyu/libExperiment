/** \file
 * Example usage of DoubleLinkedList: creation, population and iteration.
 */

#include <stdexcept>
#include <iostream>

#include "DoubleLinkedList.h"

int main(int argc, char**argv) {

  // Create and populate
  Experiment::DoubleLinkedList<int> list;
  list.push_back(3);
  list.push_back(2);
  list.push_back(4);
  list.push_back(1);
  list.push_back(0);

  // Iterate across the list printing the results
  std::cout << "List [ ";
  for(Experiment::DoubleLinkedList<int>::iterator iter = list.begin(); list.end() != iter; ++iter) {
    std::cout << *iter << " ";
  }
  std::cout << "]" << std::endl;

  return 0;
}
