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

  gaze_dir_ = gaze_dir.normalized();
  view_up_dir_ =
      (view_up_dir - gaze_dir_ * gaze_dir_.dot(view_up_dir)).normalized();
  dist_to_screen_ = dist_to_screen;
  screen_height_ = screen_height;
  screen_width_ = screen_width;
}

void Camera::move_along_local_z(length_type dist) {
  origin_ += gaze_dir_ * dist;
}

void Camera::move_along_local_y(length_type dist) {
  origin_ += view_up_dir_ * dist;
}

void Camera::move_along_local_x(length_type dist) {
  origin_ += gaze_dir_.cross(view_up_dir_).normalized() * dist;
}

void Camera::rotate_along_local_z(angle_type angle) {
  Rotation rotation(angle, gaze_dir_);
  view_up_dir_ = rotation * view_up_dir_;
  view_up_dir_.normalize();
}
void Camera::rotate_along_local_y(angle_type angle) {
  Rotation rotation(angle, view_up_dir_);
  gaze_dir_ = rotation * gaze_dir_;
  gaze_dir_.normalize();
}
void Camera::rotate_along_local_x(angle_type angle) {
  Rotation rotation(angle, gaze_dir_.cross(view_up_dir_));
  gaze_dir_ = rotation * gaze_dir_;
  gaze_dir_.normalize();
  view_up_dir_ = rotation * view_up_dir_;
  view_up_dir_.normalize();
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
