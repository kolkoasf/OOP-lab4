#pragma once

#include <memory>
#include "figure.hpp"

namespace geometry {

template <Scalar T>
class Square : public Figure<T> {
 public:
  Square();
  Square(const Point<T>& p1, const Point<T>& p2, const Point<T>& p3, const Point<T>& p4);
  Square(const Square& other);
  Square(Square&& other) noexcept = default;

  Square& operator=(const Square& other);
  Square& operator=(Square&& other) noexcept = default;
  bool operator==(const Square& other) const;

  Point<T> GetCenter() const override;
  operator double() const override;
  size_t GetVertexCount() const override;

  template <Scalar U>
  friend std::istream& operator>>(std::istream& is, Square<U>& square);

  template <Scalar U>
  friend std::ostream& operator<<(std::ostream& os, const Square<U>& square);

 private:
  static constexpr size_t VERTEX_COUNT = 4;
  std::unique_ptr<Point<T>> vertices_[VERTEX_COUNT];
};

}  // namespace geometry

#include "square.ipp"