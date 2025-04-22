#include "visual_binary_operator.h"

#include "binary_operator.h"

BinaryOperatorVisualNode::BinaryOperatorVisualNode(size_t nodeId, QString op,
                                                   QGraphicsItem *parent)
    : TextVisualNode(/* numberOfInputs=*/2, /* numberOfOutputs=*/1, nodeId,
                     QRect(0, 0, kHeight, kHeight), std::move(op), parent) {}

PlusVisualNode::PlusVisualNode(GraphController *controller,
                               QGraphicsItem *parent)
    : BinaryOperatorVisualNode(controller->AddNode<PlusOperator>(), "+",
                               parent) {}

MinusVisualNode::MinusVisualNode(GraphController *controller,
                                 QGraphicsItem *parent)
    : BinaryOperatorVisualNode(controller->AddNode<MinusOperator>(), "-",
                               parent) {}

MultipliesVisualNode::MultipliesVisualNode(GraphController *controller,
                                           QGraphicsItem *parent)
    : BinaryOperatorVisualNode(controller->AddNode<MultipliesOperator>(), "×",
                               parent) {}

DividesVisualNode::DividesVisualNode(GraphController *controller,
                                     QGraphicsItem *parent)
    : BinaryOperatorVisualNode(controller->AddNode<DividesOperator>(), "/",
                               parent) {}

PowerVisualNode::PowerVisualNode(GraphController *controller,
                                 QGraphicsItem *parent)
    : BinaryOperatorVisualNode(controller->AddNode<PowerOperator>(), "^",
                               parent) {}
