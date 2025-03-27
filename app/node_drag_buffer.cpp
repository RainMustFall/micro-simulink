#include "node_drag_buffer.h"

void NodeDragBuffer::setNode(std::unique_ptr<VisualNode> &&node) {
  m_currentNode = std::move(node);
}

std::unique_ptr<VisualNode> NodeDragBuffer::releaseNode() {
  return std::move(m_currentNode);
}
