#pragma once
#include "../Image/Color.h"
#include "../Linalg.h"
#include <array>

namespace renderer {
class Triangle {
public:
  using Point = Vector3;
  Triangle(std::array<Point, 3> vertexes, std::array<Vector3, 3> normals,
           std::array<Color, 3> colors);

  Vector3 calculate_normal_at(Vector2 proj_point) const;
  Color get_color_at(Vector2 proj_point) const;

  Vector3 calculate_normal_by_baroc_coords(
      const std::array<scale_type, 3> &bc_coords) const;
  Color
  get_color_by_baroc_coords(const std::array<scale_type, 3> &bc_coords) const;

  Triangle &transform_with_matrix(const Matrix4 &transformation_matrix);
  Triangle
  get_transformed_with_matrix(const Matrix4 &transformation_matrix) const;

  std::array<scale_type, 3>
  get_barocentric_coordinates(Vector2 proj_point) const;

  bool is_in_projection(Vector2 proj_point) const;
  bool is_in_projection_by_baroc_coords(
      const std::array<scale_type, 3> &bc_coords) const;

  scale_type z_by_proj(Vector2 proj_point) const;
  scale_type
  z_by_baroc_coords(const std::array<scale_type, 3> &bc_coords) const;

  const std::array<Point, 3> &vertexes() const;

private:
  static scale_type area2D(Vector2 ab, Vector2 ac);
  static scale_type cross2D(Vector2 ab, Vector2 ac);

  scale_type f01(Vector2 v) const;
  scale_type f12(Vector2 v) const;
  scale_type f20(Vector2 v) const;

  std::array<Point, 3> vertexes_;
  std::array<Vector3, 3> normals_;
  std::array<Color, 3> colors_;
  static constexpr scale_type eps = 1e-8;
};

} // namespace renderer
