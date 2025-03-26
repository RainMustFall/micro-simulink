#include "number_visual_node.h"

#include <QDebug>

NumberVisualNode::NumberVisualNode(GraphController *controller,
                                   QGraphicsItem *parent)
    : VisualNode(0, controller->AddScalarNode(0), parent),
      m_value(0),
      m_controller(controller) {
  m_textItem = new QGraphicsTextItem(QString::number(m_value), this);
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

    bool ok;
    double newValue = m_textItem->toPlainText().toDouble(&ok);
    if (ok) {
      m_value = newValue;

    } else {
      m_textItem->setPlainText(QString::number(m_value));
    }
  }

  return VisualNode::itemChange(change, value);
}
