#include "function.h"

Function::Function(std::function<double(double)> function)
    : function_(std::move(function)) {}

Function Function::operator+(const Function &rhs) {
  return Function([lhs = this->function_, rhs = rhs.function_](double x) {
    return lhs(x) + rhs(x);
  });
}
