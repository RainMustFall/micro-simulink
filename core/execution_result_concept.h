#ifndef EXECUTION_RESULT_CONCEPT_H
#define EXECUTION_RESULT_CONCEPT_H

#include <concepts>
#include <functional>
#include <memory>

template <typename T>
concept GraphExecutionResult = requires(T f, T g, double a, double b) {
  // Arithmetic operators
  { f + g } -> std::same_as<std::unique_ptr<T>>;
  { f - g } -> std::same_as<std::unique_ptr<T>>;
  { f * g } -> std::same_as<std::unique_ptr<T>>;
  { f / g } -> std::same_as<std::unique_ptr<T>>;
  { f ^ g } -> std::same_as<std::unique_ptr<T>>;
  { -f } -> std::same_as<std::unique_ptr<T>>;

  // Math functions
  { f.Sin() } -> std::same_as<std::unique_ptr<T>>;
  { f.Cos() } -> std::same_as<std::unique_ptr<T>>;
  { f.Tan() } -> std::same_as<std::unique_ptr<T>>;
  { f.Cot() } -> std::same_as<std::unique_ptr<T>>;
  { f.Sqrt() } -> std::same_as<std::unique_ptr<T>>;
  { f.Log() } -> std::same_as<std::unique_ptr<T>>;
  { f.Exp() } -> std::same_as<std::unique_ptr<T>>;

  // Integration
  { f.Integrate(a, b) } -> std::same_as<std::unique_ptr<T>>;
};

#endif  // EXECUTION_RESULT_CONCEPT_H
