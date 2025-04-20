#include "root_visual_node.h"

RootVisualNode::RootVisualNode(GraphController *controller,
                               QGraphicsItem *parent)
    : TextVisualNode(/* numberOfInputs=*/1, /* numberOfOutputs=*/0,
                 controller->AddRootNode(), QRect(-40, -20, 80, 40), qtTrId("result"),
                 parent) {}

bool RootVisualNode::isDeletable() const { return false; }
