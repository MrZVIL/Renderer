#pragma once
#include <cassert>
#include <cstdint>
#include <limits>
#include <tuple>

namespace renderer {

class Color {

public:
  using base_color_type = uint8_t;
  using scale_type = float;

  Color() = default;
  static Color RGB(base_color_type red, base_color_type green,
                   base_color_type blue);

  Color &set_rgb(base_color_type red, base_color_type green,
                 base_color_type blue);

  Color operator+(const Color &rhs) const;
  Color operator*(scale_type scale) const;

  Color &operator+=(const Color &rhs);
  Color &operator*=(scale_type scale);

  base_color_type &red();
  base_color_type red() const;
  base_color_type &green();
  base_color_type green() const;
  base_color_type &blue();
  base_color_type blue() const;

private:
  base_color_type red_ = 0;
  base_color_type blue_ = 0;
  base_color_type green_ = 0;

  static base_color_type sum_base_colors(const base_color_type c1,
                                         const base_color_type c2);
  static base_color_type prod_base_color(const base_color_type c,
                                         const scale_type scale);
};

} // namespace renderer
