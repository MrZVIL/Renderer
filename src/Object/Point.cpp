#include "Point.h"

namespace renderer::object {
Point::Point(const coordinates_vector_type &point) : homogeneous_point_() {
  homogeneous_point_[0] = point[0];
  homogeneous_point_[1] = point[1];
  homogeneous_point_[2] = point[2];
  homogeneous_point_[3] = 1;
}
Point::Point(coordinate_type x, coordinate_type y, coordinate_type z)
    : homogeneous_point_() {
  homogeneous_point_[0] = x;
  homogeneous_point_[1] = y;
  homogeneous_point_[2] = z;
  homogeneous_point_[3] = 1;
}

Point &Point::set_coordinates(const coordinates_vector_type &point) {
  homogeneous_point_[0] = point[0];
  homogeneous_point_[1] = point[1];
  homogeneous_point_[2] = point[2];
  homogeneous_point_[3] = 1;

  return *this;
}
Point &Point::set_coordinates(coordinate_type x, coordinate_type y,
                              coordinate_type z) {
  homogeneous_point_[0] = x;
  homogeneous_point_[1] = y;
  homogeneous_point_[2] = z;
  homogeneous_point_[3] = 1;

  return *this;
}

Point::homogeneous_vector_type Point::get_homogeneous_vector() const {
  return homogeneous_point_;
}

Point::coordinates_vector_type Point::get_3D_vector() const {
  return coordinates_vector_type(homogeneous_point_[0], homogeneous_point_[1],
                                 homogeneous_point_[2]);
}

Point &Point::transform_with_matrix(
    const transformation_matrix_type &transformation_matrix) {
  homogeneous_point_ = transformation_matrix * homogeneous_point_;
  homogeneous_point_[3] = 1;

  return *this;
}

Point Point::get_transformed_with_matrix(
    const transformation_matrix_type &transformation_matrix) const {
  Point new_point = *this;
  new_point.transform_with_matrix(transformation_matrix);

  return new_point;
}

// TODO: check if it works faster with Vector4f
Point Point::operator+(const Point &rhs) const {
  return {this->get_3D_vector() + rhs.get_3D_vector()};
}
Point Point::operator-(const Point &rhs) const {
  return {this->get_3D_vector() - rhs.get_3D_vector()};
}
Point Point::operator*(scale_type scale) const {
  return {this->get_3D_vector() * scale};
}
Point Point::operator/(scale_type scale) const {
  return {this->get_3D_vector() / scale};
}

Point &Point::operator+=(const Point &rhs) {
  this->homogeneous_point_ += rhs.homogeneous_point_;
  this->homogeneous_point_[3] = 1;

  return *this;
}
Point &Point::operator-=(const Point &rhs) {
  this->homogeneous_point_ -= rhs.homogeneous_point_;
  this->homogeneous_point_[3] = 1;

  return *this;
}
Point &Point::operator*=(scale_type scale) {
  this->homogeneous_point_ *= scale;
  this->homogeneous_point_[3] = 1;

  return *this;
}
Point &Point::operator/=(scale_type scale) {
  this->homogeneous_point_ /= scale;
  this->homogeneous_point_[3] = 1;

  return *this;
}

} // namespace renderer::object
