#ifndef EXCEPTIONS_H
#define EXCEPTIONS_H

#include <stdexcept>
#include <string>

/*!
 * @brief Exception thrown by a node if some of its dependencies are missing
 */
class GraphIsIncomplete : public std::runtime_error {
 public:
  /*!
   * @brief GraphIsIncomplete
   * @param message
   */
  GraphIsIncomplete(const std::string& message);
};

/*!
 * @brief Exception thrown by controller if scalar was requested, but the graph
 * produced a function
 */
class ResultIsNotScalar : public std::runtime_error {
 public:
    /*!
   * @brief ResultIsNotScalar
   * @param message
   */
  ResultIsNotScalar(const std::string& message);
};

#endif  // EXCEPTIONS_H
