#ifndef FUNCTION_H
#define FUNCTION_H

#include <functional>
#include <memory>

/*!
 * @brief Represents a mathematical function, overriding the () operator
 * (accepting double and returning double).
 *
 * Can be used as a T type to parameterize a graph.
 */
class Function {
 public:
  /*!
   * @brief Function
   * @param function - a functor on which the operations will be performed
   */
  Function(std::function<double(double)> function);

  virtual double operator()(double x) const { return function_(x); }

  virtual std::unique_ptr<Function> operator+(const Function &rhs);

  /*!
   * @brief Integrate the fucntion
   * @param lower_limit - lower limit for integration
   * @param upper_limit - upper limit for integration
   * @return Scalar with the result of integration
   */
  virtual std::unique_ptr<Function> Integrate(double lower_limit,
                                              double upper_limit) const;

  /*!
   * @brief Perform the binary operation on another function and this one
   *
   * Dual dispatching (an approach often used in Visitor) is used here to
   * implement operations on function/function and function/number separately
   * @param function - the first operand
   * @param op - binary operation to perform
   * @return result of the operation
   */
  virtual std::unique_ptr<Function> OperatorWithFunction(
      const Function &function,
      const std::function<double(double, double)> &op) const;

  /*!
   * @brief Perform the binary operation on scalar and this function
   *
   * Dual dispatching (an approach often used in Visitor) is used here to
   * implement operations on function/function and function/number separately
   * @param scalar - the first operand
   * @param op - binary operation to perform
   * @return result of the operation
   */
  virtual std::unique_ptr<Function> OperatorWithScalar(
      const Function &scalar,
      const std::function<double(double, double)> &op) const;

 private:
  std::function<double(double)> function_;
};

#endif  // FUNCTION_H
