#include "root_visual_node.h"

RootVisualNode::RootVisualNode(GraphController *controller,
                               QGraphicsItem *parent)
    : VisualNode(/* numInputs= */ 1, controller->AddRootNode(),
                 QRect(-40, -20, 80, 40), parent) {}
