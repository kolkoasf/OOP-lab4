#pragma once

#include <memory>
#include "figure.hpp"

namespace geometry {

template <Scalar T>
class Rhombus : public Figure<T> {
 public:
  Rhombus();
  Rhombus(const Point<T>& p1, const Point<T>& p2, const Point<T>& p3, const Point<T>& p4);
  Rhombus(const Rhombus& other);
  Rhombus(Rhombus&& other) noexcept = default;

  Rhombus& operator=(const Rhombus& other);
  Rhombus& operator=(Rhombus&& other) noexcept = default;
  bool operator==(const Rhombus& other) const;

  Point<T> GetCenter() const override;
  operator double() const override;
  size_t GetVertexCount() const override;

  template <Scalar U>
  friend std::istream& operator>>(std::istream& is, Rhombus<U>& rhombus);

  template <Scalar U>
  friend std::ostream& operator<<(std::ostream& os, const Rhombus<U>& rhombus);

 private:
  static constexpr size_t VERTEX_COUNT = 4;
  std::unique_ptr<Point<T>> vertices_[VERTEX_COUNT];
};

}  // namespace geometry

#include "rhombus.ipp"