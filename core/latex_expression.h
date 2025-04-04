#ifndef LATEX_EXPRESSION_H
#define LATEX_EXPRESSION_H

#include <memory>
#include <string>

class LatexExpression {
 public:
  LatexExpression(std::string expression);
  std::unique_ptr<LatexExpression> operator+(const LatexExpression& rhs);

  virtual std::unique_ptr<LatexExpression> Integrate(double lower_limit,
                                                     double upper_limit) const;

  const std::string& GetExpression() const;

 private:
  std::string expression_;
};

#endif  // LATEX_EXPRESSION_H
