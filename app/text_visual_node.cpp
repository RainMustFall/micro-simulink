#include "text_visual_node.h"

TextVisualNode::TextVisualNode(size_t numberOfInputs, size_t numberOfOutputs,
                               size_t id, const QRect &rect, QString text,
                               QGraphicsItem *parent)
    : VisualNode(numberOfInputs, numberOfOutputs, id, rect, parent),
      m_text(std::move(text)) {}

void TextVisualNode::paint(QPainter *painter,
                           const QStyleOptionGraphicsItem *option,
                           QWidget *widget) {
  VisualNode::paint(painter, option, widget);
  painter->drawText(rect(), Qt::AlignCenter | Qt::AlignHCenter, m_text);
}
