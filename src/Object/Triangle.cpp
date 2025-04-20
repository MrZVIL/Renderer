#include "Triangle.h"

namespace renderer {
Triangle::Triangle(std::array<Point, 3> vertexes,
                   std::array<Vector3, 3> normals, std::array<Color, 3> colors)
    : vertexes_(vertexes), normals_(normals), colors_(colors) {}

Vector3 Triangle::calculate_normal_at(Vector2 proj_point) const {
  std::array<scale_type, 3> bc_coords = get_barocentric_coordinates(proj_point);

  if (!is_in_projection_by_baroc_coords(bc_coords)) {
    return {0, 0, 0};
  }

  Vector3 normal = normals_[0] * bc_coords[0] + normals_[1] * bc_coords[1] +
                   normals_[2] * bc_coords[2];
  return normal;
}

Color Triangle::get_color_at(Vector2 proj_point) const {
  std::array<scale_type, 3> bc_coords = get_barocentric_coordinates(proj_point);

  if (!is_in_projection_by_baroc_coords(bc_coords)) {
    return Color::RGB(0, 0, 0);
  }

  Color color = colors_[0] * bc_coords[0] + colors_[1] * bc_coords[1] +
                colors_[2] * bc_coords[2];
  return color;
}

Vector3 Triangle::calculate_normal_by_baroc_coords(
    const std::array<scale_type, 3> &bc_coords) const {
  if (!is_in_projection_by_baroc_coords(bc_coords)) {
    return {0, 0, 0};
  }

  Vector3 normal = normals_[0] * bc_coords[0] + normals_[1] * bc_coords[1] +
                   normals_[2] * bc_coords[2];
  return normal;
}
Color Triangle::get_color_by_baroc_coords(
    const std::array<scale_type, 3> &bc_coords) const {
  if (!is_in_projection_by_baroc_coords(bc_coords)) {
    return Color::RGB(0, 0, 0);
  }

  Color color = colors_[0] * bc_coords[0] + colors_[1] * bc_coords[1] +
                colors_[2] * bc_coords[2];
  return color;
}

Triangle &
Triangle::transform_with_matrix(const Matrix4 &transformation_matrix) {
  for (int i = 0; i < 3; ++i) {
    vertexes_[i] =
        (transformation_matrix * (vertexes_[i]).homogeneous()).hnormalized();
  }

  return *this;
}

Triangle Triangle::get_transformed_with_matrix(
    const Matrix4 &transformation_matrix) const {
  Triangle new_triangle = *this;
  new_triangle.transform_with_matrix(transformation_matrix);

  return new_triangle;
}

bool Triangle::is_in_projection(Vector2 proj_point) const {
  int pos = 0;
  int neg = 0;
  for (int i = 0; i < 3; ++i) {
    scale_type cr = cross2D(vertexes_[i].head(2) - proj_point,
                            (vertexes_[i] - vertexes_[(i + 1) % 3]).head(2));
    if (cr > eps) {
      ++pos;
    } else if (cr < -eps) {
      ++neg;
    }
  }

  return (pos == 0) || (neg == 0);
}

bool Triangle::is_in_projection_by_baroc_coords(
    const std::array<scale_type, 3> &bc_coords) const {
  return (bc_coords[0] > 0 && bc_coords[1] > 0 && bc_coords[2] > 0) &&
         (bc_coords[0] <= 1 && bc_coords[1] <= 1 && bc_coords[2] <= 1);
}

scale_type Triangle::z_by_proj(Vector2 proj_point) const {
  std::array<scale_type, 3> bc_coords = get_barocentric_coordinates(proj_point);

  if (!is_in_projection_by_baroc_coords(bc_coords)) {
    return 0;
  }
  Point p = vertexes_[0] * bc_coords[0] + vertexes_[1] * bc_coords[1] +
            vertexes_[2] * bc_coords[2];
  return p[2];
}

scale_type
Triangle::z_by_baroc_coords(const std::array<scale_type, 3> &bc_coords) const {
  if (!is_in_projection_by_baroc_coords(bc_coords)) {
    return 0;
  }
  Point p = vertexes_[0] * bc_coords[0] + vertexes_[1] * bc_coords[1] +
            vertexes_[2] * bc_coords[2];
  return p[2];
}

const std::array<Triangle::Point, 3> &Triangle::vertexes() const {
  return vertexes_;
}

float Triangle::area2D(Vector2 ab, Vector2 ac) {
  return abs(cross2D(ab, ac)) / 2;
}

float Triangle::cross2D(Vector2 ab, Vector2 ac) {
  return ab[0] * ac[1] - ab[1] * ac[0];
}

std::array<scale_type, 3>
Triangle::get_barocentric_coordinates(Vector2 proj_point) const {
  std::array<scale_type, 3> bc_coords{0, 0, 0};
  bc_coords[0] = f12(proj_point) / f12(vertexes_[0].head(2));
  bc_coords[1] = f20(proj_point) / f20(vertexes_[1].head(2));
  bc_coords[2] = f01(proj_point) / f01(vertexes_[2].head(2));
  return bc_coords;
}

scale_type Triangle::f01(Vector2 v) const {
  return (vertexes_[0].y() - vertexes_[1].y()) * v.x() +
         (vertexes_[1].x() - vertexes_[0].x()) * v.y() +
         vertexes_[0].x() * vertexes_[1].y() -
         vertexes_[1].x() * vertexes_[0].y();
}
scale_type Triangle::f12(Vector2 v) const {
  return (vertexes_[1].y() - vertexes_[2].y()) * v.x() +
         (vertexes_[2].x() - vertexes_[1].x()) * v.y() +
         vertexes_[1].x() * vertexes_[2].y() -
         vertexes_[2].x() * vertexes_[1].y();
}
scale_type Triangle::f20(Vector2 v) const {
  return (vertexes_[2].y() - vertexes_[0].y()) * v.x() +
         (vertexes_[0].x() - vertexes_[2].x()) * v.y() +
         vertexes_[2].x() * vertexes_[0].y() -
         vertexes_[0].x() * vertexes_[2].y();
}
} // namespace renderer
