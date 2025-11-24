#include <gtest/gtest.h>

#include <cmath>
#include <stdexcept>

#include "figure_vector.hpp"
#include "point.hpp"
#include "rectangle.hpp"
#include "rhombus.hpp"
#include "trapezoid.hpp"

using namespace geometry;

class PointTest : public ::testing::Test {
 protected:
  Point<int> p_int{3, 4};
  Point<double> p_dbl{3.0, 4.0};
};

TEST_F(PointTest, DefaultConstructor) {
  Point<int> p;
  EXPECT_EQ(p.x, 0);
  EXPECT_EQ(p.y, 0);
}

TEST_F(PointTest, ParametrizedConstructor) {
  EXPECT_EQ(p_int.x, 3);
  EXPECT_EQ(p_int.y, 4);
}

TEST_F(PointTest, EqualityOperator) {
  Point<int> p1{3, 4};
  Point<int> p2{3, 4};
  Point<int> p3{5, 6};
  EXPECT_EQ(p1, p2);
  EXPECT_NE(p1, p3);
}

TEST_F(PointTest, DistanceTo) {
  Point<int> p1{0, 0};
  Point<int> p2{3, 4};
  double distance = p1.DistanceTo(p2);
  EXPECT_DOUBLE_EQ(distance, 5.0);
}

TEST_F(PointTest, DistanceToSelf) {
  EXPECT_DOUBLE_EQ(p_int.DistanceTo(p_int), 0.0);
}

TEST_F(PointTest, FloatingPointComparison) {
  Point<double> a{1.0, 2.0};
  Point<double> b{1.0 + 1e-10, 2.0 + 1e-10};
  EXPECT_EQ(a, b);
}

TEST(PointEdgeCases, NegativeCoordinates) {
  Point<int> p{-5, -10};
  EXPECT_EQ(p.x, -5);
  EXPECT_EQ(p.y, -10);
}

TEST(PointEdgeCases, ZeroCoordinates) {
  Point<int> p{0, 0};
  EXPECT_EQ(p.x, 0);
  EXPECT_EQ(p.y, 0);
}

class RhombusTest : public ::testing::Test {
 protected:
  Rhombus<int> rh1{Point<int>(0, 2), Point<int>(2, 0), Point<int>(0, -2), Point<int>(-2, 0)};
  Rhombus<int> rh2{Point<int>(0, 2), Point<int>(2, 0), Point<int>(0, -2), Point<int>(-2, 0)};
  Rhombus<int> rh3{Point<int>(1, 3), Point<int>(3, 1), Point<int>(1, -1), Point<int>(-1, 1)};
};

TEST_F(RhombusTest, GetVertexCount) {
  EXPECT_EQ(rh1.GetVertexCount(), 4);
}

TEST_F(RhombusTest, GetArea) {
  double area = static_cast<double>(rh1);
  EXPECT_DOUBLE_EQ(area, 8.0);
}

TEST_F(RhombusTest, GetCenter) {
  Point<int> center = rh1.GetCenter();
  EXPECT_EQ(center.x, 0);
  EXPECT_EQ(center.y, 0);
}

TEST_F(RhombusTest, EqualityOperator) {
  EXPECT_EQ(rh1, rh2);
  EXPECT_NE(rh1, rh3);
}

TEST_F(RhombusTest, MoveSemantics) {
  Rhombus<int> original = rh1;
  Rhombus<int> moved = std::move(original);
  EXPECT_EQ(moved, rh2);
}

TEST(RhombusEdgeCases, UnitRhombus) {
  Rhombus<int> unit{Point<int>(0, 1), Point<int>(1, 0), Point<int>(0, -1), Point<int>(-1, 0)};
  EXPECT_DOUBLE_EQ(static_cast<double>(unit), 2.0);
}

TEST(RhombusEdgeCases, LargeRhombus) {
  Rhombus<int> large{Point<int>(0, 1000), Point<int>(1000, 0), Point<int>(0, -1000),
                     Point<int>(-1000, 0)};
  EXPECT_DOUBLE_EQ(static_cast<double>(large), 2000000.0);
}

class RectangleTest : public ::testing::Test {
 protected:
  Rectangle<int> rect1{Point<int>(0, 0), Point<int>(4, 0), Point<int>(4, 2), Point<int>(0, 2)};
  Rectangle<int> rect2{Point<int>(0, 0), Point<int>(4, 0), Point<int>(4, 2), Point<int>(0, 2)};
  Rectangle<int> rect3{Point<int>(1, 1), Point<int>(5, 1), Point<int>(5, 3), Point<int>(1, 3)};
};

