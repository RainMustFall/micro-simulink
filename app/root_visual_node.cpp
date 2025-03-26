#include "root_visual_node.h"

RootVisualNode::RootVisualNode(GraphController *controller,
                               QGraphicsItem *parent)
    : VisualNode(1, controller->AddRootNode(), parent) {}
