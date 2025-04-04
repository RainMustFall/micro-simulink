#include "graph_controller.h"

#include <cassert>

#include "binary_operator.h"
#include "integral_node.h"
#include "latex_expression_factory.h"
#include "root_node.h"
#include "scalar.h"
#include "scalar_node.h"
#include "scalar_result_factory.h"
#include "x_node.h"

GraphController::GraphController() {}

size_t GraphController::AddRootNode() { return AddNode<RootNode>(); }

size_t GraphController::AddScalarNode(double value) {
  return AddNode<ScalarNode>(value);
}

size_t GraphController::AddXNode() { return AddNode<XNode>(); }

size_t GraphController::AddPlusNode() { return AddNode<PlusOperator>(); }

size_t GraphController::AddIntegralNode(double lower_limit,
                                        double upper_limit) {
  return AddNode<IntegralNode>(lower_limit, upper_limit);
}

void GraphController::SetIntegralLimits(size_t node_id, double lower_limit,
                                        double upper_limit) {
  static_cast<IntegralNode<Function>*>(nodes_[node_id].get())
      ->SetLimits(lower_limit, upper_limit);
  static_cast<IntegralNode<LatexExpression>*>(latex_nodes_[node_id].get())
      ->SetLimits(lower_limit, upper_limit);
  NotifySubscribers();
}

void GraphController::ConnectNodes(size_t src_node, size_t dst_node,
                                   size_t slot) {
  nodes_[dst_node]->AttachInput(slot, *(nodes_[src_node]));
  latex_nodes_[dst_node]->AttachInput(slot, *(latex_nodes_[src_node]));
  NotifySubscribers();
}

void GraphController::DetachNode(size_t dst_node, size_t slot) {
  nodes_[dst_node]->DetachInput(slot);
  latex_nodes_[dst_node]->DetachInput(slot);
  NotifySubscribers();
}

void GraphController::SetScalarValue(size_t node_id, double value) {
  static_cast<ScalarNode<Function>*>(nodes_[node_id].get())->SetValue(value);
  static_cast<ScalarNode<LatexExpression>*>(latex_nodes_[node_id].get())
      ->SetValue(value);
  NotifySubscribers();
}

double GraphController::GetGraphResult() {
  auto function = nodes_[kRootIndex]->Execute(FunctionFactory());
  auto scalar = dynamic_cast<Scalar*>(function.get());
  if (scalar == nullptr) {
    throw std::domain_error(
        "Only scalar expressions are supported! The graph produced a function");
  }
  return scalar->GetValue();
}

std::string GraphController::GetLatex() {
  auto latex_expression =
      latex_nodes_[kRootIndex]->Execute(LatexExpressionFactory());
  return latex_expression->GetExpression();
}
