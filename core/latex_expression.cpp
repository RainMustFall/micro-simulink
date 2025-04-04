#include "latex_expression.h"

#include <sstream>

LatexExpression::LatexExpression(std::string expression)
    : expression_(std::move(expression)) {}

std::unique_ptr<LatexExpression> LatexExpression::operator+(
    const LatexExpression& rhs) {
  return std::make_unique<LatexExpression>(expression_ + '+' + rhs.expression_);
}

std::unique_ptr<LatexExpression> LatexExpression::Integrate(
    double lower_limit, double upper_limit) const {
  std::ostringstream ss;
  ss << "\\int_{" << lower_limit << "}^{" << upper_limit << "}\\left("
     << expression_ << "\\right)dx";
  return std::make_unique<LatexExpression>(ss.str());
}

const std::string& LatexExpression::GetExpression() const {
  return expression_;
}
