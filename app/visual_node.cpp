#include "visual_node.h"

#include <QtWidgets/QGraphicsScene>

#include "input_connection_point.h"
#include "output_connection_point.h"

VisualNode::VisualNode(size_t numberOfInputs, size_t numberOfOutputs, size_t id,
                       const QRect &rect, QGraphicsItem *parent)
    : QGraphicsRectItem(rect, parent), m_id{id} {
  setFlag(ItemIsMovable);
  setFlag(ItemIsSelectable);

  auto penColor =
      QApplication::palette().color(QPalette::Active, QPalette::WindowText);

  auto fillColor = QApplication::palette()
                       .color(QPalette::Active, QPalette::Button)
                       .lighter();

  setBrush(QBrush(fillColor));
  setPen(QPen(penColor));

  m_connectionPoints.reserve(numberOfInputs + numberOfOutputs);

  for (size_t i = 0; i < numberOfInputs; ++i) {
    m_connectionPoints.push_back(
        std::make_shared<InputConnectionPoint>(i, numberOfInputs, id, this));
  }

  for (size_t i = 0; i < numberOfOutputs; ++i) {
    m_connectionPoints.push_back(
        std::make_shared<OutputConnectionPoint>(id, this));
  }
}

size_t VisualNode::getId() const { return m_id; }

ConnectionPoint *VisualNode::processHover(const QPointF &mousePos,
                                          bool mousePressed,
                                          bool currentlyConnecting) {
  for (const auto &connectionPoint : m_connectionPoints) {
    connectionPoint->updateHovered(mousePos, mousePressed, currentlyConnecting);
  }

  for (const auto &connectionPoint : m_connectionPoints) {
    if (connectionPoint->isHovered()) {
      return connectionPoint.get();
    }
  }
  return nullptr;
}

ConnectionPoint *VisualNode::processDrop(const QPointF &mousePos) {
  for (auto connectionPoint : m_connectionPoints) {
    if (connectionPoint->acceptsDrop(mousePos)) {
      return connectionPoint.get();
    }
  }
  return nullptr;
}

ConnectionPoint *VisualNode::processOutputPress(const QPointF &mousePos) {
  for (auto connectionPoint : m_connectionPoints) {
    if (connectionPoint->acceptsOutputPress(mousePos)) {
      return connectionPoint.get();
    }
  }
  return nullptr;
}

ConnectionPoint *VisualNode::processInputPress(const QPointF &mousePos) {
  for (auto connectionPoint : m_connectionPoints) {
    if (connectionPoint->acceptsInputPress(mousePos)) {
      return connectionPoint.get();
    }
  }
  return nullptr;
}

bool VisualNode::isConnected(const Connection &connection) const {
  for (auto connectionPoint : m_connectionPoints) {
    if (connection.sourcePoint() == connectionPoint.get() ||
        connection.destPoint() == connectionPoint.get()) {
      return true;
    }
  }

  return false;
}

bool VisualNode::isDeletable() const { return true; }

void VisualNode::mouseMoveEvent(QGraphicsSceneMouseEvent *event) {
  QGraphicsRectItem::mouseMoveEvent(event);
  // We want to repaint connections if the node is moved
  scene()->update();
}

bool VisualNode::isGettingTextInput() const { return false; }
