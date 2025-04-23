#ifndef X_NODE_H
#define X_NODE_H

#include "execution_result_concept.h"
#include "node.h"

/*!
 * @brief Graph node without input.
 *
 *  Returns an object of type T that represents the function y = x (e.g. functor
 * or LaTeX expression “x”).
 */
template <GraphExecutionResult T>
class XNode : public Node<T> {
 public:
  XNode() : Node<T>(0) {}

  std::unique_ptr<T> Execute(
      const ExecutionResultFactory<T> &factory) const override {
    return factory.CreateX();
  }
};

#endif  // X_NODE_H
