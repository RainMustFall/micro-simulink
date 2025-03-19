#ifndef FUNCTION_H
#define FUNCTION_H

#include <functional>

class Function {
 public:
  Function(std::function<double(double)> function);
  Function operator+(const Function& rhs);
  virtual double operator()(double x) const { return function_(x); }

 private:
  std::function<double(double)> function_;
};

#endif  // FUNCTION_H
