#ifndef EXECUTION_RESULT_FACTORY_H
#define EXECUTION_RESULT_FACTORY_H

#include <memory>

#include "execution_result.h"

class ExecutionResultFactory {
 public:
  virtual std::unique_ptr<ExecutionResult> CreateScalar(double scalar) const = 0;
  virtual std::unique_ptr<ExecutionResult> CreateX() const = 0;
};

#endif  // EXECUTION_RESULT_FACTORY_H
