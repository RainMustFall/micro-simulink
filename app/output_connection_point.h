#ifndef OUTPUT_CONNECTION_POINT_H
#define OUTPUT_CONNECTION_POINT_H

#include "connection_point.h"

class OutputConnectionPoint : public ConnectionPoint {
 public:
  OutputConnectionPoint(size_t nodeId, QGraphicsRectItem* parent = nullptr);

  void updateHovered(const QPointF& mousePos, bool mousePressed,
                     bool currentlyConnecting) override;

  bool acceptsDrop(const QPointF&) override;

  bool canStartConnection(const QPointF& mousePos) override;

  bool canCancelConnection(const QPointF&) override;

  size_t getSlot() const override;
};

#endif  // OUTPUT_CONNECTION_POINT_H
