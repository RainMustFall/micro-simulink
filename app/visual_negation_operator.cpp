#include "visual_negation_operator.h"

#include "negation_node.h"

VisualNegationOperator::VisualNegationOperator(GraphController *controller,
                                               QGraphicsItem *parent)
    : TextVisualNode(/* numberOfInputs=*/1, /* numberOfOutputs=*/1,
                     controller->AddNode<NegationNode>(), QRect(0, 0, 50, 40),
                     "neg", parent) {}
