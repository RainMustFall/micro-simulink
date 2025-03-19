#include "scalar.h"

Scalar::Scalar(double value) : Function([value](double) { return value; }) {}

double Scalar::GetValue() const { return this->operator()(0); }