TEST_F(RectangleTest, GetVertexCount) {
  EXPECT_EQ(rect1.GetVertexCount(), 4);
}

TEST_F(RectangleTest, GetArea) {
  double area = static_cast<double>(rect1);
  EXPECT_DOUBLE_EQ(area, 8.0);
}

TEST_F(RectangleTest, GetCenter) {
  Point<int> center = rect1.GetCenter();
  EXPECT_EQ(center.x, 2);
  EXPECT_EQ(center.y, 1);
}

TEST_F(RectangleTest, EqualityOperator) {
  EXPECT_EQ(rect1, rect2);
  EXPECT_NE(rect1, rect3);
}

TEST(RectangleEdgeCases, WideRectangle) {
  Rectangle<int> wide{Point<int>(0, 0), Point<int>(10, 0), Point<int>(10, 1), Point<int>(0, 1)};
  EXPECT_DOUBLE_EQ(static_cast<double>(wide), 10.0);
}

TEST(RectangleEdgeCases, TallRectangle) {
  Rectangle<int> tall{Point<int>(0, 0), Point<int>(1, 0), Point<int>(1, 10), Point<int>(0, 10)};
  EXPECT_DOUBLE_EQ(static_cast<double>(tall), 10.0);
}

class TrapezoidTest : public ::testing::Test {
 protected:
  Trapezoid<int> trap1{Point<int>(0, 0), Point<int>(4, 0), Point<int>(3, 2), Point<int>(1, 2)};
  Trapezoid<int> trap2{Point<int>(0, 0), Point<int>(4, 0), Point<int>(3, 2), Point<int>(1, 2)};
};

TEST_F(TrapezoidTest, GetVertexCount) {
  EXPECT_EQ(trap1.GetVertexCount(), 4);
}

TEST_F(TrapezoidTest, GetArea) {
  double area = static_cast<double>(trap1);
  EXPECT_DOUBLE_EQ(area, 6.0);
}

TEST_F(TrapezoidTest, GetCenter) {
  Point<int> center = trap1.GetCenter();
  EXPECT_EQ(center.x, 2);
  EXPECT_EQ(center.y, 1);
}

TEST_F(TrapezoidTest, EqualityOperator) {
  EXPECT_EQ(trap1, trap2);
}

class ArrayTest : public ::testing::Test {
 protected:
  FigureArray<Rhombus<int>> arr;

  void SetUp() override {
    arr.PushBack(
        Rhombus<int>(Point<int>(0, 2), Point<int>(2, 0), Point<int>(0, -2), Point<int>(-2, 0)));
    arr.PushBack(
        Rhombus<int>(Point<int>(1, 3), Point<int>(3, 1), Point<int>(1, -1), Point<int>(-1, 1)));
  }
};

TEST_F(ArrayTest, Size) {
  EXPECT_EQ(arr.Size(), 2);
}

TEST_F(ArrayTest, Empty) {
  EXPECT_FALSE(arr.Empty());
  FigureArray<Rhombus<int>> empty_arr;
  EXPECT_TRUE(empty_arr.Empty());
}

TEST_F(ArrayTest, PushBack) {
  arr.PushBack(
      Rhombus<int>(Point<int>(0, 1), Point<int>(1, 0), Point<int>(0, -1), Point<int>(-1, 0)));
  EXPECT_EQ(arr.Size(), 3);
}

TEST_F(ArrayTest, Insert) {
  arr.Insert(
      1, Rhombus<int>(Point<int>(0, 5), Point<int>(5, 0), Point<int>(0, -5), Point<int>(-5, 0)));
  EXPECT_EQ(arr.Size(), 3);
}

TEST_F(ArrayTest, InsertAtBeginning) {
  arr.Insert(0, Rhombus<int>(Point<int>(0, 10), Point<int>(10, 0), Point<int>(0, -10),
                             Point<int>(-10, 0)));
  EXPECT_EQ(arr.Size(), 3);
}

TEST_F(ArrayTest, InsertAtEnd) {
  arr.Insert(arr.Size(), Rhombus<int>(Point<int>(0, 10), Point<int>(10, 0), Point<int>(0, -10),
                                      Point<int>(-10, 0)));
  EXPECT_EQ(arr.Size(), 3);
}

TEST_F(ArrayTest, Erase) {
  arr.Erase(0);
  EXPECT_EQ(arr.Size(), 1);
}

TEST_F(ArrayTest, Clear) {
  arr.Clear();
  EXPECT_TRUE(arr.Empty());
  EXPECT_EQ(arr.Size(), 0);
}

TEST_F(ArrayTest, GetTotalArea) {
  double total = arr.GetTotalArea();
  EXPECT_GT(total, 0.0);
  EXPECT_DOUBLE_EQ(total, 16.0);
}

