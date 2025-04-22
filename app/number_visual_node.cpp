#include "number_visual_node.h"

#include <QDebug>
#include <QGraphicsScene>
#include <QtGlobal>

#include "scalar_node.h"

NumberVisualNode::NumberVisualNode(GraphController *controller,
                                   QGraphicsItem *parent)
    : VisualNode(/* numberOfInputs=*/0, /* numberOfOutputs=*/1,
                 controller->AddNode<ScalarNode>(0),
                 QRect(0, 0, kHeight, kHeight), parent) {
  m_textItem =
      new EditableTextItem(/*initialValue=*/0, getId(), controller, this);
  m_textItem->setDefaultTextColor(pen().color());
}

bool NumberVisualNode::isGettingTextInput() const {
  return m_textItem->hasFocus();
}

void NumberVisualNode::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *) {
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
  double newWidth = qMax(m_textItem->boundingRect().width(), kHeight);
  auto newRect = rect();

  // Moving a bit right
  newRect.setX(rect().x() + rect().width() - newWidth);
  newRect.setWidth(newWidth);

  setRect(newRect);
}

void NumberVisualNode::updateTextPosition() {
  if (m_textItem) {
    updateRectWidth();
    qreal x = rect().x() + rect().width() / 2 -
              m_textItem->boundingRect().width() / 2;
    qreal y = rect().height() / 2 - m_textItem->boundingRect().height() / 2;
    m_textItem->setPos(x, y);
    m_textItem->setRotation(0);  // Ensure it remains horizontally aligned
  }
}

EditableTextItem::EditableTextItem(double initialValue, size_t nodeId,
                                   GraphController *controller,
                                   QGraphicsItem *parent)
    : QGraphicsTextItem(QString::number(initialValue), parent),
      m_controller(controller),
      m_value(initialValue),
      m_nodeId(nodeId) {}

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
    m_controller->SetScalarValue(m_nodeId, m_value);
  } else {
    setPlainText(QString::number(m_value));
  }
}
