#include "scalar_result.h"

ScalarResult::ScalarResult(double value) : value_{value} {}

double ScalarResult::GetValue() const { return value_; }

std::unique_ptr<ExecutionResult> ScalarResult::add(
    std::unique_ptr<ExecutionResult> rhs) const {
  return std::make_unique<ScalarResult>(
      value_ + static_cast<const ScalarResult*>(rhs.get())->GetValue());
}
