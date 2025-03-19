#ifndef EXECUTION_RESULT_FACTORY_H
#define EXECUTION_RESULT_FACTORY_H

#include <memory>

template <typename T>
class ExecutionResultFactory {
 public:
  virtual std::unique_ptr<T> CreateScalar(double scalar) const = 0;
  virtual std::unique_ptr<T> CreateX() const = 0;
};

#endif  // EXECUTION_RESULT_FACTORY_H
