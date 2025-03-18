#ifndef SCALAR_RESULT_FACTORY_H
#define SCALAR_RESULT_FACTORY_H

#include "execution_result_factory.h"

class ScalarResultFactory : public ExecutionResultFactory {
 public:
  std::unique_ptr<ExecutionResult> CreateScalar(double scalar) const;
  std::unique_ptr<ExecutionResult> CreateX() const;
};

#endif  // SCALAR_RESULT_FACTORY_H
