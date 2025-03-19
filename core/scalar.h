#ifndef SCALAR_H
#define SCALAR_H

#include "function.h"

class Scalar : public Function {
 public:
  Scalar(double value);
  double GetValue() const;
};

#endif  // SCALAR_H
