#include "graph_widget.h"

#include <QGraphicsProxyWidget>
#include <algorithm>

#include "number_visual_node.h"
#include "root_visual_node.h"

GraphWidget::GraphWidget(GraphController *controller,
                         NodeDragBuffer *dragBuffer, QWidget *parent)
    : QGraphicsView(parent),
      m_controller(controller),
      m_dragBuffer(dragBuffer) {
  setScene(&m_scene);
  setRenderHint(QPainter::Antialiasing);
  setDragMode(RubberBandDrag);
  setAcceptDrops(true);
  setMouseTracking(true);
  // https://stackoverflow.com/questions/38458830
  m_scene.setItemIndexMethod(QGraphicsScene::ItemIndexMethod::NoIndex);

  // Add root node
  VisualNode *root = new RootVisualNode(controller);
  root->setPos(-200, 0);
  m_scene.addItem(root);
  m_nodes.append(root);
}

void GraphWidget::detachAndStartConnecting(ConnectionPoint *destinationPoint,
                                           const QPointF &scenePos) {
  auto connection = removeConnectionByDestination(destinationPoint);

  m_currentMousePos = scenePos;
  m_connectionSourcePoint = connection->sourcePoint();

  freezeAllNodes();
  delete connection;

  destinationPoint->disconnect();
  m_connectionSourcePoint->startConnection();
}

void GraphWidget::startConnecting(ConnectionPoint *sourcePoint,
                                  const QPointF &scenePos) {
  m_currentMousePos = scenePos;
  m_connectionSourcePoint = sourcePoint;
  m_connectionSourcePoint->startConnection();
  freezeAllNodes();
}

void GraphWidget::mousePressEvent(QMouseEvent *event) {
  QGraphicsView::mousePressEvent(event);
  if (event->button() == Qt::LeftButton) {
    QPointF scenePos = mapToScene(event->pos());
    for (VisualNode *node : m_nodes) {
      auto sourcePoint = node->tryStartConnection(scenePos);
      if (sourcePoint != nullptr) {
        startConnecting(sourcePoint, scenePos);
        return;
      }

      auto destinationPoint = node->tryCancelConnection(scenePos);
      if (destinationPoint != nullptr) {
        m_controller->DetachNode(node->getId(), destinationPoint->getSlot());
        detachAndStartConnecting(destinationPoint, scenePos);
        return;
      }
    }
  }
}

void GraphWidget::mouseMoveEvent(QMouseEvent *event) {
  QGraphicsView::mouseMoveEvent(event);
  QPointF scenePos = mapToScene(event->pos());
  bool currentlyConnecting = m_connectionSourcePoint != nullptr;

  // Handle node hovering for connection point
  ConnectionPoint *activated = nullptr;
  for (VisualNode *node : m_nodes) {
    activated = node->processHover(scenePos, event->buttons() != Qt::NoButton,
                                   currentlyConnecting);
    if (activated != nullptr) {
      break;
    }
  }

  // Draw temporary connection line
  if (currentlyConnecting) {
    if (activated != nullptr) {
      // "Stick" to the currently activated point
      m_currentMousePos = activated->sceneBoundingRect().center();
    } else {
      m_currentMousePos = scenePos;
    }

    viewport()->update();  // Trigger repaint
  }
}

void GraphWidget::keyPressEvent(QKeyEvent *event) {
  QGraphicsView::keyPressEvent(event);
  bool anyNodeHasFocus = false;
  for (auto *node : m_nodes) {
    anyNodeHasFocus |= node->isGettingTextInput();
  }

  if (!anyNodeHasFocus && event->key() == Qt::Key_Delete) {
    deleteConnectionsWithSelectedNodes();
    deleteSelectedNodes();
  }
}

void GraphWidget::makeConnection(ConnectionPoint *destinationPoint) {
  destinationPoint->connect();
  m_connectionSourcePoint->connect();

  Connection *connection =
      new Connection(m_connectionSourcePoint, destinationPoint);
  m_scene.addItem(connection);
  m_connections.append(connection);
}

