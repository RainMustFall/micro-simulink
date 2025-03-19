#ifndef X_NODE_H
#define X_NODE_H

#include "node.h"

class XNode : public Node {
 public:
  std::unique_ptr<ExecutionResult> Execute(
      const ExecutionResultFactory &factory) const override;
  size_t GetNumInputs() const override;
  Node &AttachInput(size_t slot_index, const Node &node) override;
  Node &DetachInput(size_t slot_index) override;
};

#endif  // X_NODE_H
