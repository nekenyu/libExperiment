#ifndef PREDICATES_H
#define PREDICATES_H

/** \file
 * A collection of helpful predicates for comparison, etc.
 */

namespace Experiment {

  /** Comparison of two pointers values using operator<.
   *
   * This makes explicit comparison of two pointers of a single given type.
   *
   * \tparam T the type to compare as
   */
  template<class T>
    class PointerLess {
  public:
    /** Compare the values *a and *b using operator<.
     *
     * \param a the value to compare to b
     * \param b the value to compare to a
     *
     * \return true if *a < *b, otherwise false.
     */
    bool operator()(const T* const a, const T* const b) {
      return *a < *b; // existing operator<() calls
    }
  };
  
} // namespace Experiment

#endif // PREDICATES_H
