#include "function.h"

#include <memory>

Function::Function(std::function<double(double)> function)
    : function_(std::move(function)) {}

std::unique_ptr<Function> Function::operator+(const Function &rhs) {
  return rhs.OperatorWithFunction(*this, std::plus<double>());
}

std::unique_ptr<Function> Function::OperatorWithFunction(
    const Function &function,
    const std::function<double(double, double)> &op) const {
  return std::make_unique<Function>(
      [lhs = function.function_, rhs = this->function_, op = op](double x) {
        return op(lhs(x), rhs(x));
      });
}

std::unique_ptr<Function> Function::OperatorWithScalar(
    const Function &scalar,
    const std::function<double(double, double)> &op) const {
  return OperatorWithFunction(scalar, op);
}
