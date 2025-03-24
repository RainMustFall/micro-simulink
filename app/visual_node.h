#ifndef VISUAL_NODE_H
#define VISUAL_NODE_H

#include "connection_point.h"

class VisualNode : public QGraphicsRectItem {
 public:
  VisualNode(const QString& label, QGraphicsItem* parent = nullptr);

  QString label() const;

  ConnectionPoint* processHover(const QPointF& scenePos, bool mousePressed,
                                bool currentlyConnecting);

  ConnectionPoint* processDrop(const QPointF& scenePos);

  ConnectionPoint* processOutputPress(const QPointF& scenePos);

  ConnectionPoint* processInputPress(const QPointF& scenePos);

  virtual void mouseMoveEvent(QGraphicsSceneMouseEvent* event) override;

 private:
  QString m_label;
  QGraphicsTextItem* m_textItem;
  std::vector<std::shared_ptr<ConnectionPoint>> m_connectionPoints;
};

#endif  // VISUAL_NODE_H
