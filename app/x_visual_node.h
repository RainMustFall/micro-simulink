#ifndef X_VISUAL_NODE_H
#define X_VISUAL_NODE_H

#include <QPainter>

#include "graph_controller.h"
#include "text_visual_node.h"

/*!
 * @brief Visual node corresponding to "X"
 */
class XVisualNode : public TextVisualNode {
 public:
  /*!
   * @brief XVisualNode
   * @param controller - GraphController used to interact with the graph
   * @param parent - parent graphics item
   */
  explicit XVisualNode(GraphController *controller,
                       QGraphicsItem *parent = nullptr);

 private:
  constexpr static double kHeight = 40.0;
};

#endif  // X_VISUAL_NODE_H
