#ifndef LATEX_EXPRESSION_H
#define LATEX_EXPRESSION_H

#include <memory>
#include <string>

enum class Priority { Additive = 0, Multiplicative = 1, Expression = 2 };

/*!
 * @brief Stores a syntactically correct LaTeX expression.
 *
 * It defines operations on it so that new LaTeX expressions are created. For
 * example, .Sin from “x + 5” will return “\sin{(x + 5)}”.
 */
class LatexExpression {
 public:
  LatexExpression(std::string expression,
                  Priority last_operation_priority = Priority::Expression);
  std::unique_ptr<LatexExpression> operator+(const LatexExpression& rhs);

  /*!
   * @brief Create LaTeX expression representing integral of the current
   * expression
   * @return A new LaTeX expression
   */
  virtual std::unique_ptr<LatexExpression> Integrate(double lower_limit,
                                                     double upper_limit) const;

  /*!
   * @brief Create \sin(<THIS>) LaTeX expression
   * @return A new LaTeX expression
   */
  std::unique_ptr<LatexExpression> Sin() const;

  /*!
   * @brief Create \cos(<THIS>) LaTeX expression
   * @return A new LaTeX expression
   */
  std::unique_ptr<LatexExpression> Cos() const;

  /*!
   * @brief Create \tan(<THIS>) LaTeX expression
   * @return A new LaTeX expression
   */
  std::unique_ptr<LatexExpression> Tan() const;

  /*!
   * @brief Create \cot(<THIS>) LaTeX expression
   * @return A new LaTeX expression
   */
  std::unique_ptr<LatexExpression> Cot() const;

  /*!
   * @brief Get string representation of the LaTeX expression
   * @return string representation
   */
  const std::string& GetExpression() const;

 private:
  std::string MaybePutParentheses(std::string expression,
                                  Priority new_priority) const;

  std::unique_ptr<LatexExpression> wrapWithFunction(
      const std::string& function) const;

  std::string expression_;
  Priority last_operation_priority_;
};

#endif  // LATEX_EXPRESSION_H
