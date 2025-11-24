#pragma once

#include <cmath>

namespace geometry {

template <Scalar T>
Point<T>::Point() : x(T()), y(T()) {
}

template <Scalar T>
Point<T>::Point(T x, T y) : x(x), y(y) {
}

template <Scalar T>
bool Point<T>::operator==(const Point& other) const {
  if constexpr (std::is_floating_point_v<T>) {
    return std::abs(x - other.x) < EPSILON && std::abs(y - other.y) < EPSILON;
  } else {
    return x == other.x && y == other.y;
  }
}

template <Scalar T>
bool Point<T>::operator!=(const Point& other) const {
  return !(*this == other);
}

template <Scalar T>
double Point<T>::DistanceTo(const Point& other) const {
  double dx = static_cast<double>(x - other.x);
  double dy = static_cast<double>(y - other.y);
  return std::sqrt(dx * dx + dy * dy);
}

template <Scalar T>
std::istream& operator>>(std::istream& is, Point<T>& point) {
  is >> point.x >> point.y;
  return is;
}

template <Scalar T>
std::ostream& operator<<(std::ostream& os, const Point<T>& point) {
  os << "(" << point.x << ", " << point.y << ")";
  return os;
}

}  // namespace geometry
