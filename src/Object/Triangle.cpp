#include "Triangle.h"

namespace renderer::object {
Triangle::Triangle(Point first_point, Point second_point, Point third_point,
                   image::Color average_color)
    : vertexes_(first_point, second_point, third_point),
      average_color_(average_color) {}

Triangle::coordinates_vector_type Triangle::calculate_normal() const {
  return (get<0>(vertexes_).get_3D_vector() - get<1>(vertexes_).get_3D_vector())
      .cross(get<0>(vertexes_).get_3D_vector() -
             get<2>(vertexes_).get_3D_vector());
}
image::Color Triangle::get_average_color() const { return average_color_; }

Triangle &Triangle::transform_with_matrix(
    const transformation_matrix_type &transformation_matrix) {
  get<0>(vertexes_).transform_with_matrix(transformation_matrix);
  get<1>(vertexes_).transform_with_matrix(transformation_matrix);
  get<2>(vertexes_).transform_with_matrix(transformation_matrix);

  return *this;
}
Triangle Triangle::get_transformed_with_matrix(
    const transformation_matrix_type &transformation_matrix) const {
  Triangle new_triangle = *this;
  new_triangle.transform_with_matrix(transformation_matrix);

  return new_triangle;
}
} // namespace renderer::object
