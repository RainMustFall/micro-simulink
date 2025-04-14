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

class EditableTextItem : public QGraphicsTextItem {
 public:
  EditableTextItem(double initialValue, size_t nodeId,
                   GraphController *controller,
                   QGraphicsItem *parent = nullptr);

 protected:
  void keyPressEvent(QKeyEvent *event) override;
  void focusOutEvent(QFocusEvent *event) override;

 private:
  void saveEnteredValue();
  GraphController *m_controller;
  double m_value;
  size_t m_nodeId;
};

class NumberVisualNode : public VisualNode {
 public:
  explicit NumberVisualNode(GraphController *controller,
                            QGraphicsItem *parent = nullptr);

  bool isGettingTextInput() const override;

 protected:
  void mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event) override;

  void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
             QWidget *widget) override;

 private:
  void updateTextPosition();

  EditableTextItem *m_textItem;
  void updateRectWidth();

  constexpr static double kHeight = 40;
};

#endif  // NUMBER_VISUAL_NODE_H
