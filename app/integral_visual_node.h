#ifndef INTEGRAL_VISUAL_NODE_H
#define INTEGRAL_VISUAL_NODE_H

#include <QPainter>

#include "graph_controller.h"
#include "visual_node.h"

/*!
 * @brief Visual node representing integral
 */
class IntegralVisualNode : public VisualNode {
 public:
  /*!
   * @brief IntegralVisualNode constructor
   * @param controller - GraphController maintaining the graph model
   * @param parent - parent graphich item
   */
  explicit IntegralVisualNode(GraphController *controller,
                              QGraphicsItem *parent = nullptr);

 protected:
  void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
             QWidget *widget = nullptr) override;

  void mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event) override;

 private:
  double upperLimit;
  double lowerLimit;

  GraphController *m_controller;

  constexpr static double kHeight = 70.0;
};

#endif  // INTEGRAL_VISUAL_NODE_H
