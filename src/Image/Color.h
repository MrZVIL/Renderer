#pragma once
#include "Utils.h"

namespace renderer::image {

class Color {
public:
  using color_value_type = uint8_t;
  using scale_type = float;

  Color() = default;
  Color(color_value_type value);

  Color &set_color(color_value_type new_value);
  color_value_type get_color_value();

  Color operator+(const Color &rhs);
  Color operator-(const Color &rhs);
  Color operator*(scale_type scale);
  Color operator/(scale_type scale);

  Color &operator+=(const Color &rhs);
  Color &operator-=(const Color &rhs);
  Color &operator*=(scale_type scale);
  Color &operator/=(scale_type scale);

private:
  color_value_type value;
};

} // namespace renderer::image