TEST_F(ArrayTest, Reserve) {
  arr.Reserve(10);
  EXPECT_EQ(arr.Size(), 2);
}

TEST_F(ArrayTest, MoveConstructor) {
  FigureArray<Rhombus<int>> arr_copy = std::move(arr);
  EXPECT_EQ(arr_copy.Size(), 2);
  EXPECT_TRUE(arr.Empty());
}

TEST_F(ArrayTest, MoveAssignment) {
  FigureArray<Rhombus<int>> arr2;
  arr2.PushBack(
      Rhombus<int>(Point<int>(0, 1), Point<int>(1, 0), Point<int>(0, -1), Point<int>(-1, 0)));
  arr2 = std::move(arr);
  EXPECT_EQ(arr2.Size(), 2);
}

TEST(ArrayEdgeCases, EmptyArrayArea) {
  FigureArray<Rhombus<int>> empty_arr;
  EXPECT_DOUBLE_EQ(empty_arr.GetTotalArea(), 0.0);
}

TEST(ArrayEdgeCases, SingleElement) {
  FigureArray<Rhombus<int>> arr;
  arr.PushBack(
      Rhombus<int>(Point<int>(0, 5), Point<int>(5, 0), Point<int>(0, -5), Point<int>(-5, 0)));
  EXPECT_EQ(arr.Size(), 1);
  EXPECT_DOUBLE_EQ(arr.GetTotalArea(), 50.0);
}

TEST(ArrayEdgeCases, ManyElements) {
  FigureArray<Rhombus<int>> arr;
  for (int i = 0; i < 100; ++i) {
    arr.PushBack(
        Rhombus<int>(Point<int>(0, 1), Point<int>(1, 0), Point<int>(0, -1), Point<int>(-1, 0)));
  }
  EXPECT_EQ(arr.Size(), 100);
  EXPECT_DOUBLE_EQ(arr.GetTotalArea(), 200.0);
}

TEST(ArrayEdgeCases, OutOfBounds) {
  FigureArray<Rhombus<int>> arr;
  arr.PushBack(
      Rhombus<int>(Point<int>(0, 1), Point<int>(1, 0), Point<int>(0, -1), Point<int>(-1, 0)));
  EXPECT_THROW(arr[10], std::out_of_range);
  EXPECT_THROW(arr.Erase(10), std::out_of_range);
  EXPECT_THROW(arr.Insert(100, Rhombus<int>()), std::out_of_range);
}

TEST(ArrayEdgeCases, InsertAtWrongPosition) {
  FigureArray<Rhombus<int>> arr;
  EXPECT_THROW(arr.Insert(5, Rhombus<int>()), std::out_of_range);
}

TEST(Integration, MixedFigures) {
  FigureArray<Rhombus<int>> rhombuses;
  rhombuses.PushBack(
      Rhombus<int>(Point<int>(0, 2), Point<int>(2, 0), Point<int>(0, -2), Point<int>(-2, 0)));
  EXPECT_EQ(rhombuses.Size(), 1);
  EXPECT_DOUBLE_EQ(static_cast<double>(rhombuses[0]), 8.0);
}

TEST(Integration, SequentialOperations) {
  FigureArray<Rhombus<int>> arr;
  arr.PushBack(
      Rhombus<int>(Point<int>(0, 1), Point<int>(1, 0), Point<int>(0, -1), Point<int>(-1, 0)));
  EXPECT_EQ(arr.Size(), 1);

  arr.Insert(
      0, Rhombus<int>(Point<int>(0, 2), Point<int>(2, 0), Point<int>(0, -2), Point<int>(-2, 0)));
  EXPECT_EQ(arr.Size(), 2);

  arr.Erase(0);
  EXPECT_EQ(arr.Size(), 1);
  EXPECT_DOUBLE_EQ(arr.GetTotalArea(), 2.0);
}

TEST(Integration, AllFiguresHaveValidGeometry) {
  FigureArray<Rhombus<int>> arr;
  for (int i = 0; i < 3; ++i) {
    int d = i + 1;
    arr.PushBack(
        Rhombus<int>(Point<int>(0, d), Point<int>(d, 0), Point<int>(0, -d), Point<int>(-d, 0)));
  }

  for (size_t i = 0; i < arr.Size(); ++i) {
    Point<int> center = arr[i].GetCenter();
    EXPECT_TRUE(std::isfinite(static_cast<double>(center.x)));
    EXPECT_TRUE(std::isfinite(static_cast<double>(center.y)));
    double area = static_cast<double>(arr[i]);
    EXPECT_GT(area, 0.0);
  }
}

int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
