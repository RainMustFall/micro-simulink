#ifndef BINARY_OPERATOR_H
#define BINARY_OPERATOR_H

#include "node.h"

/*!
 * @brief A node with two inputs. Performs addition of dependency results. The
 * meaning of addition is defined by the type T.
 */
template <typename T>
class PlusOperator : public Node<T> {
 public:
  PlusOperator() : Node<T>(2) {}

  std::unique_ptr<T> Execute(
      const ExecutionResultFactory<T> &factory) const override {
    auto inputs = this->ExecuteDependencies(factory);
    return *(inputs.front()) + *(inputs.back());
  }
};

/*!
 * @brief A node with two inputs. Performs multiplication of dependency results.
 * The meaning of multiplication is defined by the type T.
 */
template <typename T>
class MultipliesOperator : public Node<T> {
 public:
  MultipliesOperator() : Node<T>(2) {}

  std::unique_ptr<T> Execute(
      const ExecutionResultFactory<T> &factory) const override {
    auto inputs = this->ExecuteDependencies(factory);
    return *(inputs.front()) * *(inputs.back());
  }
};

/*!
 * @brief A node with two inputs. Performs division of dependency results. The
 * meaning of division is defined by the type T.
 */
template <typename T>
class DividesOperator : public Node<T> {
 public:
  DividesOperator() : Node<T>(2) {}

  std::unique_ptr<T> Execute(
      const ExecutionResultFactory<T> &factory) const override {
    auto inputs = this->ExecuteDependencies(factory);
    return *(inputs.front()) / *(inputs.back());
  }
};

/*!
 * @brief A node with two inputs. Performs subtraction of dependency results.
 * The meaning of subtraction is defined by the type T.
 */
template <typename T>
class MinusOperator : public Node<T> {
 public:
  MinusOperator() : Node<T>(2) {}

  std::unique_ptr<T> Execute(
      const ExecutionResultFactory<T> &factory) const override {
    auto inputs = this->ExecuteDependencies(factory);
    return *(inputs.front()) - *(inputs.back());
  }
};

/*!
 * @brief A node with two inputs. Elevates the first dependency to the degree of
 * the second. The meaning of the power operation is defined by the type T.
 */
template <typename T>
class PowerOperator : public Node<T> {
 public:
  PowerOperator() : Node<T>(2) {}

  std::unique_ptr<T> Execute(
      const ExecutionResultFactory<T> &factory) const override {
    auto inputs = this->ExecuteDependencies(factory);
    return *(inputs.front()) ^ *(inputs.back());
  }
};

#endif  // BINARY_OPERATOR_H
