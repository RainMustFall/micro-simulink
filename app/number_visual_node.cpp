#include "number_visual_node.h"

#include <QDebug>

NumberVisualNode::NumberVisualNode(QGraphicsItem *parent) : VisualNode(parent) {
  m_textItem = new QGraphicsTextItem("5", this);
  m_textItem->setPos(-m_textItem->boundingRect().width() / 2,
                     -m_textItem->boundingRect().height() / 2);
  m_textItem->setDefaultTextColor(Qt::black);
}

void NumberVisualNode::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event) {
  m_textItem->setTextInteractionFlags(Qt::TextEditorInteraction);
  m_textItem->setFocus();
}

QVariant NumberVisualNode::itemChange(GraphicsItemChange change,
                                      const QVariant &value) {
  if (change == ItemSelectedChange) {
    m_textItem->setTextInteractionFlags(Qt::NoTextInteraction);
  }
  return VisualNode::itemChange(change, value);
}
