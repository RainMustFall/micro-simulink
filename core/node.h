#ifndef NODE_H
#define NODE_H

#include <cstddef>
#include <stdexcept>
#include <vector>

#include "execution_result_factory.h"

template <typename T>
class Node {
 public:
  explicit Node(size_t input_num) : dependencies_(input_num) {}

  size_t GetNumInputs() const { return dependencies_.size(); }

  Node<T>& AttachInput(size_t slot_index, const Node<T>& input) {
    CheckSlotIndex(slot_index);
    dependencies_[slot_index] = &input;
    return *this;
  }

  Node<T>& DetachInput(size_t slot_index) {
    CheckSlotIndex(slot_index);
    dependencies_[slot_index] = nullptr;
    return *this;
  }

  virtual std::unique_ptr<T> Execute(
      const ExecutionResultFactory<T>& factory) const = 0;

  virtual ~Node() {}

 protected:
  std::vector<std::unique_ptr<T>> ExecuteDependencies(
      const ExecutionResultFactory<T>& factory) const {
    std::vector<std::unique_ptr<T>> result;
    for (size_t i = 0; i < dependencies_.size(); ++i) {
      if (dependencies_[i] == nullptr) {
        throw std::runtime_error(
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
