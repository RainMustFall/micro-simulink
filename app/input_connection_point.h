#ifndef INPUT_CONNECTION_POINT_H
#define INPUT_CONNECTION_POINT_H

#include "connection_point.h"

class InputConnectionPoint : public ConnectionPoint {
 public:
  InputConnectionPoint(size_t index, size_t totalPoints, size_t nodeId,
                       QGraphicsRectItem* parent = nullptr);

  void updateHovered(const QPointF& scenePos, bool mousePressed,
                     bool currentlyConnecting) override;

  bool acceptsDrop(const QPointF& scenePos) override;

  bool acceptsOutputPress(const QPointF&) override;

  bool acceptsInputPress(const QPointF& scenePos) override;

  size_t getSlot() const override;

 private:
  size_t m_index;
};

#endif  // INPUT_CONNECTION_POINT_H
