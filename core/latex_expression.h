#ifndef LATEX_EXPRESSION_H
#define LATEX_EXPRESSION_H

#include <string>

class LatexExpression {
 public:
  LatexExpression(std::string expression);
  LatexExpression operator+(const LatexExpression& rhs);

  const std::string& GetExpression() const;

 private:
  std::string expression_;
};

#endif  // LATEX_EXPRESSION_H
