#ifndef BINARY_OPERATOR_H
#define BINARY_OPERATOR_H

#include "node.h"

class BinaryOperator : public Node {
 public:
  std::unique_ptr<ExecutionResult> Execute(
      const ExecutionResultFactory &factory) const override;

  size_t GetNumInputs() const override;

  Node &AttachInput(size_t slot_index, const Node &node) override;

  Node &DetachInput(size_t slot_index) override;

 protected:
  virtual std::unique_ptr<ExecutionResult> Operation(
      std::unique_ptr<ExecutionResult> lhs,
      std::unique_ptr<ExecutionResult> rhs) const = 0;

 private:
  std::pair<const Node *, const Node *> dependencies_;
};

class PlusOperator : public BinaryOperator {
 protected:
  virtual std::unique_ptr<ExecutionResult> Operation(
      std::unique_ptr<ExecutionResult> lhs,
      std::unique_ptr<ExecutionResult> rhs) const override;
};

class MinusOperator : public BinaryOperator {
 protected:
  virtual std::unique_ptr<ExecutionResult> Operation(
      std::unique_ptr<ExecutionResult> lhs,
      std::unique_ptr<ExecutionResult> rhs) const override;
};

class MultiplyOperator : public BinaryOperator {
 protected:
  virtual std::unique_ptr<ExecutionResult> Operation(
      std::unique_ptr<ExecutionResult> lhs,
      std::unique_ptr<ExecutionResult> rhs) const override;
};

class DivideOperator : public BinaryOperator {
 protected:
  virtual std::unique_ptr<ExecutionResult> Operation(
      std::unique_ptr<ExecutionResult> lhs,
      std::unique_ptr<ExecutionResult> rhs) const override;
};

#endif  // BINARY_OPERATOR_H
