#include "scalar_result_factory.h"

#include <scalar_result.h>

std::unique_ptr<ExecutionResult> ScalarResultFactory::CreateScalar(
    double scalar) const {
  return std::make_unique<ScalarResult>(scalar);
}

std::unique_ptr<ExecutionResult> ScalarResultFactory::CreateX() const {
  return nullptr;
}
