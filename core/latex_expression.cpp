#include "latex_expression.h"

LatexExpression::LatexExpression(std::string expression)
    : expression_(std::move(expression)) {}

LatexExpression LatexExpression::operator+(const LatexExpression& rhs) {
  return LatexExpression(expression_ + '+' + rhs.expression_);
}

const std::string& LatexExpression::GetExpression() const {
  return expression_;
}