void GraphWidget::mouseReleaseEvent(QMouseEvent *event) {
  QGraphicsView::mouseReleaseEvent(event);
  if (event->button() != Qt::LeftButton || m_connectionSourcePoint == nullptr) {
    return;
  }

  QPointF scenePos = mapToScene(event->pos());
  bool connectionHappened = false;

  for (VisualNode *node : m_nodes) {
    auto destinationPoint = node->processDrop(scenePos);
    if (destinationPoint != nullptr) {
      m_controller->ConnectNodes(m_connectionSourcePoint->getNodeId(),
                                 destinationPoint->getNodeId(),
                                 destinationPoint->getSlot());
      makeConnection(destinationPoint);
      connectionHappened = true;
      break;
    }
  }

  if (!connectionHappened) {
    m_connectionSourcePoint->disconnect();
  }

  m_connectionSourcePoint = nullptr;
  unfreezeAllNodes();
  viewport()->update();  // Ensure temporary line is removed
}

void GraphWidget::drawForeground(QPainter *painter, const QRectF &rect) {
  QGraphicsView::drawForeground(painter, rect);
  if (m_connectionSourcePoint != nullptr) {
    auto color =
        QApplication::palette().color(QPalette::Active, QPalette::WindowText);
    painter->setPen(QPen(color, 1, Qt::DashLine));
    painter->drawLine(m_connectionSourcePoint->sceneBoundingRect().center(),
                      m_currentMousePos);
  }
}

void GraphWidget::dragEnterEvent(QDragEnterEvent *event) {
  if (event->mimeData()->hasFormat("application/x-node")) {
    event->acceptProposedAction();
  } else {
    QGraphicsView::dragEnterEvent(event);
  }
}

void GraphWidget::dragMoveEvent(QDragMoveEvent *event) {
  if (event->mimeData()->hasFormat("application/x-node")) {
    event->acceptProposedAction();
  } else {
    QGraphicsView::dragMoveEvent(event);
  }
}

void GraphWidget::dropEvent(QDropEvent *event) {
  if (event->mimeData()->hasFormat("application/x-node")) {
    QPointF dropPoint = mapToScene(event->position().toPoint());

    VisualNode *newNode = m_dragBuffer->releaseNode().release();
    newNode->setPos(dropPoint - QPointF(40, 20));  // Adjust position to center
    m_scene.addItem(newNode);
    m_nodes.append(newNode);

    event->acceptProposedAction();
  } else {
    QGraphicsView::dropEvent(event);
  }
}

void GraphWidget::freezeAllNodes() {
  for (auto node : m_nodes) {
    node->setFlag(QGraphicsItem::ItemIsMovable, false);
  }
}

void GraphWidget::unfreezeAllNodes() {
  for (auto node : m_nodes) {
    node->setFlag(QGraphicsItem::ItemIsMovable, true);
  }
}

Connection *GraphWidget::removeConnectionByDestination(
    const ConnectionPoint *connectionPoint) {
  for (qsizetype i = 0; i < m_connections.size(); ++i) {
    if (m_connections[i]->destPoint() == connectionPoint) {
      auto connection = m_connections[i];
      m_connections.remove(i);
      return connection;
    }
  }
  return nullptr;
}

void GraphWidget::deleteConnectionsWithSelectedNodes() {
  auto firstConnectionToKeep = std::partition(
      m_connections.begin(), m_connections.end(), [this](auto connection) {
        return connectedToAnyDeletedNode(connection);
      });

  for (auto it = m_connections.begin(); it != firstConnectionToKeep; ++it) {
    Connection *connection = *it;
    connection->destPoint()->disconnect();
    connection->sourcePoint()->disconnect();
    m_controller->DetachNode(connection->destPoint()->getNodeId(),
                             connection->destPoint()->getSlot());
    delete *it;
  }

  m_connections.erase(m_connections.begin(), firstConnectionToKeep);
}

void GraphWidget::deleteSelectedNodes() {
  auto firstNodeToKeep = std::partition(
      m_nodes.begin(), m_nodes.end(),
      [](auto node) { return node->isDeletable() && node->isSelected(); });

  for (auto it = m_nodes.begin(); it != firstNodeToKeep; ++it) {
    scene()->removeItem(*it);
    delete *it;
  }

  m_nodes.erase(m_nodes.begin(), firstNodeToKeep);
}

bool GraphWidget::connectedToAnyDeletedNode(
    const Connection *connection) const {
  for (const auto *node : m_nodes) {
    if (node->isDeletable() && node->isSelected() &&
        node->isConnected(*connection)) {
      return true;
    }
  }
  return false;
}
