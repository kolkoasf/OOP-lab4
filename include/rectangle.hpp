#pragma once

#include <memory>
#include "figure.hpp"

namespace geometry {

template <Scalar T>
class Rectangle : public Figure<T> {
 public:
  Rectangle();
  Rectangle(const Point<T>& p1, const Point<T>& p2, const Point<T>& p3, const Point<T>& p4);
  Rectangle(const Rectangle& other);
  Rectangle(Rectangle&& other) noexcept = default;

  Rectangle& operator=(const Rectangle& other);
  Rectangle& operator=(Rectangle&& other) noexcept = default;
  bool operator==(const Rectangle& other) const;

  Point<T> GetCenter() const override;
  operator double() const override;
  size_t GetVertexCount() const override;

  template <Scalar U>
  friend std::istream& operator>>(std::istream& is, Rectangle<U>& rectangle);

  template <Scalar U>
  friend std::ostream& operator<<(std::ostream& os, const Rectangle<U>& rectangle);

 private:
  static constexpr size_t VERTEX_COUNT = 4;
  std::unique_ptr<Point<T>> vertices_[VERTEX_COUNT];
};

}  // namespace geometry

#include "rectangle.ipp"