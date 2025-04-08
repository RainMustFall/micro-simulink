#include "binary_operator.h"

BinaryOperatorVisualNode::BinaryOperatorVisualNode(size_t nodeId, QString op,
                                                   QGraphicsItem *parent)
    : VisualNode(/* numInputs=*/2, nodeId, QRect(0, 0, kHeight, kHeight),
                 parent),
      m_operator(std::move(op)) {}

void BinaryOperatorVisualNode::paint(QPainter *painter,
                                     const QStyleOptionGraphicsItem *option,
                                     QWidget *widget) {
  VisualNode::paint(painter, option, widget);
  painter->drawText(rect(), Qt::AlignCenter | Qt::AlignHCenter, m_operator);
}

PlusVisualNode::PlusVisualNode(GraphController *controller,
                               QGraphicsItem *parent)
    : BinaryOperatorVisualNode(controller->AddPlusNode(), "+", parent) {}
