#ifndef NUMBER_VISUAL_NODE_H
#define NUMBER_VISUAL_NODE_H

#include <QFocusEvent>
#include <QLineEdit>
#include <QMouseEvent>
#include <QString>
#include <QVBoxLayout>
#include <QWidget>

#include "visual_node.h"

class NumberVisualNode : public VisualNode {
 public:
  explicit NumberVisualNode(QGraphicsItem* parent = nullptr);

 protected:
  void mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event) override;
  QVariant itemChange(GraphicsItemChange change, const QVariant &value) override;

 private:
  QGraphicsTextItem *m_textItem;
};

#endif  // NUMBER_VISUAL_NODE_H
