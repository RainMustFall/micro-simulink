#ifndef CONNECTION_POINT_H
#define CONNECTION_POINT_H

#include <QtCore/QPointF>
#include <QtCore/QRectF>
#include <QtCore/QString>
#include <QtCore/QVector>
#include <QtGui/QPainter>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGraphicsItem>
#include <QtWidgets/QGraphicsRectItem>
#include <QtWidgets/QWidget>
#include <cmath>

class ConnectionPoint : public QGraphicsEllipseItem {
 public:
  ConnectionPoint(size_t nodeId, QGraphicsRectItem* parent = nullptr);

  virtual void updateHovered(const QPointF& scenePos, bool mousePressed,
                             bool currentlyConnecting) = 0;

  virtual bool acceptsDrop(const QPointF& scenePos) = 0;

  virtual bool acceptsInputPress(const QPointF& scenePos) = 0;

  virtual bool acceptsOutputPress(const QPointF& scenePos) = 0;

  virtual size_t getSlot() const = 0;

  size_t getNodeId() const;

  void startConnection();

  void connect();

  void disconnect();

  bool isHovered() const;

 protected:
  void paint(QPainter* painter, const QStyleOptionGraphicsItem* option,
             QWidget* widget = nullptr) override;

  bool m_hovered = false;

  enum class ConnectionState {
    FREE = 0,
    CONNECTING = 1,
    CONNECTED = 2,
  };

  ConnectionState m_state = ConnectionState::FREE;

  size_t m_nodeId;
};
#endif  // CONNECTION_POINT_H
