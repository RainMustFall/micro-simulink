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
  virtual std::unique_ptr<Function> operator-(const Function &rhs);
  virtual std::unique_ptr<Function> operator-();
  virtual std::unique_ptr<Function> operator/(const Function &rhs);
  virtual std::unique_ptr<Function> operator*(const Function &rhs);
  virtual std::unique_ptr<Function> operator^(const Function &rhs);

  /*!
   * @brief Integrate the fucntion
   * @param lower_limit - lower limit for integration
   * @param upper_limit - upper limit for integration
   * @return Scalar with the result of integration
   */
  virtual std::unique_ptr<Function> Integrate(double lower_limit,
                                              double upper_limit) const;

  /*!
   * @brief Calculate f(x) -> sin(f(x))
   * @return sin(f(x)) function
   */
  std::unique_ptr<Function> Sin() const;

  /*!
   * @brief Calculate f(x) -> cos(f(x))
   * @return cos(f(x)) function
   */
  std::unique_ptr<Function> Cos() const;

  /*!
   * @brief Calculate f(x) -> tan(f(x))
   * @return tan(f(x)) function
   */
  std::unique_ptr<Function> Tan() const;

  /*!
   * @brief Calculate f(x) -> cot(f(x))
   * @return cot(f(x)) function
   */
  std::unique_ptr<Function> Cot() const;

  /*!
   * @brief Calculate f(x) -> sqrt(f(x))
   * @return sqrt(f(x)) function
   */
  std::unique_ptr<Function> Sqrt() const;

  /*!
   * @brief Calculate f(x) -> log(f(x))
   * @return log(f(x)) function
   */
  std::unique_ptr<Function> Log() const;

  /*!
   * @brief Calculate f(x) -> Exp(f(x))
   * @return Exp(f(x)) function
   */
  std::unique_ptr<Function> Exp() const;

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

  virtual ~Function();

 protected:
  /*!
   * @brief Apply some mathematical unary function to the internal
   * representation
   *
   * Function instance applies `func` to each point. Scalar applies it to its
   * only value, returning another scalar
   * @param func - mathematical function to apply (e.g., std::sin)
   * @return a new function func(f(x))
   */
  virtual std::unique_ptr<Function> calculateMathFunction(
      std::function<double(double)> func) const;

 private:
  std::function<double(double)> function_;
};

#endif  // FUNCTION_H
