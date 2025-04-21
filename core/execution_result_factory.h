#ifndef EXECUTION_RESULT_FACTORY_H
#define EXECUTION_RESULT_FACTORY_H

#include <memory>

/*!
 * @brief Factory responsible for creating the object that will be processed in
 * the graph.
 *
 * ScalarNode or XNode call the Create... method of the factory to create an
 * initial object of the appropriate type.
 */
template <typename T>
class ExecutionResultFactory {
 public:
  /*!
   * @brief Create instance of T corresponding to a number
   * @param scalar - the number T corresponds to
   * @return Instance of T created
   */
  virtual std::unique_ptr<T> CreateScalar(double scalar) const = 0;

  /*!
   * @brief Create instance of T corresponding to "x"
   * @return Instance of T created
   */
  virtual std::unique_ptr<T> CreateX() const = 0;
};

#endif  // EXECUTION_RESULT_FACTORY_H
