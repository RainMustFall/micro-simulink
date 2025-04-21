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

/*!
 * @brief Graphics item responsible for displaying the vertex on the screen.
 *
 * It reacts to moves, mouse events (hovering, clicking to create or delete a
 * connection). Cannot be created on its own and should be inherited by concrete
 * nodes.
 */
class VisualNode : public QGraphicsRectItem {
 public:
  /*!
   * @brief VisualNode
   * @param numberOfInputs - number of inputs the node accepts
   * @param numberOfOutputs - number of outputs of the node
   * @param id - ID of the node this visual node corresponds to (assigned by
   * controller when creating a node).
   * @param rect - rectangle describing the shape of the node
   * @param parent - parent graphics item
   */
  VisualNode(size_t numberOfInputs, size_t numberOfOutputs, size_t id,
             const QRect& rect, QGraphicsItem* parent);

  /*!
   * @brief Get ID of the node this visual node corresponds to
   * @return Node ID
   */
  size_t getId() const;

  /*!
   * @brief Highligh a connection point based on the mouse position and what the
   * user is currently doing
   * @param scenePos - mouse position on the scene
   * @param mousePressed - whether the mouse is currently pressed
   * @param currentlyConnecting - whether the user is dragging a connection now
   * @return Pointer to the connection point highlighted (or nullptr if no
   * connection points were triggered)
   */
  ConnectionPoint* processHover(const QPointF& mousePos, bool mousePressed,
                                bool currentlyConnecting);

  /*!
   * @brief Process mouse release with connection being created.
   * @param mousePos - mouse position on the scene when it was released
   * @return ConnectionPoint that was able to form a connection or nullptr if no
   * such point found.
   */
  ConnectionPoint* processDrop(const QPointF& mousePos);

  /*!
   * @brief Process mouse click trying to start a connection
   * @param mousePos - mouse position on the scene when it was clicked
   * @return ConnectionPoint which was clicked and from which the connection can
   * start.
   */
  ConnectionPoint* tryStartConnection(const QPointF& mousePos);

  /*!
   * @brief Process mouse click trying to cancel an existing connection
   * @param mousePos - mouse position on the scene when it was clicked
   * @return ConnectionPoint which was clicked and which is bound by a
   * connection that can be cancelled.
   */
  ConnectionPoint* tryCancelConnection(const QPointF& mousePos);

  /*!
   * @brief Whether the node is bound by this connection.
   * @param connection
   * @return true if the node belongs to this connection.
   */
  bool isConnected(const Connection& connection) const;

  /*!
   * @brief Whether the node should be deleted if it's selected and Delete is
   * pressed
   *
   * Some nodes (root) should never be deleted even if the user tries to do so.
   * @return true if the node can be deleted
   */
  virtual bool isDeletable() const;

  /*!
   * @brief If the user is currently entering any text to it
   *
   * If yes, Delete press should be forwarded to text input, not used to delete
   * the nodes from the working area.
   * @return true if the user is currently entering any text to this node.
   */
  virtual bool isGettingTextInput() const;

 protected:
  virtual void mouseMoveEvent(QGraphicsSceneMouseEvent* event) override;

 private:
  std::vector<std::shared_ptr<ConnectionPoint>> m_connectionPoints;

  size_t m_id;
};

#endif  // VISUAL_NODE_H
