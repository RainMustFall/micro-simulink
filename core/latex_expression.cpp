#include "latex_expression.h"

LatexExpression::LatexExpression(std::string expression)
    : expression_(std::move(expression)) {}

std::unique_ptr<LatexExpression> LatexExpression::operator+(const LatexExpression& rhs) {
  return std::make_unique<LatexExpression>(expression_ + '+' + rhs.expression_);
}

const std::string& LatexExpression::GetExpression() const {
  return expression_;
}
