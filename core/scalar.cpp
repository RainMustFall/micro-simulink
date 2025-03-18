#include "scalar.h"

Scalar::Scalar(double value) : value_{value} {}

std::unique_ptr<ExecutionResult> Scalar::Execute(
    const ExecutionResultFactory &factory) const {
  return factory.CreateScalar(value_);
}

size_t Scalar::GetNumInputs() const { return 0; }

Node &Scalar::AttachInput(size_t, const Node &) {
  throw std::runtime_error("Scalar does not accept inputs");
}

Node &Scalar::DetachInput(size_t) {
  throw std::runtime_error("Scalar does not accept inputs");
}
