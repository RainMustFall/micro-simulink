#ifndef X_NODE_H
#define X_NODE_H

#include "node.h"

template <typename T>
class XNode : public Node<T> {
 public:
  XNode() : Node<T>(0) {}

  std::unique_ptr<T> Execute(
      const ExecutionResultFactory<T> &factory) const override {
    return factory.CreateX();
  }
};

#endif  // X_NODE_H
