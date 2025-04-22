#ifndef VISUAL_NEGATION_OPERATOR_H
#define VISUAL_NEGATION_OPERATOR_H

#include "graph_controller.h"
#include "text_visual_node.h"

/*!
 * @brief Visual node corresponding to negation (-x)
 */
class VisualNegationOperator : public TextVisualNode {
 public:
  /*!
   * @brief VisualNegationOperator
   * @param controller - GraphController used to interact with the graph
   * @param parent - parent graphics item
   */
  explicit VisualNegationOperator(GraphController *controller,
                                  QGraphicsItem *parent = nullptr);
};

#endif  // VISUAL_NEGATION_OPERATOR_H
