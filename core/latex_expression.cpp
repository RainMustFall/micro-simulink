#include "latex_expression.h"

#include <sstream>

LatexExpression::LatexExpression(std::string expression,
                                 Priority last_operation_priority)
    : expression_(std::move(expression)),
      last_operation_priority_(last_operation_priority) {}

std::unique_ptr<LatexExpression> LatexExpression::operator+(
    const LatexExpression& rhs) {
  auto priority = Priority::Additive;
  return std::make_unique<LatexExpression>(
      MaybePutParentheses(*this, priority) + "+" +
          MaybePutParentheses(rhs, priority),
      priority);
}

std::unique_ptr<LatexExpression> LatexExpression::operator-(
    const LatexExpression& rhs) {
  auto priority = Priority::Additive;
  return std::make_unique<LatexExpression>(
      MaybePutParentheses(*this, priority) + "-" +
          MaybePutParentheses(rhs, priority),
      priority);
}

std::unique_ptr<LatexExpression> LatexExpression::operator-() {
  auto priority = Priority::Negation;
  return std::make_unique<LatexExpression>(
      "-" + MaybePutParentheses(*this, Priority::Multiplicative), priority);
}

std::unique_ptr<LatexExpression> LatexExpression::operator*(
    const LatexExpression& rhs) {
  auto priority = Priority::Multiplicative;
  return std::make_unique<LatexExpression>(
      MaybePutParentheses(*this, priority) + "\\cdot " +
          MaybePutParentheses(rhs, priority),
      priority);
}

std::unique_ptr<LatexExpression> LatexExpression::operator/(
    const LatexExpression& rhs) {
  auto priority = Priority::Multiplicative;
  return std::make_unique<LatexExpression>(
      "\\dfrac{" + expression_ + "}{" + rhs.expression_ + "}", priority);
}

std::unique_ptr<LatexExpression> LatexExpression::operator^(
    const LatexExpression& rhs) {
  std::string base = expression_;
  if (last_operation_priority_ != Priority::Expression) {
    base = "\\left(" + base + "\\right)";
  }
  return std::make_unique<LatexExpression>(base + "^{" + rhs.expression_ + "}",
                                           Priority::Power);
}

std::unique_ptr<LatexExpression> LatexExpression::Integrate(
    double lower_limit, double upper_limit) const {
  std::ostringstream ss;
  ss << "\\int_{" << lower_limit << "}^{" << upper_limit << "}"
     << MaybePutParentheses(*this, Priority::Multiplicative) << "dx";
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

std::unique_ptr<LatexExpression> LatexExpression::Log() const {
  return wrapWithFunction("log");
}

std::unique_ptr<LatexExpression> LatexExpression::Exp() const {
  return wrapWithFunction("exp");
}

std::unique_ptr<LatexExpression> LatexExpression::Sqrt() const {
  return std::make_unique<LatexExpression>("\\sqrt{" + expression_ + "}");
}

const std::string& LatexExpression::GetExpression() const {
  return expression_;
}

std::string LatexExpression::MaybePutParentheses(
    const LatexExpression& expression, Priority new_priority) const {
  if (static_cast<int>(new_priority) >
      static_cast<int>(expression.last_operation_priority_)) {
    return "\\left(" + expression.GetExpression() + "\\right)";
  }

  return expression.GetExpression();
}

std::unique_ptr<LatexExpression> LatexExpression::wrapWithFunction(
    const std::string& function) const {
  return std::make_unique<LatexExpression>("\\" + function + "{\\left(" +
                                           expression_ + "\\right)}");
}

LatexExpression::~LatexExpression() {}
