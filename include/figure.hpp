#pragma once

#include <cstddef>
#include <memory>

#include "point.hpp"

namespace geometry {

template <Scalar T>
class Figure {
 public:
  Figure() = default;
  virtual ~Figure() = default;

  virtual size_t GetVertexCount() const = 0;
  virtual Point<T> GetCenter() const = 0;
  virtual operator double() const = 0;

 protected:
  static Point<T> CalculateCenter(const std::unique_ptr<Point<T>>* points, size_t count) {
    double sum_x = 0.0;
    double sum_y = 0.0;
    for (size_t i = 0; i < count; ++i) {
      sum_x += static_cast<double>(points[i]->x);
      sum_y += static_cast<double>(points[i]->y);
    }
    return Point<T>(static_cast<T>(sum_x / count), static_cast<T>(sum_y / count));
  }
};

}  // namespace geometry