#pragma once

#include <memory>
#include "figure.hpp"

namespace geometry {

template <Scalar T>
class Trapezoid : public Figure<T> {
 public:
  Trapezoid();
  Trapezoid(const Point<T>& p1, const Point<T>& p2, const Point<T>& p3, const Point<T>& p4);
  Trapezoid(const Trapezoid& other);
  Trapezoid(Trapezoid&& other) noexcept = default;

  Trapezoid& operator=(const Trapezoid& other);
  Trapezoid& operator=(Trapezoid&& other) noexcept = default;
  bool operator==(const Trapezoid& other) const;

  Point<T> GetCenter() const override;
  operator double() const override;
  size_t GetVertexCount() const override;

  template <Scalar U>
  friend std::istream& operator>>(std::istream& is, Trapezoid<U>& trapezoid);

  template <Scalar U>
  friend std::ostream& operator<<(std::ostream& os, const Trapezoid<U>& trapezoid);

 private:
  static constexpr size_t VERTEX_COUNT = 4;
  std::unique_ptr<Point<T>> vertices_[VERTEX_COUNT];
};

}  // namespace geometry

#include "trapezoid.ipp"