#ifndef NEGATION_NODE_H
#define NEGATION_NODE_H

#include "node.h"

/*!
 * @brief The node calculating negation of its input (-x)
 */
template <typename T>
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
