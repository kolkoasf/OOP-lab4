#pragma once

namespace geometry {

template <Scalar T>
Square<T>::Square() {
  for (size_t i = 0; i < VERTEX_COUNT; ++i) {
    vertices_[i] = std::make_unique<Point<T>>();
  }
}

template <Scalar T>
Square<T>::Square(const Point<T>& p1, const Point<T>& p2, const Point<T>& p3, const Point<T>& p4) {
  vertices_[0] = std::make_unique<Point<T>>(p1);
  vertices_[1] = std::make_unique<Point<T>>(p2);
  vertices_[2] = std::make_unique<Point<T>>(p3);
  vertices_[3] = std::make_unique<Point<T>>(p4);
}

template <Scalar T>
Square<T>::Square(const Square& other) {
  for (size_t i = 0; i < VERTEX_COUNT; ++i) {
    vertices_[i] = std::make_unique<Point<T>>(*other.vertices_[i]);
  }
}

template <Scalar T>
Square<T>& Square<T>::operator=(const Square& other) {
  if (this != &other) {
    for (size_t i = 0; i < VERTEX_COUNT; ++i) {
      vertices_[i] = std::make_unique<Point<T>>(*other.vertices_[i]);
    }
  }
  return *this;
}

template <Scalar T>
bool Square<T>::operator==(const Square& other) const {
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
size_t Square<T>::GetVertexCount() const {
  return VERTEX_COUNT;
}

template <Scalar T>
Point<T> Square<T>::GetCenter() const {
  return Figure<T>::CalculateCenter(vertices_, VERTEX_COUNT);
}

template <Scalar T>
Square<T>::operator double() const {
  double side = vertices_[0]->DistanceTo(*vertices_[1]);
  return side * side;
}

template <Scalar T>
std::istream& operator>>(std::istream& is, Square<T>& square) {
  for (size_t i = 0; i < square.VERTEX_COUNT; ++i) {
    is >> *square.vertices_[i];
  }
  return is;
}

template <Scalar T>
std::ostream& operator<<(std::ostream& os, const Square<T>& square) {
  for (size_t i = 0; i < square.VERTEX_COUNT; ++i) {
    os << *square.vertices_[i];
    if (i < square.VERTEX_COUNT - 1) {
      os << " ";
    }
  }
  return os;
}

}  // namespace geometry
