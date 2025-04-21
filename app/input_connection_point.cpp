#include "input_connection_point.h"

InputConnectionPoint::InputConnectionPoint(size_t index, size_t totalPoints,
                                           size_t nodeId,
                                           QGraphicsRectItem *parent)
    : ConnectionPoint(nodeId, parent), m_index{index} {
  double distanceBetweenInputs =
      parentItem()->boundingRect().height() / (totalPoints + 1);
  double x = parentItem()->boundingRect().left();
  double y = parentItem()->boundingRect().top() +
             distanceBetweenInputs * (m_index + 1);
  setRect(x, y - kRadius, 2 * kRadius, 2 * kRadius);
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

bool InputConnectionPoint::canStartConnection(const QPointF &) { return false; }

bool InputConnectionPoint::canCancelConnection(const QPointF &scenePos) {
  return sceneBoundingRect().contains(scenePos) &&
         m_state == ConnectionState::CONNECTED;
}

size_t InputConnectionPoint::getSlot() const { return m_index; }
