#pragma once
#include "PrimitiveColor.h"
#include <tuple>

namespace renderer::image {

class Color {
public:
  Color() = default;
  Color(PrimitiveColor::primitive_color_value_type red_value,
        PrimitiveColor::primitive_color_value_type green_value,
        PrimitiveColor::primitive_color_value_type blue_value);

  Color &set_color(PrimitiveColor::primitive_color_value_type red_value,
                   PrimitiveColor::primitive_color_value_type green_value,
                   PrimitiveColor::primitive_color_value_type blue_value);
  Color &clean_color();

  Color operator+(const Color &rhs);
  Color operator-(const Color &rhs);
  Color operator*(PrimitiveColor::scale_type scale);
  Color operator/(PrimitiveColor::scale_type scale);

  Color &operator+=(const Color &rhs);
  Color &operator-=(const Color &rhs);
  Color &operator*=(PrimitiveColor::scale_type scale);
  Color &operator/=(PrimitiveColor::scale_type scale);

  std::tuple<PrimitiveColor::primitive_color_value_type,
             PrimitiveColor::primitive_color_value_type,
             PrimitiveColor::primitive_color_value_type>
  as_tuple();

private:
  PrimitiveColor red_, blue_, green_;
};

} // namespace renderer::image
