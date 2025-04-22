#include "latex_expression_factory.h"

#include <sstream>

std::unique_ptr<LatexExpression> LatexExpressionFactory::CreateScalar(
    double scalar) const {
  std::ostringstream sstream;
  sstream << scalar;
  auto priority = scalar < 0 ? Priority::Negation : Priority::Expression;
  return std::make_unique<LatexExpression>(sstream.str(), priority);
}

std::unique_ptr<LatexExpression> LatexExpressionFactory::CreateX() const {
  return std::make_unique<LatexExpression>("x");
}
