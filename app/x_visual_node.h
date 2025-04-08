#ifndef X_VISUAL_NODE_H
#define X_VISUAL_NODE_H

#include <QPainter>

#include "graph_controller.h"
#include "visual_node.h"

class XVisualNode : public VisualNode {
 public:
  explicit XVisualNode(GraphController *controller,
                       QGraphicsItem *parent = nullptr);

 protected:
  void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
             QWidget *widget = nullptr) override;

  constexpr static double kHeight = 40.0;
};

#endif  // X_VISUAL_NODE_H
