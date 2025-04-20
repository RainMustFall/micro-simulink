#ifndef ROOT_VISUAL_NODE_H
#define ROOT_VISUAL_NODE_H

#include "graph_controller.h"
#include "text_visual_node.h"

class RootVisualNode : public TextVisualNode {
 public:
  explicit RootVisualNode(GraphController* controller,
                          QGraphicsItem* parent = nullptr);

  bool isDeletable() const override;
};

#endif  // ROOT_VISUAL_NODE_H
