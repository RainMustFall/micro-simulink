#ifndef TRIGONOMETRY_H
#define TRIGONOMETRY_H

/*!
 * @brief The node calculating sine of its input
 */
template <typename T>
class SineNode : public Node<T> {
 public:
  SineNode() : Node<T>(1) {}

  std::unique_ptr<T> Execute(
      const ExecutionResultFactory<T> &factory) const override {
    auto inputs = this->ExecuteDependencies(factory);
    return inputs.front()->Sin();
  }
};

/*!
 * @brief The node calculating cosine of its input
 */
template <typename T>
class CosineNode : public Node<T> {
 public:
  CosineNode() : Node<T>(1) {}

  std::unique_ptr<T> Execute(
      const ExecutionResultFactory<T> &factory) const override {
    auto inputs = this->ExecuteDependencies(factory);
    return inputs.front()->Cos();
  }
};

/*!
 * @brief The node calculating tangent of its input
 */
template <typename T>
class TangentNode : public Node<T> {
 public:
  TangentNode() : Node<T>(1) {}

  std::unique_ptr<T> Execute(
      const ExecutionResultFactory<T> &factory) const override {
    auto inputs = this->ExecuteDependencies(factory);
    return inputs.front()->Tan();
  }
};

/*!
 * @brief The node calculating cotangent of its input
 */
template <typename T>
class CotangentNode : public Node<T> {
 public:
  CotangentNode() : Node<T>(1) {}

  std::unique_ptr<T> Execute(
      const ExecutionResultFactory<T> &factory) const override {
    auto inputs = this->ExecuteDependencies(factory);
    return inputs.front()->Cot();
  }
};

#endif  // TRIGONOMETRY_H
