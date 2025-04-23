#ifndef UNARY_ALGEBRAIC_FUNCTIONS_H
#define UNARY_ALGEBRAIC_FUNCTIONS_H

#include "execution_result_concept.h"
#include "node.h"

/*!
 * @brief The node calculating square root of its input
 */
template <GraphExecutionResult T>
class SqrtNode : public Node<T> {
 public:
  SqrtNode() : Node<T>(1) {}

  std::unique_ptr<T> Execute(
      const ExecutionResultFactory<T> &factory) const override {
    auto inputs = this->ExecuteDependencies(factory);
    return inputs.front()->Sqrt();
  }
};

/*!
 * @brief The node calculating natural log of its input
 */
template <GraphExecutionResult T>
class LogNode : public Node<T> {
 public:
  LogNode() : Node<T>(1) {}

  std::unique_ptr<T> Execute(
      const ExecutionResultFactory<T> &factory) const override {
    auto inputs = this->ExecuteDependencies(factory);
    return inputs.front()->Log();
  }
};

/*!
 * @brief The node calculating exponent of its input
 */
template <GraphExecutionResult T>
class ExpNode : public Node<T> {
 public:
  ExpNode() : Node<T>(1) {}

  std::unique_ptr<T> Execute(
      const ExecutionResultFactory<T> &factory) const override {
    auto inputs = this->ExecuteDependencies(factory);
    return inputs.front()->Exp();
  }
};

#endif  // UNARY_ALGEBRAIC_FUNCTIONS_H
