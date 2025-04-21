#ifndef EXCEPTIONS_H
#define EXCEPTIONS_H

#include <stdexcept>
#include <string>

class GraphIsIncomplete : public std::runtime_error {
 public:
  GraphIsIncomplete(const std::string& message);
};

class ResultIsNotScalar : public std::runtime_error {
 public:
  ResultIsNotScalar(const std::string& message);
};

#endif  // EXCEPTIONS_H
