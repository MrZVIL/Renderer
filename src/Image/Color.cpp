#include "Color.h"

namespace renderer {
Color Color::RGB(base_color_type red, base_color_type green,
                 base_color_type blue) {
  Color color;
  color.red_ = red;
  color.green_ = green;
  color.blue_ = blue;
  return color;
}

Color &Color::set_rgb(base_color_type red, base_color_type green,
                      base_color_type blue) {
  red_ = red;
  green_ = green;
  blue_ = blue;

  return *this;
}

Color::base_color_type Color::sum_base_colors(base_color_type c1,
                                              base_color_type c2) {
  base_color_type new_bc = 0;
  if (std::numeric_limits<base_color_type>::max() - c1 >= c2) {
    new_bc = c1 + c2;
  } else {
    new_bc = std::numeric_limits<base_color_type>::max();
  }

  return new_bc;
}

Color::base_color_type Color::prod_base_color(base_color_type c,
                                              scale_type scale) {
  assert((scale >= 0) && "Invalid scale: less than zero");
  assert((scale <= 1) && "Invalid scale: more than one");

  base_color_type new_bc = scale * c;
  return new_bc;
}

Color Color::operator+(const Color &rhs) const {
  base_color_type new_red = sum_base_colors(red_, rhs.red_);
  base_color_type new_green = sum_base_colors(green_, rhs.green_);
  base_color_type new_blue = sum_base_colors(blue_, rhs.blue_);

  return RGB(new_red, new_green, new_blue);
}

Color Color::operator*(const scale_type scale) const {
  base_color_type new_red = prod_base_color(red_, scale);
  base_color_type new_green = prod_base_color(green_, scale);
  base_color_type new_blue = prod_base_color(blue_, scale);

  return RGB(new_red, new_green, new_blue);
}

Color &Color::operator+=(const Color &rhs) {
  red_ = sum_base_colors(red_, rhs.red_);
  green_ = sum_base_colors(green_, rhs.green_);
  blue_ = sum_base_colors(blue_, rhs.blue_);

  return *this;
}

Color &Color::operator*=(const scale_type scale) {
  red_ = prod_base_color(red_, scale);
  green_ = prod_base_color(green_, scale);
  blue_ = prod_base_color(blue_, scale);

  return *this;
}

Color::base_color_type &Color::red() { return red_; }
Color::base_color_type Color::red() const { return red_; }
Color::base_color_type &Color::green() { return green_; }
Color::base_color_type Color::green() const { return green_; }
Color::base_color_type &Color::blue() { return blue_; }
Color::base_color_type Color::blue() const { return blue_; }
} // namespace renderer
