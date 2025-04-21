#include "output_connection_point.h"

OutputConnectionPoint::OutputConnectionPoint(size_t nodeId,
                                             QGraphicsRectItem *parent)
    : ConnectionPoint(nodeId, parent) {
  double x = parentItem()->boundingRect().right() - 2 * kRadius;
  double y = parentItem()->boundingRect().center().y() - kRadius;
  setRect(x, y, 2 * kRadius, 2 * kRadius);
}

void OutputConnectionPoint::updateHovered(const QPointF &mousePos,
                                          bool mousePressed,
                                          bool currentlyConnecting) {
  if (sceneBoundingRect().contains(mousePos)) {
    m_hovered = (!currentlyConnecting && !mousePressed &&
                 m_state == ConnectionState::FREE);
  } else {
    m_hovered = false;
  }
  update();
}

bool OutputConnectionPoint::acceptsDrop(const QPointF &) { return false; }

bool OutputConnectionPoint::canStartConnection(const QPointF &mousePos) {
  return sceneBoundingRect().contains(mousePos) &&
         m_state == ConnectionState::FREE;
}

bool OutputConnectionPoint::canCancelConnection(const QPointF &) {
  return false;
}

size_t OutputConnectionPoint::getSlot() const { return 0; }
