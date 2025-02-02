#include "Color.h"

namespace renderer::image {
Color::Color(PrimitiveColor::primitive_color_value_type red_value,
             PrimitiveColor::primitive_color_value_type green_value,
             PrimitiveColor::primitive_color_value_type blue_value)
    : red_(red_value), blue_(blue_value), green_(green_value) {}

Color &Color::set_color(PrimitiveColor::primitive_color_value_type red_value,
                        PrimitiveColor::primitive_color_value_type green_value,
                        PrimitiveColor::primitive_color_value_type blue_value) {
  this->red_.set_primitive_color(red_value);
  this->green_.set_primitive_color(green_value);
  this->blue_.set_primitive_color(blue_value);

  return *this;
}

Color &Color::clean_color() {
  return this->set_color(utils::MIN_COLOR_VALUE, utils::MIN_COLOR_VALUE,
                         utils::MIN_COLOR_VALUE);
}

Color Color::operator+(const Color &rhs) {
  Color new_color(*this);
  new_color += rhs;
  return new_color;
}

Color Color::operator-(const Color &rhs) {
  Color new_color(*this);
  new_color -= rhs;
  return new_color;
}

Color Color::operator*(PrimitiveColor::scale_type scale) {
  Color new_color(*this);
  new_color *= scale;
  return new_color;
}

Color Color::operator/(PrimitiveColor::scale_type scale) {
  Color new_color(*this);
  new_color /= scale;
  return new_color;
}

Color &Color::operator+=(const Color &rhs) {
  this->red_ += rhs.red_;
  this->blue_ += rhs.blue_;
  this->green_ += rhs.green_;
  return *this;
}
Color &Color::operator-=(const Color &rhs) {
  this->red_ -= rhs.red_;
  this->blue_ -= rhs.blue_;
  this->green_ -= rhs.green_;
  return *this;
}
Color &Color::operator*=(PrimitiveColor::scale_type scale) {
  this->red_ *= scale;
  this->blue_ *= scale;
  this->green_ *= scale;
  return *this;
}
Color &Color::operator/=(PrimitiveColor::scale_type scale) {
  this->red_ /= scale;
  this->blue_ /= scale;
  this->green_ /= scale;
  return *this;
}

std::tuple<PrimitiveColor::primitive_color_value_type,
           PrimitiveColor::primitive_color_value_type,
           PrimitiveColor::primitive_color_value_type>
Color::as_tuple() {
  return std::make_tuple(red_.get_primitive_color_value(),
                         green_.get_primitive_color_value(),
                         blue_.get_primitive_color_value());
}
} // namespace renderer::image
