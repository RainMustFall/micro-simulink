#include "input_connection_point.h"

InputConnectionPoint::InputConnectionPoint(size_t index, size_t totalPoints,
                                           QGraphicsRectItem *parent)
    : ConnectionPoint(parent) {
  double distanceBetweenInputs =
      parent->boundingRect().height() / (totalPoints + 1);
  double x = parent->boundingRect().left();
  double y = parent->boundingRect().top() + distanceBetweenInputs * (index + 1);
  setRect(x, y, 10, 10);
}

void InputConnectionPoint::updateHovered(const QPointF &scenePos,
                                         bool mousePressed,
                                         bool currentlyConnecting) {
  if (sceneBoundingRect().contains(scenePos)) {
    m_hovered = ((currentlyConnecting && m_state == ConnectionState::FREE) ||
                 (!mousePressed && m_state == ConnectionState::CONNECTED));
  } else {
    m_hovered = false;
  }
  update();
}

bool InputConnectionPoint::acceptsDrop(const QPointF &scenePos) {
  return m_state == ConnectionState::FREE &&
         sceneBoundingRect().contains(scenePos);
}

bool InputConnectionPoint::acceptsOutputPress(const QPointF &) { return false; }

bool InputConnectionPoint::acceptsInputPress(const QPointF &scenePos) {
  return sceneBoundingRect().contains(scenePos) &&
         m_state == ConnectionState::CONNECTED;
}
