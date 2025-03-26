#ifndef ROOT_NODE_H
#define ROOT_NODE_H

#include "node.h"

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
