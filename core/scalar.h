#ifndef SCALAR_H
#define SCALAR_H

#include "function.h"

class Scalar : public Function {
 public:
  std::unique_ptr<Function> operator+(const Function &rhs) override;

  virtual std::unique_ptr<Function> Integrate(double lower_limit,
                                              double upper_limit) const;

  Scalar(double value);
  double GetValue() const;

  std::unique_ptr<Function> OperatorWithScalar(
      const Function &scalar,
      const std::function<double(double, double)> &op) const override;
};

#endif  // SCALAR_H
