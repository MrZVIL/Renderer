#include "Pixel.h"

namespace renderer::image {
Pixel::Pixel(Color::color_value_type red_value,
             Color::color_value_type green_value,
             Color::color_value_type blue_value)
    : red_(red_value), blue_(blue_value), green_(green_value) {}

Pixel &Pixel::set_pixel(Color::color_value_type red_value,
                        Color::color_value_type green_value,
                        Color::color_value_type blue_value) {
  this->red_.set_color(red_value);
  this->green_.set_color(green_value);
  this->blue_.set_color(blue_value);

  return *this;
}

Pixel &Pixel::clean_pixel() {
  return this->set_pixel(utils::MIN_COLOR_VALUE, utils::MIN_COLOR_VALUE,
                         utils::MIN_COLOR_VALUE);
}

Pixel Pixel::operator+(const Pixel &rhs) {
  Pixel new_pixel(*this);
  new_pixel += rhs;
  return new_pixel;
}

Pixel Pixel::operator-(const Pixel &rhs) {
  Pixel new_pixel(*this);
  new_pixel -= rhs;
  return new_pixel;
}

Pixel Pixel::operator*(Color::scale_type scale) {
  Pixel new_pixel(*this);
  new_pixel *= scale;
  return new_pixel;
}

Pixel Pixel::operator/(Color::scale_type scale) {
  Pixel new_pixel(*this);
  new_pixel /= scale;
  return new_pixel;
}

Pixel &Pixel::operator+=(const Pixel &rhs) {
  this->red_ += rhs.red_;
  this->blue_ += rhs.blue_;
  this->green_ += rhs.green_;
  return *this;
}
Pixel &Pixel::operator-=(const Pixel &rhs) {
  this->red_ -= rhs.red_;
  this->blue_ -= rhs.blue_;
  this->green_ -= rhs.green_;
  return *this;
}
Pixel &Pixel::operator*=(Color::scale_type scale) {
  this->red_ *= scale;
  this->blue_ *= scale;
  this->green_ *= scale;
  return *this;
}
Pixel &Pixel::operator/=(Color::scale_type scale) {
  this->red_ /= scale;
  this->blue_ /= scale;
  this->green_ /= scale;
  return *this;
}

std::tuple<Color::color_value_type, Color::color_value_type,
           Color::color_value_type>
Pixel::as_tuple() {
  return std::make_tuple(red_.get_color_value(), green_.get_color_value(),
                         blue_.get_color_value());
}
} // namespace renderer::image
