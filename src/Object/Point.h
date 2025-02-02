#pragma once

#undef Success // pupupu. There is building error without it, because there is
               // same directive in X11.

#include <../../external/eigen/Eigen/Dense>

namespace renderer::object {
class Point {
public:
  using coordinate_type = float;
  using scale_type = float;
  using transformation_matrix_type = Eigen::Matrix4f;
  using homogeneous_vector_type = Eigen::Vector4f;
  using coordinates_vector_type = Eigen::Vector3f;

  Point() = default;
  Point(const coordinates_vector_type &point);
  Point(coordinate_type x, coordinate_type y, coordinate_type z);

  Point &set_coordinates(const coordinates_vector_type &point);
  Point &set_coordinates(coordinate_type x, coordinate_type y,
                         coordinate_type z);

  homogeneous_vector_type get_homogeneous_vector() const;
  coordinates_vector_type get_3D_vector() const;

  Point &transform_with_matrix(
      const transformation_matrix_type &transformation_matrix);
  Point get_transformed_with_matrix(
      const transformation_matrix_type &transformation_matrix) const;

  Point operator+(const Point &rhs) const;
  Point operator-(const Point &rhs) const;
  Point operator*(scale_type scale) const;
  Point operator/(scale_type scale) const;

  Point &operator+=(const Point &rhs);
  Point &operator-=(const Point &rhs);
  Point &operator*=(scale_type scale);
  Point &operator/=(scale_type scale);

private:
  homogeneous_vector_type homogeneous_point_;
};

} // namespace renderer::object
