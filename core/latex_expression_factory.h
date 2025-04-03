#ifndef LATEX_EXPRESSION_FACTORY_H
#define LATEX_EXPRESSION_FACTORY_H

#include "execution_result_factory.h"
#include "latex_expression.h"

class LatexExpressionFactory : public ExecutionResultFactory<LatexExpression> {
 public:
  std::unique_ptr<LatexExpression> CreateScalar(double scalar) const;
  std::unique_ptr<LatexExpression> CreateX() const;
};

#endif  // LATEX_EXPRESSION_FACTORY_H
