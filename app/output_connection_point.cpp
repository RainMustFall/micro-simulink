#include "output_connection_point.h"

OutputConnectionPoint::OutputConnectionPoint(QGraphicsRectItem *parent)
    : ConnectionPoint(parent) {
  double x = parent->boundingRect().right() - 10;
  double y = parent->boundingRect().center().y() - 5;
  setRect(x, y, 10, 10);
}

void OutputConnectionPoint::updateHovered(const QPointF &scenePos,
                                          bool mousePressed,
                                          bool currentlyConnecting) {
  if (sceneBoundingRect().contains(scenePos)) {
    m_hovered = (!currentlyConnecting && !mousePressed &&
                 m_state == ConnectionState::FREE);
  } else {
    m_hovered = false;
  }
  update();
}

bool OutputConnectionPoint::acceptsDrop(const QPointF &) { return false; }

bool OutputConnectionPoint::acceptsOutputPress(const QPointF &scenePos) {
  return sceneBoundingRect().contains(scenePos) &&
         m_state == ConnectionState::FREE;
}

bool OutputConnectionPoint::acceptsInputPress(const QPointF &) { return false; }
