#pragma once

#include <concepts>
#include <iostream>
#include <type_traits>

namespace geometry {

template <typename T>
concept Scalar = std::is_arithmetic_v<T>;

template <Scalar T>
struct Point {
  static constexpr double EPSILON = 1e-9;

  T x;
  T y;

  Point();
  Point(T x, T y);

  bool operator==(const Point& other) const;
  bool operator!=(const Point& other) const;

  double DistanceTo(const Point& other) const;

  template <Scalar U>
  friend std::istream& operator>>(std::istream& is, Point<U>& point);

  template <Scalar U>
  friend std::ostream& operator<<(std::ostream& os, const Point<U>& point);
};

}  // namespace geometry

#include "point.ipp"