#ifndef ROOT_NODE_H
#define ROOT_NODE_H

#include "node.h"

/*!
 * @brief The RootNode class
 *
 * Graph execution starts from the root. It simply returns the result of its
 * only dependency.
 */
template <typename T>
class RootNode : public Node<T> {
 public:
  RootNode() : Node<T>(1) {}

  std::unique_ptr<T> Execute(
      const ExecutionResultFactory<T> &factory) const override {
    auto inputs = this->ExecuteDependencies(factory);
    return std::move(inputs.front());
  }
};

#endif  // ROOT_NODE_H
