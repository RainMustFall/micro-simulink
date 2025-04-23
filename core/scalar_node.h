#ifndef SCALAR_NODE_H
#define SCALAR_NODE_H

#include "execution_result_concept.h"
#include "node.h"

/*!
 * @brief A node of a graph with no input.
 *
 * Returns an object of type T, which represents the number stored in this node
 * (e.g. scalar 5 or LaTeX expression “5”).
 */
template <GraphExecutionResult T>
class ScalarNode : public Node<T> {
 public:
  /*!
   * @brief ScalarNode
   * @param value - the number stored in this node
   */
  ScalarNode(double value) : Node<T>(0), value_{value} {}

  /*!
   * @brief Set value
   * @param value - a new number stored in this node
   */
  void SetValue(double value) { value_ = value; }

  std::unique_ptr<T> Execute(
      const ExecutionResultFactory<T> &factory) const override {
    return factory.CreateScalar(value_);
  }

 private:
  double value_;
};

#endif  // SCALAR_NODE_H
