#ifndef FUNCTION_H
#define FUNCTION_H

#include <functional>
#include <memory>

class Function {
 public:
  Function(std::function<double(double)> function);
  virtual std::unique_ptr<Function> operator+(const Function &rhs);

  virtual double operator()(double x) const { return function_(x); }

  virtual std::unique_ptr<Function> OperatorWithFunction(
      const Function &function,
      const std::function<double(double, double)> &op) const;

  virtual std::unique_ptr<Function> OperatorWithScalar(
      const Function &scalar,
      const std::function<double(double, double)> &op) const;

 private:
  std::function<double(double)> function_;
};

#endif  // FUNCTION_H
