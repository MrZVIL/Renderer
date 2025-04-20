#pragma once
#include "../Linalg.h"
#include <cassert>
namespace renderer {
class Camera {
public:
  using Point = Vector3;
  using length_type = float;
  using angle_type = float;
  Camera() = default;
  Camera(Point origin, Vector3 gaze_dir, Vector3 view_up_dir,
         length_type dist_to_screen, length_type screen_width,
         length_type screen_height);

  void move_along_local_z(length_type dist);
  void move_along_local_y(length_type dist);
  void move_along_local_x(length_type dist);

  void rotate_along_local_z(angle_type angle);
  void rotate_along_local_y(angle_type angle);
  void rotate_along_local_x(angle_type angle);

  const Point &origin() const;
  const Vector3 &gaze_dir() const;
  const Vector3 &view_up_dir() const;
  const length_type &dist_to_screen() const;
  const length_type &screen_width() const;
  const length_type &screen_height() const;

private:
  Point origin_{0, 0, 0};
  Vector3 gaze_dir_{0, 0, -1};
  Vector3 view_up_dir_{0, 1, 0};
  length_type dist_to_screen_ = 1.0;
  length_type screen_width_ = 1.0;
  length_type screen_height_ = 1.0;
};
} // namespace renderer
