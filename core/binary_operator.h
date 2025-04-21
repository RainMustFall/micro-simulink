#ifndef BINARY_OPERATOR_H
#define BINARY_OPERATOR_H

#include "node.h"

/*!
 * @brief A node with two inputs. Performs addition of dependency results. The
 * meaning of addition is defined by the type T.
 */
template <typename T>
class PlusOperator : public Node<T> {
 public:
  PlusOperator() : Node<T>(2) {}

  std::unique_ptr<T> Execute(
      const ExecutionResultFactory<T> &factory) const override {
    auto inputs = this->ExecuteDependencies(factory);
    return *(inputs.front()) + *(inputs.back());
  }
};

#endif  // BINARY_OPERATOR_H
