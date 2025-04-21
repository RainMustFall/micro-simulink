#ifndef INPUT_CONNECTION_POINT_H
#define INPUT_CONNECTION_POINT_H

#include "connection_point.h"

/*!
 * @brief A small circle on the left edge of a node
 *
 *  It accepts connections which start at another node of the graph, also
 * allowing to detach the current connection by mouse click
 */
class InputConnectionPoint : public ConnectionPoint {
 public:
  /*!
   * @brief InputConnectionPoint constructor
   * @param index - the number of this point among all the points of its nodes
   * (starting from zero)
   * @param totalPoints - total number of inputs that the node has
   * @param nodeId - ID of the node this point belongs to
   * @param parent - parent Graphics item
   */
  InputConnectionPoint(size_t index, size_t totalPoints, size_t nodeId,
                       QGraphicsRectItem* parent = nullptr);

  void updateHovered(const QPointF& mousePos, bool mousePressed,
                     bool currentlyConnecting) override;

  bool acceptsDrop(const QPointF& mousePos) override;

  bool canStartConnection(const QPointF&) override;

  bool canCancelConnection(const QPointF& mousePos) override;

  size_t getSlot() const override;

 private:
  size_t m_index;
};

#endif  // INPUT_CONNECTION_POINT_H
