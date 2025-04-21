#ifndef LATEX_EXPRESSION_H
#define LATEX_EXPRESSION_H

#include <memory>
#include <string>

enum class Priority { Additive = 0, Multiplicative = 1, Expression = 2 };

/*!
 * @brief Stores a syntactically correct LaTeX expression.
 *
 * It defines operations on it so that new LaTeX expressions are created. For
 * example, .Sinus from “x + 5” will return “\sin{(x + 5)}”.
 */
class LatexExpression {
 public:
  LatexExpression(std::string expression,
                  Priority last_operation_priority = Priority::Expression);
  std::unique_ptr<LatexExpression> operator+(const LatexExpression& rhs);

  virtual std::unique_ptr<LatexExpression> Integrate(double lower_limit,
                                                     double upper_limit) const;

  const std::string& GetExpression() const;

 private:
  std::string MaybePutParentheses(std::string expression,
                                  Priority new_priority) const;
  std::string expression_;
  Priority last_operation_priority_;
};

#endif  // LATEX_EXPRESSION_H
