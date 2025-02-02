#pragma once
#include "Utils.h"

namespace renderer::image {

class PrimitiveColor {
public:
  using primitive_color_value_type = uint8_t;
  using scale_type = float;

  PrimitiveColor() = default;
  PrimitiveColor(primitive_color_value_type value);

  PrimitiveColor &set_primitive_color(primitive_color_value_type new_value);
  primitive_color_value_type get_primitive_color_value();

  PrimitiveColor operator+(const PrimitiveColor &rhs);
  PrimitiveColor operator-(const PrimitiveColor &rhs);
  PrimitiveColor operator*(scale_type scale);
  PrimitiveColor operator/(scale_type scale);

  PrimitiveColor &operator+=(const PrimitiveColor &rhs);
  PrimitiveColor &operator-=(const PrimitiveColor &rhs);
  PrimitiveColor &operator*=(scale_type scale);
  PrimitiveColor &operator/=(scale_type scale);

private:
  primitive_color_value_type value;
};

} // namespace renderer::image
