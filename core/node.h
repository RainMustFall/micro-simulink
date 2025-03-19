#ifndef NODE_H
#define NODE_H

#include <cstddef>

#include "execution_result_factory.h"

template <typename T>
class Executable {
 public:
  virtual std::unique_ptr<T> Execute(
      const ExecutionResultFactory<T>& factory) const = 0;
};

template <typename T, size_t NumInputs>
class Node : public Executable<T> {
 public:
  size_t GetNumInputs() const { return NumInputs; }

  Node<T, NumInputs>& AttachInput(size_t slot_index,
                                  const Executable<T>& input) {
    CheckSlotIndex(slot_index);
    dependencies_[slot_index] = &input;
    return *this;
  }

  Node<T, NumInputs>& DetachInput(size_t slot_index) {
    CheckSlotIndex(slot_index);
    dependencies_[slot_index] = nullptr;
    return *this;
  }

 protected:
  std::array<std::unique_ptr<T>, NumInputs> ExecuteDependencies(
      const ExecutionResultFactory<T>& factory) const {
    std::array<std::unique_ptr<T>, NumInputs> result;
    for (size_t i = 0; i < NumInputs; ++i) {
      if (dependencies_[i] == nullptr) {
        throw std::runtime_error(
            "The graph is incomplete: some nodes are missing inputs!");
      }

      result[i] = dependencies_[i]->Execute(factory);
    }

    return result;
  }

 private:
  void CheckSlotIndex(size_t slot_index) {
    if (slot_index >= NumInputs) {
      throw std::out_of_range("Tried to access slot with index out of range");
    }
  }

  std::array<const Executable<T>*, NumInputs> dependencies_;
};

#endif  // NODE_H
