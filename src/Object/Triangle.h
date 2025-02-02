#pragma once

#include "../Image/Color.h"
#include "Point.h"
#include <tuple>

namespace renderer::object {
class Triangle {
public:
  using coordinates_vector_type = Point::coordinates_vector_type;
  using transformation_matrix_type = Point::transformation_matrix_type;

  Triangle() = default;
  Triangle(Point first_point, Point second_point, Point third_point,
           image::Color average_color);

  coordinates_vector_type calculate_normal() const;
  image::Color get_average_color() const;

  Triangle &transform_with_matrix(
      const transformation_matrix_type &transformation_matrix);
  Triangle get_transformed_with_matrix(
      const transformation_matrix_type &transformation_matrix) const;

private:
  // TODO: explore the possibility of using pointers instead of values
  std::tuple<Point, Point, Point> vertexes_;
  // TODO: make triangle color less primitive
  image::Color average_color_;
};

} // namespace renderer::object
