#pragma once

#include <algorithm>
#include <cstddef>
#include <cstdint>
#include <iterator>


template <class T>
struct State {
  explicit State(size_t size, size_t capacity)
      : arr_(new T[capacity]), size_(size), capacity_(capacity) {}

  State(State &) = delete;
  State(State &&) = delete;
  State &operator=(State &) = delete;
  State &operator=(State &&) = delete;

  ~State() { delete[] arr_; }

  int &RefCount() { return ref_count_; }

  T *Arr() { return arr_; }

  size_t &Size() { return size_; }

  size_t &Capacity() { return capacity_; }

private:
  int ref_count_{1};
  T *arr_;
  size_t size_;
  size_t capacity_;
};

template<class T>
class COWVector {
public:
  COWVector() : state_(new State<T>(0, 0)) {}

  ~COWVector() { DecrementAndClean(state_); }

  COWVector(const COWVector &other) : state_(other.state_) {
    state_->RefCount()++;
  }

  COWVector &operator=(const COWVector &other) {
    if (this != &other) {
      DecrementAndClean(state_);
      state_ = other.state_;
      state_->RefCount()++;
    }
    return *this;
  }

  COWVector(COWVector &&other) noexcept : state_(other.state_) {
    other.state_ = nullptr;
  }

  COWVector &operator=(COWVector &&other) noexcept {
    if (this != &other) {
      DecrementAndClean(state_);
      state_ = other.state_;
      other.state_ = nullptr;
    }
    return *this;
  }

  [[nodiscard]] size_t Size() const { return state_->Size(); }

  void Resize(size_t size) {
    if (size <= state_->Capacity()) {
      state_->Size() = size;
      return;
    }

    const size_t new_capacity = std::max(state_->Capacity() * 2, size);
    auto *new_state =
        new State<T>(size, new_capacity); // NOLINT cppcoreguidelines-owning-memory
    std::copy_n(state_->Arr(), std::min(size, state_->Size()),
                new_state->Arr());
    DecrementAndClean(state_);
    state_ = new_state;
  }

  void PushBack(const T &value) {
    if (state_->Size() == state_->Capacity()) {
      Resize(state_->Size() + 1);
    } else {
      state_->Size()++;
    }
    Set(state_->Size() - 1, value);
  }

  [[nodiscard]] const T &Get(size_t at) const {
    auto *it = std::next(state_->Arr(), static_cast<int64_t>(at));
    return *it;
  }

  [[nodiscard]] const T &Back() const {
    return Get(state_->Size() - 1);
  }

  void Set(size_t at, const T &value) {
    if (state_->RefCount() != 1) {
      auto *new_state = new State<T>(state_->Size(), state_->Capacity());
      std::copy_n(state_->Arr(), state_->Size(), new_state->Arr());
      DecrementAndClean(state_);
      state_ = new_state;
    }
    auto *it = std::next(state_->Arr(), static_cast<int64_t>(at));
    *it = value;
  }

private:
  State<T> *state_;

  static void DecrementAndClean(State<T> *state) {
    if (state != nullptr) {
      state->RefCount()--;
      if (state->RefCount() == 0) {
        delete state; // NOLINT cppcoreguidelines-owning-memory
      }
    }
  }
};
