#include "x_visual_node.h"

XVisualNode::XVisualNode(GraphController *controller, QGraphicsItem *parent)
    : TextVisualNode(/* numberOfInputs=*/0, /* numberOfOutputs=*/1,
                     controller->AddXNode(), QRect(0, 0, kHeight, kHeight), "x",
                     parent) {}
