#pragma once
#include "../../external/CImg/CImg.h"
#include "Color.h"
#include <stdexcept>
#include <string>
#include <vector>

namespace renderer::image {
class Image {
public:
  using matrix_type = std::vector<std::vector<Color>>;
  using size_type = size_t;

  Image() = default;
  Image(size_type width, size_type height);

  void output_image_to_bmp(char *path);
  Image &clean_image();
  Image &set_pixel(size_type column, size_type row, Color new_pixel);
  Image &set_pixel(size_type column, size_type row,
                   PrimitiveColor::primitive_color_value_type red_value,
                   PrimitiveColor::primitive_color_value_type green_value,
                   PrimitiveColor::primitive_color_value_type blue_value);

  size_type get_height();
  size_type get_width();
  Color get_pixel(size_type column, size_type row);

private:
  using row_type = std::vector<Color>;

  void check_height_and_width(size_type x, size_type y);

  size_type width_, height_;
  matrix_type matrix_;
};

} // namespace renderer::image
