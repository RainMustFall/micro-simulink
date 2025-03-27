#ifndef NODE_DRAG_BUFFER_H
#define NODE_DRAG_BUFFER_H

#include <memory>

#include "visual_node.h"

class NodeDragBuffer {
 public:
  void setNode(std::unique_ptr<VisualNode>&& node);
  std::unique_ptr<VisualNode> releaseNode();

 private:
  std::unique_ptr<VisualNode> m_currentNode;
};

#endif  // NODE_DRAG_BUFFER_H
