#include "function.h"

Function::Function(
    std::function<double(double)> function)
    : function_(std::move(function)) {}

std::unique_ptr<ExecutionResult> Function::add(
    std::unique_ptr<ExecutionResult> rhs) const {
  auto rhs_function = static_cast<const Function*>(rhs.get());

  return std::make_unique<Function>(
      [lhs = this->function_, rhs = rhs_function->function_](double x) {
        return lhs(x) + rhs(x);
      });
}
