#include "graph_controller.h"

#include <cassert>

#include "binary_operator.h"
#include "exceptions.h"
#include "integral_node.h"
#include "latex_expression_factory.h"
#include "root_node.h"
#include "scalar.h"
#include "scalar_node.h"
#include "scalar_result_factory.h"
#include "trigonometry.h"
#include "x_node.h"

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

double GraphController::GetGraphResult() const {
  auto function = nodes_[kRootIndex]->Execute(FunctionFactory());
  auto scalar = dynamic_cast<Scalar*>(function.get());
  if (scalar == nullptr) {
    throw ResultIsNotScalar(
        "Only scalar expressions are supported! The graph produced a function");
  }
  return scalar->GetValue();
}

std::string GraphController::GetLatex() const {
  auto latex_expression =
      latex_nodes_[kRootIndex]->Execute(LatexExpressionFactory());
  return latex_expression->GetExpression();
}
