#ifndef LATEX_EXPRESSION_FACTORY_H
#define LATEX_EXPRESSION_FACTORY_H

#include "execution_result_factory.h"
#include "latex_expression.h"

/*!
 * @brief Factory responsible for creating the simplest LaTeX expressions.
 *
 * It can create scalars: “5”, “3.14” - and the expression “x”, on which
 * arithmetic operations will be performed, creating more complex expressions.
 */
class LatexExpressionFactory : public ExecutionResultFactory<LatexExpression> {
 public:
  std::unique_ptr<LatexExpression> CreateScalar(double scalar) const;
  std::unique_ptr<LatexExpression> CreateX() const;
};

#endif  // LATEX_EXPRESSION_FACTORY_H
