#ifndef EXECUTION_RESULT_H
#define EXECUTION_RESULT_H

#include <memory>

class ExecutionResult {
 public:
  virtual std::unique_ptr<ExecutionResult> add(
      std::unique_ptr<ExecutionResult> rhs) const = 0;
};

#endif  // EXECUTION_RESULT_H
