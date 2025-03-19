#include "scalar_result_factory.h"

#include "function.h"
#include "scalar.h"

std::unique_ptr<ExecutionResult> ScalarResultFactory::CreateScalar(
    double scalar) const {
  return std::make_unique<Scalar>(scalar);
}

std::unique_ptr<ExecutionResult> ScalarResultFactory::CreateX() const {
  return std::make_unique<Function>([](double x) { return x; });
}
