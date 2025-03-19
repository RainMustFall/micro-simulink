#ifndef FUNCTION_H
#define FUNCTION_H

#include <functional>

#include "execution_result.h"

class Function : public ExecutionResult {
 public:
  Function(std::function<double(double)> function);
  std::unique_ptr<ExecutionResult> add(
      std::unique_ptr<ExecutionResult> rhs) const;

  virtual double operator()(double x) const { return function_(x); }

 private:
  std::function<double(double)> function_;
};

#endif  // FUNCTION_H
