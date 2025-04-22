#include "trigonometry_visual_nodes.h"

CotangentVisualNode::CotangentVisualNode(GraphController *controller,
                                         QGraphicsItem *parent)
    : TextVisualNode(/* numberOfInputs=*/1, /* numberOfOutputs=*/1,
                     controller->AddCotangentNode(), QRect(0, 0, 50, 40), "cot",
                     parent) {}

CosineVisualNode::CosineVisualNode(GraphController *controller,
                                     QGraphicsItem *parent)
    : TextVisualNode(/* numberOfInputs=*/1, /* numberOfOutputs=*/1,
                     controller->AddCosineNode(), QRect(0, 0, 50, 40), "cos",
                     parent) {}

SineVisualNode::SineVisualNode(GraphController *controller,
                                 QGraphicsItem *parent)
    : TextVisualNode(/* numberOfInputs=*/1, /* numberOfOutputs=*/1,
                     controller->AddSineNode(), QRect(0, 0, 50, 40), "sin",
                     parent) {}

TangentVisualNode::TangentVisualNode(GraphController *controller,
                                     QGraphicsItem *parent)
    : TextVisualNode(/* numberOfInputs=*/1, /* numberOfOutputs=*/1,
                     controller->AddTangentNode(), QRect(0, 0, 50, 40), "tan",
                     parent) {}
