#ifndef GRAPH_CONTROLLER_H
#define GRAPH_CONTROLLER_H

#include <stddef.h>

#include <memory>
#include <string>
#include <vector>

#include "function.h"
#include "graph_update_subscription.h"
#include "latex_expression.h"
#include "node.h"

/*!
 * @brief Stores and manages the current computational graph. Rebuilds it on
 * user interface request and returns the graph execution result.
 */
class GraphController : public GraphUpdateNotifier {
 public:
  GraphController();

  /*!
   * @brief Add scalar node
   * @param value - the scalar stored in the node
   * @return ID of the newly created node
   */
  size_t AddScalarNode(double value);

  /*!
   * @brief Set scalar value of the node
   * @param node_id - ID of the scalar node
   * @param value - the value to set
   */
  void SetScalarValue(size_t node_id, double value);

  /*!
   * @brief Add root node
   * @return ID of the newly created node
   */
  size_t AddRootNode();

  /*!
   * @brief Add "x" node
   * @return ID of the newly created node
   */
  size_t AddXNode();

  /*!
   * @brief Add plus node
   * @return ID of the newly created node
   */
  size_t AddPlusNode();

  /*!
   * @brief Add integral node
   * @param lower_limit - lower limit of integration
   * @param upper_limit - upper limit of integration
   * @return  ID of the newly created node
   */
  size_t AddIntegralNode(double lower_limit, double upper_limit);

  /*!
   * @brief Add sin node
   * @return ID of the newly created node
   */
  size_t AddSineNode();

  /*!
   * @brief Add cos node
   * @return ID of the newly created node
   */
  size_t AddCosineNode();

  /*!
   * @brief Add tan node
   * @return ID of the newly created node
   */
  size_t AddTangentNode();

  /*!
   * @brief Add cot node
   * @return ID of the newly created node
   */
  size_t AddCotangentNode();

  /*!
   * @brief Set integral limits
   * @param node_id - ID of the integral node
   * @param lower_limit - new lower limit of integration
   * @param upper_limit - new upper limit of integration
   */
  void SetIntegralLimits(size_t node_id, double lower_limit,
                         double upper_limit);

  /*!
   * @brief Connect nodes
   * @param src_node - ID of the source node
   * @param dst_node - ID of the destination node
   * @param slot - index of the input slot of the destination node
   */
  void ConnectNodes(size_t src_node, size_t dst_node, size_t slot);

  /*!
   * @brief Detach input from the node
   * @param dst_node - ID of the destination node
   * @param slot - index of the input slot of the destination node
   */
  void DetachNode(size_t dst_node, size_t slot);

  /*!
   * @brief Execute the graph and get the result
   * @return Execution result
   * @throws ResultIsNotScalar if a function was returned
   * @throws GraphIsIncomplete if some deepndencies are missing
   */
  double GetGraphResult() const;

  /*!
   * @brief Get latex representation of the graph
   * @return latex representation of the graph
   */
  std::string GetLatex() const;

 private:
  std::vector<std::unique_ptr<Node<Function>>> nodes_;
  std::vector<std::unique_ptr<Node<LatexExpression>>> latex_nodes_;

  static const size_t kRootIndex = 0;

  template <template <class> class NodeType, typename... Args>
  size_t AddNode(Args &&...args) {
    nodes_.emplace_back(new NodeType<Function>(std::forward<Args>(args)...));

    latex_nodes_.emplace_back(
        new NodeType<LatexExpression>(std::forward<Args>(args)...));

    return nodes_.size() - 1;
  }
};

#endif  // GRAPH_CONTROLLER_H
