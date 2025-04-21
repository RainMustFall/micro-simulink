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

/*!
 * @brief A small circle on edge of a node used for connection
 *
 *  The connection point can be either input or output: it can be either on the
 * right or on the left.
 *
 *  Depending on this, it responds differently to user actions (hovering, mouse
 * clicks) and indicates whether it is ready for interaction. The exact behavior
 * is defined in the child classes
 */
class ConnectionPoint : public QGraphicsEllipseItem {
 public:
  /*!
   * @brief ConnectionPoint constructor
   * @param nodeId - ID of the graph node this point belongs to
   * @param parent - parent Graphics item
   */
  ConnectionPoint(size_t nodeId, QGraphicsRectItem* parent = nullptr);

  /*!
   * @brief React to mouse hover and update visual state
   *
   * Behavior is based on mouse position and what the user is
   * currently doing
   * @param scenePos - mouse position on the scene
   * @param mousePressed - whether the mouse is currently pressed
   * @param currentlyConnecting - whether the user is dragging a connection now
   */
  virtual void updateHovered(const QPointF& scenePos, bool mousePressed,
                             bool currentlyConnecting) = 0;

  /*!
   * @brief Whether point can form connection, if the mouse is released now
   *
   * It depends on whether mouse is close enough to the point, whether point is
   * already connected, whether this type of points reacts on such events at
   * all.
   * @param mousePos - mouse position on the scene
   * @return true of point can form a connection
   */
  virtual bool acceptsDrop(const QPointF& mousePos) = 0;

  /*!
   * @brief Whether point can cancel its current connection, if the mouse is
   * pressed now
   * @param mousePos - mouse position on the scene
   * @return true of point can cancel connection
   */
  virtual bool canCancelConnection(const QPointF& mousePos) = 0;

  /*!
   * @brief Whether point can start connection, if the mouse is pressed now
   * @param mousePos - mouse position on the scene
   * @return true of point can start connection
   */
  virtual bool canStartConnection(const QPointF& mousePos) = 0;

  /*!
   * @brief Get index of node slot which this point represents
   *
   * Slots for input and output nodes are counted independently
   * @return index of the slot
   */
  virtual size_t getSlot() const = 0;

  /*!
   * @brief Get ID of the node this point belongs to
   * @return Node ID
   */
  size_t getNodeId() const;

  /*!
   * @brief Change the state to connecting
   */
  void startConnection();

  /*!
   * @brief Change the state to connected
   */
  void connect();

  /*!
   * @brief Change the state to free
   */
  void disconnect();

  /*!
   * @brief Whether the point is currently highlighted after mouse hovering
   * @return true if the point is currently highlighted
   */
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

  constexpr static double kRadius = 5;
};
#endif  // CONNECTION_POINT_H
