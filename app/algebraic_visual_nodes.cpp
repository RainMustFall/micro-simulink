#include "algebraic_visual_nodes.h"

#include "unary_algebraic_functions.h"

SqrtVisualNode::SqrtVisualNode(GraphController *controller,
                               QGraphicsItem *parent)
    : TextVisualNode(/* numberOfInputs=*/1, /* numberOfOutputs=*/1,
                     controller->AddNode<SqrtNode>(), QRect(0, 0, 50, 40), "√",
                     parent) {}

LogVisualNode::LogVisualNode(GraphController *controller, QGraphicsItem *parent)
    : TextVisualNode(/* numberOfInputs=*/1, /* numberOfOutputs=*/1,
                     controller->AddNode<LogNode>(), QRect(0, 0, 50, 40), "log",
                     parent) {}

ExpVisualNode::ExpVisualNode(GraphController *controller, QGraphicsItem *parent)
    : TextVisualNode(/* numberOfInputs=*/1, /* numberOfOutputs=*/1,
                     controller->AddNode<ExpNode>(), QRect(0, 0, 50, 40), "exp",
                     parent) {}
