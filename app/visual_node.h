#ifndef VISUAL_NODE_H
#define VISUAL_NODE_H

#include <QDialog>
#include <QDialogButtonBox>
#include <QFont>
#include <QFormLayout>
#include <QGraphicsRectItem>
#include <QGraphicsSceneMouseEvent>
#include <QInputDialog>
#include <QLineEdit>

#include "connection.h"
#include "connection_point.h"

class VisualNode : public QGraphicsRectItem {
 public:
  VisualNode(size_t numberOfInputs, size_t numberOfOutputs, size_t id, const QRect& rect,
             QGraphicsItem* parent);

  size_t getId() const;

  ConnectionPoint* processHover(const QPointF& scenePos, bool mousePressed,
                                bool currentlyConnecting);

  ConnectionPoint* processDrop(const QPointF& scenePos);

  ConnectionPoint* processOutputPress(const QPointF& scenePos);

  ConnectionPoint* processInputPress(const QPointF& scenePos);

  bool isConnected(const Connection& connection) const;

  virtual bool isDeletable() const;

  virtual void mouseMoveEvent(QGraphicsSceneMouseEvent* event) override;

  virtual bool isGettingTextInput() const;

 private:
  std::vector<std::shared_ptr<ConnectionPoint>> m_connectionPoints;

  size_t m_id;
};

#endif  // VISUAL_NODE_H
