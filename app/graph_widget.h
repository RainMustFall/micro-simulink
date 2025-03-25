#ifndef GRAPH_WIDGET_H
#define GRAPH_WIDGET_H

#include <QMimeData>
#include <QtCore/QPointF>
#include <QtCore/QRectF>
#include <QtCore/QString>
#include <QtCore/QVector>
#include <QtGui/QDrag>
#include <QtGui/QMouseEvent>
#include <QtGui/QPainter>
#include <QtWidgets/QGraphicsScene>
#include <QtWidgets/QGraphicsTextItem>
#include <QtWidgets/QGraphicsView>
#include <QtWidgets/QWidget>

#include "connection.h"
#include "connection_point.h"
#include "visual_node.h"
#include "number_visual_node.h"

class GraphWidget : public QGraphicsView {
 public:
  GraphWidget(QWidget *parent = nullptr);

 protected:
  void mousePressEvent(QMouseEvent *event) override;

  void mouseMoveEvent(QMouseEvent *event) override;

  void mouseReleaseEvent(QMouseEvent *event) override;

  void drawForeground(QPainter *painter, const QRectF &rect) override;

  void dragEnterEvent(QDragEnterEvent *event) override;

  void dragMoveEvent(QDragMoveEvent *event) override;

  void dropEvent(QDropEvent *event) override;

 private:
  QGraphicsScene m_scene;
  QVector<VisualNode *> m_nodes;
  QVector<Connection *> m_connections;

  ConnectionPoint *m_connectionSourcePoint = nullptr;
  QPointF m_currentMousePos;

  void freezeAllNodes();

  void unfreezeAllNodes();

  void detachAndStartConnecting(ConnectionPoint *destinationPoint,
                                const QPointF &scenePos);

  void startConnecting(ConnectionPoint *sourcePoint, const QPointF &scenePos);

  void makeConnection(ConnectionPoint *destinationPoint);

  Connection *removeConnectionByDestination(
      const ConnectionPoint *connectionPoint);
};

#endif  // GRAPH_WIDGET_H
