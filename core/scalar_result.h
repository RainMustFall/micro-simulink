#ifndef SCALAR_RESULT_H
#define SCALAR_RESULT_H

#include <execution_result.h>

class ScalarResult : public ExecutionResult {
 public:
  ScalarResult(double value);

  double GetValue() const;

  std::unique_ptr<ExecutionResult> add(
      std::unique_ptr<ExecutionResult> rhs) const;

 private:
  double value_;
};

#endif  // SCALAR_RESULT_H
