#ifndef TRIGONOMETRY_VISUAL_NODES_H
#define TRIGONOMETRY_VISUAL_NODES_H

#include "graph_controller.h"
#include "text_visual_node.h"

/*!
 * @brief Visual node corresponding to sinus
 */
class SineVisualNode : public TextVisualNode {
 public:
  /*!
   * @brief SineVisualNode
   * @param controller - GraphController used to interact with the graph
   * @param parent - parent graphics item
   */
  explicit SineVisualNode(GraphController *controller,
                          QGraphicsItem *parent = nullptr);
};

/*!
 * @brief Visual node corresponding to cosinus
 */
class CosineVisualNode : public TextVisualNode {
 public:
  /*!
   * @brief CosineVisualNode
   * @param controller - GraphController used to interact with the graph
   * @param parent - parent graphics item
   */
  explicit CosineVisualNode(GraphController *controller,
                            QGraphicsItem *parent = nullptr);
};

/*!
 * @brief Visual node corresponding to tangent
 */
class TangentVisualNode : public TextVisualNode {
 public:
  /*!
   * @brief TangentVisualNode
   * @param controller - GraphController used to interact with the graph
   * @param parent - parent graphics item
   */
  explicit TangentVisualNode(GraphController *controller,
                             QGraphicsItem *parent = nullptr);
};

/*!
 * @brief Visual node corresponding to cotangent
 */
class CotangentVisualNode : public TextVisualNode {
 public:
  /*!
   * @brief CotangentVisualNode
   * @param controller - GraphController used to interact with the graph
   * @param parent - parent graphics item
   */
  explicit CotangentVisualNode(GraphController *controller,
                               QGraphicsItem *parent = nullptr);
};

#endif  // TRIGONOMETRY_VISUAL_NODES_H
