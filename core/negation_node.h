#ifndef NEGATION_NODE_H
#define NEGATION_NODE_H

#include "execution_result_concept.h"
#include "node.h"

/*!
 * @brief The node calculating negation of its input (-x)
 */
template <GraphExecutionResult T>
class NegationNode : public Node<T> {
 public:
  NegationNode() : Node<T>(1) {}

  std::unique_ptr<T> Execute(
      const ExecutionResultFactory<T> &factory) const override {
    auto inputs = this->ExecuteDependencies(factory);
    return -(*inputs.front());
  }
};

#endif  // NEGATION_NODE_H
