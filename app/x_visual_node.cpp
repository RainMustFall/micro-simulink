#include "x_visual_node.h"

XVisualNode::XVisualNode(GraphController *controller, QGraphicsItem *parent)
    : VisualNode(/* numInputs=*/0, controller->AddXNode(),
                 QRect(0, 0, kHeight, kHeight), parent) {}

void XVisualNode::paint(QPainter *painter,
                        const QStyleOptionGraphicsItem *option,
                        QWidget *widget) {
  VisualNode::paint(painter, option, widget);
  painter->drawText(rect(), Qt::AlignCenter | Qt::AlignHCenter, "x");
}
