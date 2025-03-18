#include "binary_operator.h"

std::unique_ptr<ExecutionResult> BinaryOperator::Execute(
    const ExecutionResultFactory &factory) const {
  if (dependencies_.first == nullptr || dependencies_.second == nullptr) {
    throw std::runtime_error("Binary operator misses one or both inputs");
  }

  return Operation(dependencies_.first->Execute(factory),
                   dependencies_.second->Execute(factory));
}

size_t BinaryOperator::GetNumInputs() const { return 2; }

Node &BinaryOperator::AttachInput(size_t slot_index, const Node &node) {
  switch (slot_index) {
    case 0:
      dependencies_.first = &node;
      return *this;
    case 1:
      dependencies_.second = &node;
      return *this;
    default:
      throw std::out_of_range(
          "Only input indexes 0 and 1 are allowed for BinaryOperator");
  }
}

Node &BinaryOperator::DetachInput(size_t slot_index) {
  switch (slot_index) {
    case 0:
      dependencies_.first = nullptr;
      return *this;
    case 1:
      dependencies_.second = nullptr;
      return *this;
    default:
      throw std::out_of_range(
          "Only input indexes 0 and 1 are allowed for BinaryOperator");
  }
}

std::unique_ptr<ExecutionResult> PlusOperator::Operation(
    std::unique_ptr<ExecutionResult> lhs,
    std::unique_ptr<ExecutionResult> rhs) const {
  return lhs->add(std::move(rhs));
}
