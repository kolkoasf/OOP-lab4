#pragma once

namespace geometry {

template <Scalar T>
Trapezoid<T>::Trapezoid() {
  for (size_t i = 0; i < VERTEX_COUNT; ++i) {
    vertices_[i] = std::make_unique<Point<T>>();
  }
}

template <Scalar T>
Trapezoid<T>::Trapezoid(const Point<T>& p1, const Point<T>& p2, const Point<T>& p3,
                        const Point<T>& p4) {
  vertices_[0] = std::make_unique<Point<T>>(p1);
  vertices_[1] = std::make_unique<Point<T>>(p2);
  vertices_[2] = std::make_unique<Point<T>>(p3);
  vertices_[3] = std::make_unique<Point<T>>(p4);
}

template <Scalar T>
Trapezoid<T>::Trapezoid(const Trapezoid& other) {
  for (size_t i = 0; i < VERTEX_COUNT; ++i) {
    vertices_[i] = std::make_unique<Point<T>>(*other.vertices_[i]);
  }
}

template <Scalar T>
Trapezoid<T>& Trapezoid<T>::operator=(const Trapezoid& other) {
  if (this != &other) {
    for (size_t i = 0; i < VERTEX_COUNT; ++i) {
      vertices_[i] = std::make_unique<Point<T>>(*other.vertices_[i]);
    }
  }
  return *this;
}

template <Scalar T>
bool Trapezoid<T>::operator==(const Trapezoid& other) const {
  if (GetVertexCount() != other.GetVertexCount()) {
    return false;
  }
  for (size_t i = 0; i < VERTEX_COUNT; ++i) {
    if (*vertices_[i] != *other.vertices_[i]) {
      return false;
    }
  }
  return true;
}

template <Scalar T>
size_t Trapezoid<T>::GetVertexCount() const {
  return VERTEX_COUNT;
}

template <Scalar T>
Point<T> Trapezoid<T>::GetCenter() const {
  return Figure<T>::CalculateCenter(vertices_, VERTEX_COUNT);
}

template <Scalar T>
Trapezoid<T>::operator double() const {
  T x1 = vertices_[0]->x;
  T x2 = vertices_[1]->x;
  T x3 = vertices_[2]->x;
  T x4 = vertices_[3]->x;
  T y1 = vertices_[0]->y;
  T y2 = vertices_[1]->y;
  T y3 = vertices_[2]->y;
  T y4 = vertices_[3]->y;

  double area = 0.5 * std::abs((x1 * y2 + x2 * y3 + x3 * y4 + x4 * y1) -
                               (y1 * x2 + y2 * x3 + y3 * x4 + y4 * x1));
  return area;
}

template <Scalar T>
std::istream& operator>>(std::istream& is, Trapezoid<T>& trapezoid) {
  for (size_t i = 0; i < trapezoid.VERTEX_COUNT; ++i) {
    is >> *trapezoid.vertices_[i];
  }
  return is;
}

template <Scalar T>
std::ostream& operator<<(std::ostream& os, const Trapezoid<T>& trapezoid) {
  for (size_t i = 0; i < trapezoid.VERTEX_COUNT; ++i) {
    os << *trapezoid.vertices_[i];
    if (i < trapezoid.VERTEX_COUNT - 1) {
      os << " ";
    }
  }
  return os;
}

}  // namespace geometry