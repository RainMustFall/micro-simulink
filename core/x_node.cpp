#include "x_node.h"

std::unique_ptr<ExecutionResult> XNode::Execute(
    const ExecutionResultFactory &factory) const {
  return factory.CreateX();
}

size_t XNode::GetNumInputs() const { return 0; }

Node &XNode::AttachInput(size_t, const Node &) {
  throw std::runtime_error("X does not accept inputs");
}

Node &XNode::DetachInput(size_t) {
  throw std::runtime_error("X does not accept inputs");
}
