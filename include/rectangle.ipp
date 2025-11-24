#pragma once

namespace geometry {

template <Scalar T>
Rectangle<T>::Rectangle() {
  for (size_t i = 0; i < VERTEX_COUNT; ++i) {
    vertices_[i] = std::make_unique<Point<T>>();
  }
}

template <Scalar T>
Rectangle<T>::Rectangle(const Point<T>& p1, const Point<T>& p2, const Point<T>& p3,
                        const Point<T>& p4) {
  vertices_[0] = std::make_unique<Point<T>>(p1);
  vertices_[1] = std::make_unique<Point<T>>(p2);
  vertices_[2] = std::make_unique<Point<T>>(p3);
  vertices_[3] = std::make_unique<Point<T>>(p4);
}

template <Scalar T>
Rectangle<T>::Rectangle(const Rectangle& other) {
  for (size_t i = 0; i < VERTEX_COUNT; ++i) {
    vertices_[i] = std::make_unique<Point<T>>(*other.vertices_[i]);
  }
}

template <Scalar T>
Rectangle<T>& Rectangle<T>::operator=(const Rectangle& other) {
  if (this != &other) {
    for (size_t i = 0; i < VERTEX_COUNT; ++i) {
      vertices_[i] = std::make_unique<Point<T>>(*other.vertices_[i]);
    }
  }
  return *this;
}

template <Scalar T>
bool Rectangle<T>::operator==(const Rectangle& other) const {
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
size_t Rectangle<T>::GetVertexCount() const {
  return VERTEX_COUNT;
}

template <Scalar T>
Point<T> Rectangle<T>::GetCenter() const {
  return Figure<T>::CalculateCenter(vertices_, VERTEX_COUNT);
}

template <Scalar T>
Rectangle<T>::operator double() const {
  double side1 = vertices_[0]->DistanceTo(*vertices_[1]);
  double side2 = vertices_[1]->DistanceTo(*vertices_[2]);
  return side1 * side2;
}

template <Scalar T>
std::istream& operator>>(std::istream& is, Rectangle<T>& rectangle) {
  for (size_t i = 0; i < rectangle.VERTEX_COUNT; ++i) {
    is >> *rectangle.vertices_[i];
  }
  return is;
}

template <Scalar T>
std::ostream& operator<<(std::ostream& os, const Rectangle<T>& rectangle) {
  for (size_t i = 0; i < rectangle.VERTEX_COUNT; ++i) {
    os << *rectangle.vertices_[i];
    if (i < rectangle.VERTEX_COUNT - 1) {
      os << " ";
    }
  }
  return os;
}

}  // namespace geometry