#ifndef TEXT_VISUAL_NODE_H
#define TEXT_VISUAL_NODE_H

#include "visual_node.h"

/*!
 * @brief Visual node which is rendered with plain text on it
 *
 * Should be inherited by concrete nodes and cannot be created on its own
 */
class TextVisualNode : public VisualNode {
 protected:
  /*!
   * @brief TextVisualNode
   * @param numberOfInputs - number of inputs the node accepts
   * @param numberOfOutputs - number of outputs of the node
   * @param id - ID of the node this visual node corresponds to
   * @param rect - rectangle describing the shape of the node
   * @param text - the text displayed on the node
   * @param parent - parent graphics item
   */
  TextVisualNode(size_t numberOfInputs, size_t numberOfOutputs, size_t id,
                 const QRect &rect, QString text, QGraphicsItem *parent);

  void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
             QWidget *widget = nullptr) override;

 private:
  QString m_text;
};

#endif  // TEXT_VISUAL_NODE_H
