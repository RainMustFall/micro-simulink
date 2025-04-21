#ifndef BINARY_OPERATOR_H
#define BINARY_OPERATOR_H

#include <QPainter>

#include "graph_controller.h"
#include "text_visual_node.h"

/*!
 * @brief A visual node representing a binary operator.
 *
 * It has two inputs, one output, and is rendered with a square
 * with a single symbol on it (+, -, /, ...)
 */
class BinaryOperatorVisualNode : public TextVisualNode {
 protected:
  /*!
   * @brief Constructor
   * @param nodeId - id of the graph node to interact with controller
   * @param op - an operation symbol to display (e.g., +)
   * @param parent - parent QGraphicsItem
   */
  BinaryOperatorVisualNode(size_t nodeId, QString op, QGraphicsItem *parent);

 private:
  constexpr static double kHeight = 40.0;
};

/*!
 * @brief A visual node representing + operator.
 */
class PlusVisualNode : public BinaryOperatorVisualNode {
 public:
  /*!
   * @brief Constructor
   * @param controller - GraphController used to interact with the graph
   * @param parent - QGraphicsItem
   */
  PlusVisualNode(GraphController *controller, QGraphicsItem *parent = nullptr);
};

#endif  // BINARY_OPERATOR_H
