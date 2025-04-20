#ifndef BINARY_OPERATOR_H
#define BINARY_OPERATOR_H

#include <QPainter>

#include "graph_controller.h"
#include "text_visual_node.h"

class BinaryOperatorVisualNode : public TextVisualNode {
 protected:
  BinaryOperatorVisualNode(size_t nodeId, QString op, QGraphicsItem *parent);

 private:
  constexpr static double kHeight = 40.0;
};

class PlusVisualNode : public BinaryOperatorVisualNode {
 public:
  PlusVisualNode(GraphController *controller, QGraphicsItem *parent = nullptr);
};

#endif  // BINARY_OPERATOR_H
