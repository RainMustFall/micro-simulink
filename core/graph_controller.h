#ifndef GRAPH_CONTROLLER_H
#define GRAPH_CONTROLLER_H

#include <stddef.h>

#include <memory>
#include <vector>

#include "function.h"
#include "node.h"

class GraphController {
 public:
  GraphController();

  size_t AddScalarNode(double value);

  size_t AddRootNode();

  size_t AddXNode();

  size_t AddPlusNode();

  void ConnectNodes(size_t src_node, size_t dst_node, size_t slot);

  void DetachNode(size_t dst_node, size_t slot);

  double GetGraphResult();

  static const size_t kRootIndex = 0;

 private:
  std::vector<std::unique_ptr<Node<Function>>> nodes_;

  template <template <class> class NodeType, typename... Args>
  size_t AddNode(Args&&... args) {
    nodes_.emplace_back(new NodeType<Function>(std::forward<Args>(args)...));
    return nodes_.size() - 1;
  }
};

#endif  // GRAPH_CONTROLLER_H
