#include "trigonometry_visual_nodes.h"

#include "trigonometry.h"

CotangentVisualNode::CotangentVisualNode(GraphController *controller,
                                         QGraphicsItem *parent)
    : TextVisualNode(/* numberOfInputs=*/1, /* numberOfOutputs=*/1,
                     controller->AddNode<CotangentNode>(), QRect(0, 0, 50, 40),
                     "cot", parent) {}

CosineVisualNode::CosineVisualNode(GraphController *controller,
                                   QGraphicsItem *parent)
    : TextVisualNode(/* numberOfInputs=*/1, /* numberOfOutputs=*/1,
                     controller->AddNode<CosineNode>(), QRect(0, 0, 50, 40),
                     "cos", parent) {}

SineVisualNode::SineVisualNode(GraphController *controller,
                               QGraphicsItem *parent)
    : TextVisualNode(/* numberOfInputs=*/1, /* numberOfOutputs=*/1,
                     controller->AddNode<SineNode>(), QRect(0, 0, 50, 40),
                     "sin", parent) {}

TangentVisualNode::TangentVisualNode(GraphController *controller,
                                     QGraphicsItem *parent)
    : TextVisualNode(/* numberOfInputs=*/1, /* numberOfOutputs=*/1,
                     controller->AddNode<TangentNode>(), QRect(0, 0, 50, 40),
                     "tan", parent) {}
