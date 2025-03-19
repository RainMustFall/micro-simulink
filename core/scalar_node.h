#ifndef SCALAR_NODE_H
#define SCALAR_NODE_H

#include "node.h"

template <typename T>
class ScalarNode : public Node<T, 0> {
 public:
  ScalarNode(double value) : value_{value} {}
  std::unique_ptr<T> Execute(const ExecutionResultFactory<T> &factory) const override {
    return factory.CreateScalar(value_);
  }

 private:
  double value_;
};

#endif  // SCALAR_NODE_H
