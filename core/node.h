#ifndef NODE_H
#define NODE_H

#include <cstddef>
#include <stdexcept>
#include <vector>

#include "exceptions.h"
#include "execution_result_factory.h"

/*!
 * @brief Represents a node of the graph (input, output or intermediate).
 *
 * It allows to attach/detach dependencies (other nodes) and return the
 * execution result (calling Execute from its dependencies, if necessary).
 *
 * It is a template parameterized with a type T - calculations are performed on
 * this type. Inheriting classes override the Execute method with specific
 * actions on an object of type T. An example of a T type could be a function of
 * one variable, a numeric constant or a LaTeX expression. In general, it is a
 * type that supports specific arithmetic operations (such as the addition
 * operator).
 */
template <typename T>
class Node {
 public:
  /*!
   * @brief Node
   * @param input_num - the number of inputs of this node
   */
  explicit Node(size_t input_num) : dependencies_(input_num) {}

  /*!
   * @brief Get number of inputs
   * @return number of inputs
   */
  size_t GetNumInputs() const { return dependencies_.size(); }

  /*!
   * @brief Attach other node as input
   * @param slot_index - index of the input slot to attach the dependency
   * @param input - the dependency to attach
   * @return link to itself after update
   */
  Node<T>& AttachInput(size_t slot_index, const Node<T>& input) {
    CheckSlotIndex(slot_index);
    dependencies_[slot_index] = &input;
    return *this;
  }

  /*!
   * @brief Detach the input dependency
   * @param slot_index - index of the input slot to detach the dependency
   * @return link to itself after update
   */
  Node<T>& DetachInput(size_t slot_index) {
    CheckSlotIndex(slot_index);
    dependencies_[slot_index] = nullptr;
    return *this;
  }

  /*!
   * @brief Perform the main action of this node (e.g., an arithmetic
   * operation).
   * @param factory - factory used to create initial objects
   * @return execution result
   */
  virtual std::unique_ptr<T> Execute(
      const ExecutionResultFactory<T>& factory) const = 0;

  virtual ~Node() {}

 protected:
  /*!
   * @brief Execute dependencies of the node
   * @param factory - factory used to create initial objects
   * @return vector of execution results of each dependency
   * @throws GraphIsIncomplete if some nodes are missing inputs
   */
  std::vector<std::unique_ptr<T>> ExecuteDependencies(
      const ExecutionResultFactory<T>& factory) const {
    std::vector<std::unique_ptr<T>> result;
    for (size_t i = 0; i < dependencies_.size(); ++i) {
      if (dependencies_[i] == nullptr) {
        throw GraphIsIncomplete(
            "The graph is incomplete: some nodes are missing inputs!");
      }

      result.emplace_back(dependencies_[i]->Execute(factory));
    }

    return result;
  }

 private:
  void CheckSlotIndex(size_t slot_index) {
    if (slot_index >= dependencies_.size()) {
      throw std::out_of_range("Tried to access slot with index out of range");
    }
  }

  std::vector<const Node<T>*> dependencies_;
};

#endif  // NODE_H
