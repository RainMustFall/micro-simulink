#include "scalar_result_factory.h"

#include "function.h"
#include "scalar.h"

std::unique_ptr<Function> FunctionFactory::CreateScalar(double scalar) const {
  return std::make_unique<Scalar>(scalar);
}

std::unique_ptr<Function> FunctionFactory::CreateX() const {
  return std::make_unique<Function>([](double x) { return x; });
}
