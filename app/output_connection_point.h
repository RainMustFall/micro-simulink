#ifndef OUTPUT_CONNECTION_POINT_H
#define OUTPUT_CONNECTION_POINT_H

#include "connection_point.h"

/*!
 * @brief A small circle on the right edge of a node
 *
 *  It allowes to start new connections on mouse click
 */
class OutputConnectionPoint : public ConnectionPoint {
 public:
  /*!
   * @brief OutputConnectionPoint constructor
   * @param nodeId - ID of the node this point belongs to
   * @param parent - parent Graphics item
   */
  OutputConnectionPoint(size_t nodeId, QGraphicsRectItem* parent = nullptr);

  void updateHovered(const QPointF& mousePos, bool mousePressed,
                     bool currentlyConnecting) override;

  bool acceptsDrop(const QPointF&) override;

  bool canStartConnection(const QPointF& mousePos) override;

  bool canCancelConnection(const QPointF&) override;

  size_t getSlot() const override;
};

#endif  // OUTPUT_CONNECTION_POINT_H
