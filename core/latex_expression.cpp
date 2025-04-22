#include "latex_expression.h"

#include <sstream>

LatexExpression::LatexExpression(std::string expression,
                                 Priority last_operation_priority)
    : expression_(std::move(expression)),
      last_operation_priority_(last_operation_priority) {}

std::unique_ptr<LatexExpression> LatexExpression::operator+(
    const LatexExpression& rhs) {
  return std::make_unique<LatexExpression>(expression_ + '+' + rhs.expression_,
                                           Priority::Additive);
}

std::unique_ptr<LatexExpression> LatexExpression::Integrate(
    double lower_limit, double upper_limit) const {
  std::ostringstream ss;
  ss << "\\int_{" << lower_limit << "}^{" << upper_limit << "}"
     << MaybePutParentheses(expression_, Priority::Multiplicative) << "dx";
  return std::make_unique<LatexExpression>(ss.str(), Priority::Multiplicative);
}

std::unique_ptr<LatexExpression> LatexExpression::Sin() const {
  return wrapWithFunction("sin");
}

std::unique_ptr<LatexExpression> LatexExpression::Cos() const {
  return wrapWithFunction("cos");
}

std::unique_ptr<LatexExpression> LatexExpression::Tan() const {
  return wrapWithFunction("tan");
}

std::unique_ptr<LatexExpression> LatexExpression::Cot() const {
  return wrapWithFunction("cot");
}

const std::string& LatexExpression::GetExpression() const {
  return expression_;
}

std::string LatexExpression::MaybePutParentheses(std::string expression,
                                                 Priority new_priority) const {
  if (static_cast<int>(new_priority) >
      static_cast<int>(last_operation_priority_)) {
    return "\\left(" + expression + "\\right)";
  }

  return expression;
}

std::unique_ptr<LatexExpression> LatexExpression::wrapWithFunction(
    const std::string& function) const {
  return std::make_unique<LatexExpression>("\\" + function + "{\\left(" +
                                           expression_ + "\\right)}");
}
