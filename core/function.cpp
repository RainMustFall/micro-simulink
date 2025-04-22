#include "function.h"

#include <cmath>
#include <memory>

#include "scalar.h"

Function::Function(std::function<double(double)> function)
    : function_(std::move(function)) {}

std::unique_ptr<Function> Function::operator+(const Function &rhs) {
  return rhs.OperatorWithFunction(*this, std::plus<double>());
}

std::unique_ptr<Function> Function::operator-(const Function &rhs) {
  return rhs.OperatorWithFunction(*this, std::minus<double>());
}

std::unique_ptr<Function> Function::operator/(const Function &rhs) {
  return rhs.OperatorWithFunction(*this, std::divides<double>());
}

std::unique_ptr<Function> Function::operator*(const Function &rhs) {
  return rhs.OperatorWithFunction(*this, std::multiplies<double>());
}

std::unique_ptr<Function> Function::operator^(const Function &rhs) {
  return rhs.OperatorWithFunction(
      *this, [](double x, double y) { return std::pow(x, y); });
}

std::unique_ptr<Function> Function::Integrate(double lower_limit,
                                              double upper_limit) const {
  const int n = 1000;  // Number of intervals
  double h = (upper_limit - lower_limit) / n;
  double sum = 0.5 * (function_(lower_limit) + function_(upper_limit));

  for (int i = 1; i < n; ++i) {
    double x = lower_limit + i * h;
    sum += function_(x);
  }

  return std::make_unique<Scalar>(sum * h);
}

std::unique_ptr<Function> Function::Sin() const {
  return calculateMathFunction([](double x) { return std::sin(x); });
}

std::unique_ptr<Function> Function::Cos() const {
  return calculateMathFunction([](double x) { return std::cos(x); });
}

std::unique_ptr<Function> Function::Tan() const {
  return calculateMathFunction([](double x) { return std::tan(x); });
}

std::unique_ptr<Function> Function::Cot() const {
  return calculateMathFunction(
      [](double x) { return std::cos(x) / std::sin(x); });
}

std::unique_ptr<Function> Function::Log() const {
  return calculateMathFunction([](double x) { return std::log(x); });
}

std::unique_ptr<Function> Function::Exp() const {
  return calculateMathFunction([](double x) { return std::exp(x); });
}

std::unique_ptr<Function> Function::Sqrt() const {
  return calculateMathFunction([](double x) { return std::sqrt(x); });
}

std::unique_ptr<Function> Function::operator-() {
  return calculateMathFunction([](double x) { return -x; });
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

std::unique_ptr<Function> Function::calculateMathFunction(
    std::function<double(double)> func) const {
  return std::make_unique<Function>(
      [my_function = this->function_, func](double x) {
        return func(my_function(x));
      });
}
