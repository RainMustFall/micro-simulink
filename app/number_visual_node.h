#ifndef NUMBER_VISUAL_NODE_H
#define NUMBER_VISUAL_NODE_H

#include <QFocusEvent>
#include <QLineEdit>
#include <QMouseEvent>
#include <QString>
#include <QVBoxLayout>
#include <QWidget>

#include "graph_controller.h"
#include "visual_node.h"

class NumberVisualNode : public VisualNode {
 public:
  explicit NumberVisualNode(GraphController *controller,
                            QGraphicsItem *parent = nullptr);

 protected:
  void mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event) override;
  QVariant itemChange(GraphicsItemChange change,
                      const QVariant &value) override;

 private:
  QGraphicsTextItem *m_textItem;

  double m_value;

  GraphController *m_controller;
};

#endif  // NUMBER_VISUAL_NODE_H
