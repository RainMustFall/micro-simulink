#ifndef ALGEBRAIC_VISUAL_NODES_H
#define ALGEBRAIC_VISUAL_NODES_H

#include "graph_controller.h"
#include "text_visual_node.h"

/*!
 * @brief Visual node corresponding to logarithm
 */
class LogVisualNode : public TextVisualNode {
 public:
  /*!
   * @brief LogVisualNode
   * @param controller - GraphController used to interact with the graph
   * @param parent - parent graphics item
   */
  explicit LogVisualNode(GraphController *controller,
                         QGraphicsItem *parent = nullptr);
};

/*!
 * @brief Visual node corresponding to exponent
 */
class ExpVisualNode : public TextVisualNode {
 public:
  /*!
   * @brief ExpVisualNode
   * @param controller - GraphController used to interact with the graph
   * @param parent - parent graphics item
   */
  explicit ExpVisualNode(GraphController *controller,
                         QGraphicsItem *parent = nullptr);
};

/*!
 * @brief Visual node corresponding to square root
 */
class SqrtVisualNode : public TextVisualNode {
 public:
  /*!
   * @brief SqrtVisualNode
   * @param controller - GraphController used to interact with the graph
   * @param parent - parent graphics item
   */
  explicit SqrtVisualNode(GraphController *controller,
                          QGraphicsItem *parent = nullptr);
};

#endif  // ALGEBRAIC_VISUAL_NODES_H
