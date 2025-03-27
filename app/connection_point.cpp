#include "connection_point.h"

ConnectionPoint::ConnectionPoint(size_t nodeId, QGraphicsRectItem *parent)
    : QGraphicsEllipseItem(parent), m_nodeId(nodeId) {
  setBrush(QBrush(Qt::blue));
  setPen(QPen(Qt::blue));
}

size_t ConnectionPoint::getNodeId() const { return m_nodeId; }

void ConnectionPoint::startConnection() {
  m_state = ConnectionState::CONNECTING;
}

void ConnectionPoint::connect() { m_state = ConnectionState::CONNECTED; }

void ConnectionPoint::disconnect() { m_state = ConnectionState::FREE; }

bool ConnectionPoint::isHovered() const { return m_hovered; }

void ConnectionPoint::paint(QPainter *painter,
                            const QStyleOptionGraphicsItem *option,
                            QWidget *widget) {
  if (m_hovered) {
    QGraphicsEllipseItem::paint(painter, option, widget);
  }
}
