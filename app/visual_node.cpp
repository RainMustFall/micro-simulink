#include "visual_node.h"

#include <QtWidgets/QGraphicsScene>

#include "input_connection_point.h"
#include "output_connection_point.h"

VisualNode::VisualNode(QGraphicsItem *parent)
    : QGraphicsRectItem(parent) {
  setFlag(ItemIsMovable);
  setFlag(ItemIsSelectable);
  setRect(-40, -20, 80, 40);
  setBrush(QBrush(Qt::white));
  setPen(QPen(Qt::black));

  m_connectionPoints = {
      std::make_shared<InputConnectionPoint>(0, 1, this),
      std::make_shared<OutputConnectionPoint>(this),
  };
}

ConnectionPoint *VisualNode::processHover(const QPointF &scenePos,
                                          bool mousePressed,
                                          bool currentlyConnecting) {
  for (const auto &connectionPoint : m_connectionPoints) {
    connectionPoint->updateHovered(scenePos, mousePressed, currentlyConnecting);
  }

  for (const auto &connectionPoint : m_connectionPoints) {
    if (connectionPoint->isHovered()) {
      return connectionPoint.get();
    }
  }
  return nullptr;
}

ConnectionPoint *VisualNode::processDrop(const QPointF &scenePos) {
  for (auto connectionPoint : m_connectionPoints) {
    if (connectionPoint->acceptsDrop(scenePos)) {
      return connectionPoint.get();
    }
  }
  return nullptr;
}

ConnectionPoint *VisualNode::processOutputPress(const QPointF &scenePos) {
  for (auto connectionPoint : m_connectionPoints) {
    if (connectionPoint->acceptsOutputPress(scenePos)) {
      return connectionPoint.get();
    }
  }
  return nullptr;
}

ConnectionPoint *VisualNode::processInputPress(const QPointF &scenePos) {
  for (auto connectionPoint : m_connectionPoints) {
    if (connectionPoint->acceptsInputPress(scenePos)) {
      return connectionPoint.get();
    }
  }
  return nullptr;
}

void VisualNode::mouseMoveEvent(QGraphicsSceneMouseEvent *event) {
  QGraphicsRectItem::mouseMoveEvent(event);
  // We want to repaint connections if the node is moved
  scene()->update();
}
