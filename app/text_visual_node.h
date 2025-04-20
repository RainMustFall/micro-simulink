#ifndef TEXT_VISUAL_NODE_H
#define TEXT_VISUAL_NODE_H

#include "visual_node.h"

class TextVisualNode : public VisualNode {
 public:
  TextVisualNode(size_t numberOfInputs, size_t numberOfOutputs, size_t id,
                 const QRect &rect, QString text, QGraphicsItem *parent);

  void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
             QWidget *widget = nullptr) override;

 private:
  QString m_text;
};

#endif  // TEXT_VISUAL_NODE_H
