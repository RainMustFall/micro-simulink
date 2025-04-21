#ifndef INTEGRAL_NODE_H
#define INTEGRAL_NODE_H

#include "node.h"

/*!
 * @brief The node performing integration of its input
 */
template <typename T>
class IntegralNode : public Node<T> {
 public:
  /*!
   * @brief IntegralNode
   * @param lower_limit - lower limit of integration
   * @param upper_limit - upper limit of integration
   */
  IntegralNode(double lower_limit, double upper_limit)
      : Node<T>(1), lower_limit_(lower_limit), upper_limit_(upper_limit) {}

  std::unique_ptr<T> Execute(
      const ExecutionResultFactory<T> &factory) const override {
    auto inputs = this->ExecuteDependencies(factory);
    return inputs.front()->Integrate(lower_limit_, upper_limit_);
  }

  /*!
   * @brief Set integration limits
   * @param lower_limit - new lower limit of integration
   * @param upper_limit - new upper limit of integration
   */
  void SetLimits(double lower_limit, double upper_limit) {
    lower_limit_ = lower_limit;
    upper_limit_ = upper_limit;
  }

 private:
  double lower_limit_;
  double upper_limit_;
};

#endif  // INTEGRAL_NODE_H
