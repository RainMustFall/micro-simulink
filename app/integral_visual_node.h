#ifndef INTEGRAL_VISUAL_NODE_H
#define INTEGRAL_VISUAL_NODE_H

#include <QPainter>

#include "number_visual_node.h"
#include "visual_node.h"

class IntegralVisualNode : public VisualNode {
 public:
  explicit IntegralVisualNode(GraphController *controller,
                              QGraphicsItem *parent = nullptr);

 protected:
  void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
             QWidget *widget = nullptr) override;

 protected:
  void mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event) override;

 private:
  double upperLimit;
  double lowerLimit;

  constexpr static double kHeight = 70.0;
};

#endif  // INTEGRAL_VISUAL_NODE_H
