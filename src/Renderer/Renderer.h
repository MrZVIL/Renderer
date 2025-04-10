#pragma once
#include "Includes.h"
#include <cmath>

namespace renderer {
class Renderer {
public:
  Renderer(Width width, Height height);

  Image render(const World &world, const Camera &camera);

private:
  using depth_type = float;
  using primitives_container = std::vector<Triangle>;
  using index_type = Image::index_type;

  index_type width_;
  index_type height_;
  static constexpr depth_type neg_inf_ = -1'000'000'000;
  static constexpr std::pair<index_type, index_type> shifts[] = {
      {1, 0}, {-1, 0}, {0, 1}, {0, -1}};
  std::vector<std::pair<depth_type, index_type>> z_buffer_;
  std::vector<index_type> visited_;

  primitives_container clipping(const World &world, const Camera &camera) const;
  primitives_container &camera_transformation(primitives_container &primitives,
                                              const Camera &camera) const;
  primitives_container &
  projection_transformation(primitives_container &primitives,
                            const Camera &camera) const;
  primitives_container &
  viewport_transformation(primitives_container &primitives) const;

  Image rasterization(const primitives_container &primitives);

  void update_z_buffer_with_triangle(const Triangle &triangle,
                                     index_type index);

  static Color shadeColorByAngle(Color clear_color, Vector3 normal,
                                 Vector3 point);

  void clear_z_buffer();
  void clear_visited();
};
} // namespace renderer