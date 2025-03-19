#ifndef SCALAR_RESULT_FACTORY_H
#define SCALAR_RESULT_FACTORY_H

#include "execution_result_factory.h"
#include "function.h"

class FunctionFactory : public ExecutionResultFactory<Function> {
 public:
  std::unique_ptr<Function> CreateScalar(double scalar) const;
  std::unique_ptr<Function> CreateX() const;
};

#endif  // SCALAR_RESULT_FACTORY_H
