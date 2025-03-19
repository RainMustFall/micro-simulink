#include "scalar_node.h"

ScalarNode::ScalarNode(double value) : value_{value} {}

std::unique_ptr<ExecutionResult> ScalarNode::Execute(
    const ExecutionResultFactory &factory) const {
  return factory.CreateScalar(value_);
}

size_t ScalarNode::GetNumInputs() const { return 0; }

Node &ScalarNode::AttachInput(size_t, const Node &) {
  throw std::runtime_error("Scalar does not accept inputs");
}

Node &ScalarNode::DetachInput(size_t) {
  throw std::runtime_error("Scalar does not accept inputs");
}
