#pragma once
#include "Color.h"
#include <tuple>

namespace renderer::image {

class Pixel {
public:
  Pixel() = default;
  Pixel(Color::color_value_type red_value, Color::color_value_type green_value,
        Color::color_value_type blue_value);

  Pixel &set_pixel(Color::color_value_type red_value,
                   Color::color_value_type green_value,
                   Color::color_value_type blue_value);
  Pixel &clean_pixel();

  Pixel operator+(const Pixel &rhs);
  Pixel operator-(const Pixel &rhs);
  Pixel operator*(Color::scale_type scale);
  Pixel operator/(Color::scale_type scale);

  Pixel &operator+=(const Pixel &rhs);
  Pixel &operator-=(const Pixel &rhs);
  Pixel &operator*=(Color::scale_type scale);
  Pixel &operator/=(Color::scale_type scale);

  std::tuple<Color::color_value_type, Color::color_value_type,
             Color::color_value_type>
  as_tuple();

private:
  Color red_, blue_, green_;
};

} // namespace renderer::image
