#include "number_visual_node.h"

#include <QDebug>
#include <QGraphicsScene>
#include <QtGlobal>

NumberVisualNode::NumberVisualNode(GraphController *controller,
                                   QGraphicsItem *parent)
    : VisualNode(/* numInputs=*/0, controller->AddScalarNode(0),
                 QRect(0, 0, 40, 40), parent) {
  m_textItem = new EditableTextItem(/*initialValue=*/0, controller, this);
  m_textItem->setDefaultTextColor(pen().color());
}

void NumberVisualNode::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event) {
  m_textItem->setTextInteractionFlags(Qt::TextEditorInteraction);
  m_textItem->setFocus();
  QTextCursor cursor = m_textItem->textCursor();
  cursor.select(QTextCursor::Document);
  m_textItem->setTextCursor(cursor);
}

void NumberVisualNode::paint(QPainter *painter,
                             const QStyleOptionGraphicsItem *option,
                             QWidget *widget) {
  updateTextPosition();
  QGraphicsRectItem::paint(painter, option, widget);
}

void NumberVisualNode::updateRectWidth() {
  double newWidth = qMax(m_textItem->boundingRect().width(), 40.0);
  auto newRect = rect();

  // Moving a bit right
  newRect.setX(rect().x() + rect().width() - newWidth);
  newRect.setWidth(newWidth);

  updateRect(newRect);
}

void NumberVisualNode::updateTextPosition() {
  if (m_textItem) {
    updateRectWidth();
    qreal x = rect().x() + rect().width() / 2 - m_textItem->boundingRect().width() / 2;
    qreal y = rect().height() / 2 - m_textItem->boundingRect().height() / 2;
    m_textItem->setPos(x, y);
    m_textItem->setRotation(0);  // Ensure it remains horizontally aligned
  }
}

EditableTextItem::EditableTextItem(double initialValue,
                                   GraphController *controller,
                                   QGraphicsItem *parent)
    : QGraphicsTextItem(QString::number(initialValue), parent),
      m_controller(controller),
      m_value(initialValue) {}

void EditableTextItem::keyPressEvent(QKeyEvent *event) {
  if (event->key() == Qt::Key_Return || event->key() == Qt::Key_Enter) {
    clearFocus();  // Lose focus when Enter is pressed
    saveEnteredValue();
  } else {
    QGraphicsTextItem::keyPressEvent(event);
  }
}

void EditableTextItem::focusOutEvent(QFocusEvent *event) {
  saveEnteredValue();
  QGraphicsTextItem::focusOutEvent(event);
}

void EditableTextItem::saveEnteredValue() {
  setTextInteractionFlags(Qt::NoTextInteraction);

  bool ok;
  double newValue = toPlainText().replace(',', '.').toDouble(&ok);
  if (ok) {
    m_value = newValue;

  } else {
    setPlainText(QString::number(m_value));
  }
}
