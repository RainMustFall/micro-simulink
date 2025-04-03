#include "graph_controller.h"

#include <cassert>

#include "binary_operator.h"
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

void GraphController::ConnectNodes(size_t src_node, size_t dst_node,
                                   size_t slot) {
  nodes_[dst_node]->AttachInput(slot, *(nodes_[src_node]));
  NotifySubscribers();
}

void GraphController::DetachNode(size_t dst_node, size_t slot) {
  nodes_[dst_node]->DetachInput(slot);
  NotifySubscribers();
}

double GraphController::GetGraphResult() {
  auto function = nodes_[kRootIndex]->Execute(FunctionFactory());
  auto scalar = static_cast<Scalar*>(function.get());
  // if (scalar == nullptr) {
  //   throw std::domain_error(
  //       "Only scalar expressions are supported! The graph produced a
  //       function");
  // }
  return scalar->GetValue();
}
