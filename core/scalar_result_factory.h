#ifndef SCALAR_RESULT_FACTORY_H
#define SCALAR_RESULT_FACTORY_H

#include "execution_result_factory.h"
#include "function.h"

/*!
 * @brief Factory responsible for creating the Function object that will be
 * processed in the graph.
 *
 * ScalarNode or XNode call the Create... method of the factory to create an
 * initial Function
 */
class FunctionFactory : public ExecutionResultFactory<Function> {
 public:
  std::unique_ptr<Function> CreateScalar(double scalar) const override;
  std::unique_ptr<Function> CreateX() const override;
};

#endif  // SCALAR_RESULT_FACTORY_H
