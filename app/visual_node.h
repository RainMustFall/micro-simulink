#ifndef VISUAL_NODE_H
#define VISUAL_NODE_H

#include "connection_point.h"

class VisualNode : public QGraphicsRectItem {
 public:
  VisualNode(size_t numberOfInputs, size_t id, QGraphicsItem* parent = nullptr);

  size_t getId() const;

  ConnectionPoint* processHover(const QPointF& scenePos, bool mousePressed,
                                bool currentlyConnecting);

  ConnectionPoint* processDrop(const QPointF& scenePos);

  ConnectionPoint* processOutputPress(const QPointF& scenePos);

  ConnectionPoint* processInputPress(const QPointF& scenePos);

  virtual void mouseMoveEvent(QGraphicsSceneMouseEvent* event) override;

 private:
  std::vector<std::shared_ptr<ConnectionPoint>> m_connectionPoints;

  size_t m_id;
};

#endif  // VISUAL_NODE_H
