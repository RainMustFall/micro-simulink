#include "binary_operator.h"

BinaryOperatorVisualNode::BinaryOperatorVisualNode(size_t nodeId, QString op,
                                                   QGraphicsItem *parent)
    : TextVisualNode(/* numberOfInputs=*/2, /* numberOfOutputs=*/1, nodeId,
                     QRect(0, 0, kHeight, kHeight), std::move(op), parent) {}

PlusVisualNode::PlusVisualNode(GraphController *controller,
                               QGraphicsItem *parent)
    : BinaryOperatorVisualNode(controller->AddPlusNode(), "+", parent) {}

MinusVisualNode::MinusVisualNode(GraphController *controller,
                                 QGraphicsItem *parent)
    : BinaryOperatorVisualNode(controller->AddMinusNode(), "-", parent) {}

MultipliesVisualNode::MultipliesVisualNode(GraphController *controller,
                                           QGraphicsItem *parent)
    : BinaryOperatorVisualNode(controller->AddMultipliesNode(), "×", parent) {}

DividesVisualNode::DividesVisualNode(GraphController *controller,
                                     QGraphicsItem *parent)
    : BinaryOperatorVisualNode(controller->AddDividesNode(), "/", parent) {}

PowerVisualNode::PowerVisualNode(GraphController *controller,
                                 QGraphicsItem *parent)
    : BinaryOperatorVisualNode(controller->AddPowerNode(), "^", parent) {}
