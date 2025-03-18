#ifndef NODE_H
#define NODE_H

#include <execution_result.h>
#include <execution_result_factory.h>

#include <cstddef>
#include <memory>

class Node {
 public:
  virtual std::unique_ptr<ExecutionResult> Execute(
      const ExecutionResultFactory& factory) const = 0;
  virtual size_t GetNumInputs() const = 0;
  virtual Node& AttachInput(size_t slot_index, const Node& node) = 0;
  virtual Node& DetachInput(size_t slot_index) = 0;
};

#endif  // NODE_H
