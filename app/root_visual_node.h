#ifndef ROOT_VISUAL_NODE_H
#define ROOT_VISUAL_NODE_H

#include "graph_controller.h"
#include "text_visual_node.h"

/*!
 * @brief Visual node representing the root of the graph
 *
 * Graph execution starts from the root. It appears first on the graph widget
 * and can never be deleted.
 */
class RootVisualNode : public TextVisualNode {
 public:
  /*!
   * @brief RootVisualNode
   * @param controller - GraphController used to interact with the graph
   * @param parent - parent graphics item
   */
  explicit RootVisualNode(GraphController* controller,
                          QGraphicsItem* parent = nullptr);

  bool isDeletable() const override;
};

#endif  // ROOT_VISUAL_NODE_H
