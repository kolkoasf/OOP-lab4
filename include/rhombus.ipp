#pragma once

namespace geometry {

template <Scalar T>
Rhombus<T>::Rhombus() {
  for (size_t i = 0; i < VERTEX_COUNT; ++i) {
    vertices_[i] = std::make_unique<Point<T>>();
  }
}

template <Scalar T>
Rhombus<T>::Rhombus(const Point<T>& p1, const Point<T>& p2, const Point<T>& p3,
                    const Point<T>& p4) {
  vertices_[0] = std::make_unique<Point<T>>(p1);
  vertices_[1] = std::make_unique<Point<T>>(p2);
  vertices_[2] = std::make_unique<Point<T>>(p3);
  vertices_[3] = std::make_unique<Point<T>>(p4);
}

template <Scalar T>
Rhombus<T>::Rhombus(const Rhombus& other) {
  for (size_t i = 0; i < VERTEX_COUNT; ++i) {
    vertices_[i] = std::make_unique<Point<T>>(*other.vertices_[i]);
  }
}

template <Scalar T>
Rhombus<T>& Rhombus<T>::operator=(const Rhombus& other) {
  if (this != &other) {
    for (size_t i = 0; i < VERTEX_COUNT; ++i) {
      vertices_[i] = std::make_unique<Point<T>>(*other.vertices_[i]);
    }
  }
  return *this;
}

template <Scalar T>
bool Rhombus<T>::operator==(const Rhombus& other) const {
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
size_t Rhombus<T>::GetVertexCount() const {
  return VERTEX_COUNT;
}

template <Scalar T>
Point<T> Rhombus<T>::GetCenter() const {
  return Figure<T>::CalculateCenter(vertices_, VERTEX_COUNT);
}

template <Scalar T>
Rhombus<T>::operator double() const {
  double d1 = vertices_[0]->DistanceTo(*vertices_[2]);
  double d2 = vertices_[1]->DistanceTo(*vertices_[3]);
  return (d1 * d2) / 2.0;
}

template <Scalar T>
std::istream& operator>>(std::istream& is, Rhombus<T>& rhombus) {
  for (size_t i = 0; i < rhombus.VERTEX_COUNT; ++i) {
    is >> *rhombus.vertices_[i];
  }
  return is;
}

template <Scalar T>
std::ostream& operator<<(std::ostream& os, const Rhombus<T>& rhombus) {
  for (size_t i = 0; i < rhombus.VERTEX_COUNT; ++i) {
    os << *rhombus.vertices_[i];
    if (i < rhombus.VERTEX_COUNT - 1) {
      os << " ";
    }
  }
  return os;
}

}  // namespace geometry
