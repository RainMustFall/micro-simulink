#ifndef SCALAR_H
#define SCALAR_H

#include "function.h"

/*!
 * @brief A special case of the function, but simpler (returns the same value
 * for any argument).
 *
 * Introduced to optimize some calculations. For example,
 * calculating the numerical integral for a constant does not require performing
 * the full algorithm (dividing into small trapezoids and summing), and can be
 * replaced by a single formula for the area of a rectangle.
 */
class Scalar : public Function {
 public:
  /*!
   * @brief Scalar
   * @param value - the numeric value of the scalar
   */
  Scalar(double value);

  /*!
   * @brief Get value
   * @return scalar value as double
   */
  double GetValue() const;

  std::unique_ptr<Function> operator+(const Function &rhs) override;

  virtual std::unique_ptr<Function> Integrate(
      double lower_limit, double upper_limit) const override;

  std::unique_ptr<Function> OperatorWithScalar(
      const Function &scalar,
      const std::function<double(double, double)> &op) const override;
};

#endif  // SCALAR_H
