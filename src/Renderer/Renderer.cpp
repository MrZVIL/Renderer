#include "Renderer.h"
#include <iostream>

namespace renderer {
Renderer::Renderer(Width width, Height height) {
  assert((static_cast<index_type>(width) > 0) && "Invalid image width");
  assert((static_cast<index_type>(height) > 0) && "Invalid image height");
  width_ = static_cast<index_type>(width);
  height_ = static_cast<index_type>(height);
  z_buffer_.resize(width_ * height_, {neg_inf_, -1});
  visited_.resize(width_ * height_, -1);
}

Image Renderer::render(const World &world, const Camera &camera) {
  primitives_container primitives = clipping(world, camera);
  primitives = camera_transformation(primitives, camera);
  primitives = projection_transformation(primitives, camera);
  primitives = viewport_transformation(primitives);
  return rasterization(primitives);
}

Renderer::primitives_container Renderer::clipping(const World &world,
                                                  const Camera &camera) const {
  primitives_container primitives{};
  for (const Object &obj : world.objects()) {
    for (const Triangle &triangle : obj.triangles()) {
      primitives.push_back(triangle);
    }
  }

  return primitives;
}

Renderer::primitives_container &
Renderer::camera_transformation(primitives_container &primitives,
                                const Camera &camera) const {
  Vector3 w = -camera.gaze_dir();
  w.normalize();
  Vector3 u = (camera.view_up_dir()).cross(w);
  u.normalize();
  Vector3 v = w.cross(u);

  Matrix4 rotate_matr = Matrix4::Zero();
  Matrix4 moving_matr = Matrix4::Identity();

  rotate_matr(3, 3) = 1;
  rotate_matr.row(0) << u.transpose(), 0;
  rotate_matr.row(1) << v.transpose(), 0;
  rotate_matr.row(2) << w.transpose(), 0;

  moving_matr.col(3) << -camera.origin(), 1;

  Matrix4 transform_matr = rotate_matr * moving_matr;

  for (Triangle &triangle : primitives) {
    triangle.transform_with_matrix(transform_matr);
  }

  return primitives;
}

Renderer::primitives_container &
Renderer::projection_transformation(primitives_container &primitives,
                                    const Camera &camera) const {
  Matrix4 proj_matr = Matrix4::Zero();
  proj_matr.row(0) << -2 * camera.dist_to_screen() / camera.screen_width(), 0,
      0, 0;
  proj_matr.row(1) << 0, -2 * camera.dist_to_screen() / camera.screen_height(),
      0, 0;
  proj_matr.row(2) << 0, 0, -1, -2 * camera.dist_to_screen();
  proj_matr.row(3) << 0, 0, 1, 0;

  for (Triangle &triangle : primitives) {
    triangle.transform_with_matrix(proj_matr);
  }

  return primitives;
}

Renderer::primitives_container &
Renderer::viewport_transformation(primitives_container &primitives) const {
  Matrix4 vp_matr = Matrix4::Zero();
  vp_matr.row(0) << width_ / 2.0, 0, 0, (width_ - 1) / 2.0;
  vp_matr.row(1) << 0, height_ / 2.0, 0, (height_ - 1) / 2.0;
  vp_matr.row(2) << 0, 0, 1, 0;
  vp_matr.row(3) << 0, 0, 0, 1;

  for (Triangle &triangle : primitives) {
    triangle.transform_with_matrix(vp_matr);
  }

  return primitives;
}

Image Renderer::rasterization(const primitives_container &primitives) {
  Image img{Width(width_), Height(height_)};
  for (size_t index = 0; index < primitives.size(); ++index) {
    update_z_buffer_with_triangle(primitives[index], index);
  }

  for (index_type row = 0; row < height_; ++row) {
    for (index_type col = 0; col < width_; ++col) {
      if (z_buffer_[col * height_ + row].second == -1) {
        continue;
      }
      std::array bc_coords = primitives[z_buffer_[col * height_ + row].second]
                                 .get_barocentric_coordinates({col, row});
      if (primitives[z_buffer_[col * height_ + row].second]
              .is_in_projection_by_baroc_coords(bc_coords)) {
        Color clear_color = primitives[z_buffer_[col * height_ + row].second]
                                .get_color_by_baroc_coords(bc_coords);
        Vector3 normal = primitives[z_buffer_[col * height_ + row].second]
                             .calculate_normal_by_baroc_coords(bc_coords);
        img(col, row) =
            shadeColorByAngle(clear_color, normal,
                              {static_cast<float>(col), static_cast<float>(row),
                               z_buffer_[col * height_ + row].first});
      } else {
        img(col, row) = Color::RGB(0, 0, 0);
      }
    }
  }

  clear_z_buffer();
  return img;
}

void Renderer::update_z_buffer_with_triangle(const Triangle &triangle,
                                             const index_type index) {
  std::array vertexes = triangle.vertexes();
  index_type x_min = static_cast<index_type>(
      std::min({vertexes[0].x(), vertexes[1].x(), vertexes[2].x()}));
  index_type x_max = static_cast<index_type>(
      std::max({vertexes[0].x(), vertexes[1].x(), vertexes[2].x()}));
  index_type y_min = static_cast<index_type>(
      std::min({vertexes[0].y(), vertexes[1].y(), vertexes[2].y()}));
  index_type y_max = static_cast<index_type>(
      std::max({vertexes[0].y(), vertexes[1].y(), vertexes[2].y()}));

  x_min = std::max(x_min, static_cast<index_type>(0));
  y_min = std::max(y_min, static_cast<index_type>(0));

  x_max = std::min(x_max, width_ - 1);
  y_max = std::min(y_max, height_ - 1);

  for (index_type x = x_min; x <= x_max; ++x) {
    for (index_type y = y_min; y <= y_max; ++y) {
      std::array bc_coords = triangle.get_barocentric_coordinates({x, y});
      if (triangle.is_in_projection_by_baroc_coords(bc_coords)) {
        depth_type depth = triangle.z_by_baroc_coords(bc_coords);
        if (depth < 0 && depth > z_buffer_[x * height_ + y].first) {
          z_buffer_[x * height_ + y] = {depth, index};
        }
      }
    }
  }
}

Color Renderer::shadeColorByAngle(Color clear_color, Vector3 normal,
                                  Vector3 point) {
  float cos_a =
      std::sqrt(1 - abs(normal.dot(point) / normal.norm() / point.norm()));
  return clear_color * cos_a;
}

void Renderer::clear_z_buffer() {
  z_buffer_.assign(width_ * height_, {neg_inf_, -1});
}

void Renderer::clear_visited() { visited_.assign(width_ * height_, -1); }
} // namespace renderer
