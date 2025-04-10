#pragma once
#include "../Linalg.h"
namespace renderer {
class Camera {
public:
  using Point = Vector3;
  using length_type = float;
  Camera() = default;
  Camera(Point origin, Vector3 gaze_dir, Vector3 view_up_dir,
         length_type dist_to_screen, length_type screen_width,
         length_type screen_height);

  const Point &origin() const;
  const Vector3 &gaze_dir() const;
  const Vector3 &view_up_dir() const;
  const length_type &dist_to_screen() const;
  const length_type &screen_width() const;
  const length_type &screen_height() const;

  // TODO: Methods to move camera

private:
  Point origin_{0, 0, 0};
  Vector3 gaze_dir_{0, 0, -1};
  Vector3 view_up_dir_{0, 1, 0};
  length_type dist_to_screen_ = 1.0;
  length_type screen_width_ = 1.0;
  length_type screen_height_ = 1.0;
};
} // namespace renderer