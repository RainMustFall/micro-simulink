#ifndef BINARY_OPERATOR_H
#define BINARY_OPERATOR_H

#include <QPainter>

#include "graph_controller.h"
#include "visual_node.h"

class BinaryOperatorVisualNode : public VisualNode {
 protected:
  BinaryOperatorVisualNode(size_t nodeId, QString op, QGraphicsItem *parent);

  void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
             QWidget *widget = nullptr) override;

 private:
  QString m_operator;
  constexpr static double kHeight = 40.0;
};

class PlusVisualNode : public BinaryOperatorVisualNode {
 public:
  PlusVisualNode(GraphController *controller, QGraphicsItem *parent = nullptr);
};

#endif  // BINARY_OPERATOR_H
