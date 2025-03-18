#ifndef SCALAR_H
#define SCALAR_H

#include "node.h"

class Scalar : public Node {
 public:
  Scalar(double value);
  std::unique_ptr<ExecutionResult> Execute(
      const ExecutionResultFactory &factory) const;
  size_t GetNumInputs() const;
  Node &AttachInput(size_t slot_index, const Node &node);
  Node &DetachInput(size_t slot_index);

 private:
  double value_;
};

#endif  // SCALAR_H
