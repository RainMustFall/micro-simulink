#ifndef NODE_DRAG_BUFFER_H
#define NODE_DRAG_BUFFER_H

#include <memory>

#include "visual_node.h"

/*!
 * @brief Buffer which is used to pass a visual node from Palette to
 * GraphWidget, when user drags it with mouse
 *
 * Usually QMimeData is used to store the data that is being dragged. The
 * problem is that it supports only text data and is not very useful for the
 * hierarchy of nodes we have here.
 *
 * Instead of QMimeData, we have a small helper class that temporarily owns
 * the node that is being dragged. If drag succeeds, the ownership is
 * transferred to the GraphWidget. If not, it is discarded and destroyed as soon
 * as another drag starts.
 */
class NodeDragBuffer {
 public:
  /*!
   * @brief Put the node into the buffer
   *
   * The buffer takes over the node and caller cannot reuse this pointer
   * anymore.
   * @param node - Unique ptr to the node
   */
  void setNode(std::unique_ptr<VisualNode>&& node);

  /*!
   * @brief Extract the node from the buffer.
   *
   * Once called, it cannot be called again (unless another setNode is called).
   * Caller obtains the only poiner to the node.
   * @return the node
   */
  std::unique_ptr<VisualNode> releaseNode();

 private:
  std::unique_ptr<VisualNode> m_currentNode;
};

#endif  // NODE_DRAG_BUFFER_H
