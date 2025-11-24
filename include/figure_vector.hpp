#pragma once

#include <concepts>
#include <memory>
#include <ostream>

namespace geometry {

template <typename T>
concept HasArea = requires(T t) {
  { static_cast<double>(t) } -> std::convertible_to<double>;
};

template <typename T>
class FigureArray {
 public:
  FigureArray();
  FigureArray(const FigureArray&) = delete;
  FigureArray& operator=(const FigureArray&) = delete;
  FigureArray(FigureArray&& other) noexcept;
  FigureArray& operator=(FigureArray&& other) noexcept;
  ~FigureArray();

  void Insert(size_t pos, const T& value);
  void Insert(size_t pos, T&& value);
  void PushBack(const T& value);
  void PushBack(T&& value);
  void Erase(size_t index);

  size_t Size() const;
  bool Empty() const;

  T& operator[](size_t index);
  const T& operator[](size_t index) const;

  bool operator==(const FigureArray& other) const;
  bool operator!=(const FigureArray& other) const;

  void Clear();
  void Reserve(size_t new_capacity);

  double GetTotalArea() const requires HasArea<T>;
  void PrintAll(std::ostream& os) const;

  template <typename U>
  friend std::ostream& operator<<(std::ostream& os, const FigureArray<U>& arr);

 private:
  static constexpr size_t INIT_CAPACITY = 4;

  size_t sz_;
  size_t capacity_;
  T* data_;
};

}  // namespace geometry

#include "figure_vector.ipp"