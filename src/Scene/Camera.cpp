#include "Camera.h"

namespace renderer {
Camera::Camera(Point origin, Vector3 gaze_dir, Vector3 view_up_dir,
               length_type dist_to_screen, length_type screen_width,
               length_type screen_height)
    : origin_(origin) {
  assert((!gaze_dir.cross(view_up_dir).isZero()) &&
         "Invalid gaze and view-up directions: should not be collinear");
  assert((dist_to_screen > 0) &&
         "Invalid distance to screen: should be positive");
  assert((screen_width > 0) && "Invalid screen width: should be positive");
  assert((screen_height > 0) && "Invalid screen heigth: should be positive");

  gaze_dir_ = gaze_dir;
  view_up_dir_ = view_up_dir;
  dist_to_screen_ = dist_to_screen;
  screen_height_ = screen_height;
  screen_width_ = screen_width;
}

const Camera::Point &Camera::origin() const { return origin_; }
const Vector3 &Camera::gaze_dir() const { return gaze_dir_; }
const Vector3 &Camera::view_up_dir() const { return view_up_dir_; }
const Camera::length_type &Camera::dist_to_screen() const {
  return dist_to_screen_;
}
const Camera::length_type &Camera::screen_width() const {
  return screen_width_;
}
const Camera::length_type &Camera::screen_height() const {
  return screen_height_;
}

} // namespace renderer
