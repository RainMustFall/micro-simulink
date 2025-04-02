#include "connection.h"

Connection::Connection(ConnectionPoint *source, ConnectionPoint *dest,
                       QGraphicsItem *parent)
    : QGraphicsItem(parent), m_sourcePoint(source), m_destPoint(dest) {
  setZValue(-1);  // Draw connections behind nodes
}

QRectF Connection::boundingRect() const {
  if (!m_sourcePoint || !m_destPoint) return QRectF();
  QRectF sourceRect = m_sourcePoint->sceneBoundingRect();
  QRectF destRect = m_destPoint->sceneBoundingRect();
  return sourceRect.united(destRect);
}

void Connection::prepareForRemoval() { prepareGeometryChange(); }

void Connection::paint(QPainter *painter, const QStyleOptionGraphicsItem *,
                       QWidget *) {
  if (!m_sourcePoint || !m_destPoint) return;

  QPointF sourcePoint = m_sourcePoint->sceneBoundingRect().center();
  QPointF destPoint = m_destPoint->sceneBoundingRect().center();

  auto color =
      QApplication::palette().color(QPalette::Active, QPalette::WindowText);

  painter->setPen(QPen(color));
  painter->drawLine(sourcePoint, destPoint);

  // Draw arrowhead
  double angle = std::atan2(destPoint.y() - sourcePoint.y(),
                            destPoint.x() - sourcePoint.x());
  QPointF arrowHead1 = destPoint + QPointF(-10 * std::cos(angle - M_PI / 6),
                                           -10 * std::sin(angle - M_PI / 6));
  QPointF arrowHead2 = destPoint + QPointF(-10 * std::cos(angle + M_PI / 6),
                                           -10 * std::sin(angle + M_PI / 6));

  painter->drawPolygon(QPolygonF() << destPoint << arrowHead1 << arrowHead2);
}

ConnectionPoint *Connection::sourcePoint() { return m_sourcePoint; }

ConnectionPoint *Connection::destPoint() { return m_destPoint; }

Connection::~Connection() {
  prepareGeometryChange();
  scene()->removeItem(this);
}
