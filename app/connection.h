#ifndef CONNECTION_H
#define CONNECTION_H

#include <QtWidgets/QGraphicsScene>

#include "connection_point.h"

class Connection : public QGraphicsItem {
 public:
  Connection(ConnectionPoint *source, ConnectionPoint *dest,
             QGraphicsItem *parent = nullptr);

  QRectF boundingRect() const override;

  void prepareForRemoval();

  void paint(QPainter *painter, const QStyleOptionGraphicsItem *,
             QWidget *) override;

  ConnectionPoint *sourcePoint();
  ;

  ConnectionPoint *destPoint();

  ~Connection() override;

 private:
  ConnectionPoint *m_sourcePoint;
  ConnectionPoint *m_destPoint;
};

#endif  // CONNECTION_H
