#pragma once

#include <stdexcept>
#include <utility>

namespace geometry {

template <typename T>
FigureArray<T>::FigureArray() : sz_(0), capacity_(0), data_(nullptr) {
}

template <typename T>
FigureArray<T>::FigureArray(FigureArray&& other) noexcept
    : sz_(other.sz_), capacity_(other.capacity_), data_(std::move(other.data_)) {
  other.sz_ = 0;
  other.capacity_ = 0;
}

template <typename T>
FigureArray<T>& FigureArray<T>::operator=(FigureArray&& other) noexcept {
  if (this != &other) {
    data_.reset();
    sz_ = other.sz_;
    capacity_ = other.capacity_;
    data_ = std::move(other.data_);
    other.sz_ = 0;
    other.capacity_ = 0;
  }
  return *this;
}

template <typename T>
FigureArray<T>::~FigureArray() {
  data_.reset();
  capacity_ = 0;
}

template <typename T>
void FigureArray<T>::Insert(size_t pos, const T& figure) {
  if (pos > sz_) {
    throw std::out_of_range("Insert position out of range");
  }

  if (sz_ == capacity_) {
    size_t new_capacity;
    if (capacity_ == 0) {
      new_capacity = INIT_CAPACITY;
    } else {
      new_capacity = capacity_ * 2;
    }
    Reserve(new_capacity);
  }

  for (size_t i = sz_; i > pos; --i) {
    data_[i] = std::move(data_[i - 1]);
  }

  data_[pos] = figure;
  ++sz_;
}

template <typename T>
void FigureArray<T>::Insert(size_t pos, T&& figure) {
  if (pos > sz_) {
    throw std::out_of_range("Insert position out of range");
  }

  if (sz_ == capacity_) {
    size_t new_capacity;
    if (capacity_ == 0) {
      new_capacity = INIT_CAPACITY;
    } else {
      new_capacity = capacity_ * 2;
    }
    Reserve(new_capacity);
  }

  for (size_t i = sz_; i > pos; --i) {
    data_[i] = std::move(data_[i - 1]);
  }

  data_[pos] = std::move(figure);
  ++sz_;
}

template <typename T>
void FigureArray<T>::PushBack(const T& figure) {
  Insert(sz_, figure);
}

template <typename T>
void FigureArray<T>::PushBack(T&& figure) {
  Insert(sz_, std::move(figure));
}

template <typename T>
void FigureArray<T>::Erase(size_t index) {
  if (index >= sz_) {
    throw std::out_of_range("Index out of range");
  }

  for (size_t i = index; i < sz_ - 1; ++i) {
    data_[i] = std::move(data_[i + 1]);
  }

  --sz_;
}

template <typename T>
size_t FigureArray<T>::Size() const {
  return sz_;
}

template <typename T>
bool FigureArray<T>::Empty() const {
  return sz_ == 0;
}

template <typename T>
T& FigureArray<T>::operator[](size_t index) {
  if (index >= sz_) {
    throw std::out_of_range("Index out of range");
  }
  return data_[index];
}

template <typename T>
const T& FigureArray<T>::operator[](size_t index) const {
  if (index >= sz_) {
    throw std::out_of_range("Index out of range");
  }
  return data_[index];
}

template <typename T>
bool FigureArray<T>::operator==(const FigureArray& other) const {
  if (sz_ != other.sz_) {
    return false;
  }
  for (size_t i = 0; i < sz_; ++i) {
    if (!(data_[i] == other.data_[i])) {
      return false;
    }
  }
  return true;
}

template <typename T>
bool FigureArray<T>::operator!=(const FigureArray& other) const {
  return !(*this == other);
}

template <typename T>
void FigureArray<T>::Clear() {
  sz_ = 0;
}

template <typename T>
void FigureArray<T>::Reserve(size_t new_capacity) {
  if (new_capacity <= capacity_) {
    return;
  }

  std::shared_ptr<T[]> new_data(new T[new_capacity]);

  for (size_t i = 0; i < sz_; ++i) {
    new_data[i] = std::move(data_[i]);
  }

  data_ = new_data;
  capacity_ = new_capacity;
}

template <typename T>
double FigureArray<T>::GetTotalArea() const requires HasArea<T> {
  double total = 0.0;
  for (size_t i = 0; i < sz_; ++i) {
    total += static_cast<double>(data_[i]);
  }
  return total;
}

template <typename T>
void FigureArray<T>::PrintAll(std::ostream& os) const {
  for (size_t i = 0; i < sz_; ++i) {
    os << "Element " << i << ": " << data_[i] << " | ";
    os << "Center: " << data_[i].GetCenter() << " | ";
    os << "Area: " << static_cast<double>(data_[i]) << "\n";
  }
}

template <typename U>
std::ostream& operator<<(std::ostream& os, const FigureArray<U>& arr) {
  arr.PrintAll(os);
  return os;
}

}  // namespace geometry
