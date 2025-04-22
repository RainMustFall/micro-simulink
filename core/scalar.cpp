#include "scalar.h"

Scalar::Scalar(double value) : Function([value](double) { return value; }) {}

double Scalar::GetValue() const { return this->operator()(0); }

std::unique_ptr<Function> Scalar::operator+(const Function &rhs) {
  return rhs.OperatorWithScalar(*this, std::plus<double>());
}

std::unique_ptr<Function> Scalar::Integrate(double lower_limit,
                                            double upper_limit) const {
  return std::make_unique<Scalar>((upper_limit - lower_limit) * GetValue());
}

std::unique_ptr<Function> Scalar::OperatorWithScalar(
    const Function &scalar,
    const std::function<double(double, double)> &op) const {
  return std::unique_ptr<Function>(new Scalar(op(scalar(0), GetValue())));
}

std::unique_ptr<Function> Scalar::calculateMathFunction(
    std::function<double(double)> func) const {
  return std::unique_ptr<Function>(new Scalar(func(GetValue())));
}
