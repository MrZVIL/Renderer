#pragma once
#include "../../external/CImg/CImg.h"
#include "Pixel.h"
#include <stdexcept>
#include <string>
#include <vector>

namespace renderer::image {
class Image {
public:
  using matrix_type = std::vector<std::vector<Pixel>>;
  using size_type = size_t;

  Image() = default;
  Image(size_type width, size_type height);

  void output_image_to_bmp(char *path);
  Image &clean_image();
  Image &set_pixel(size_type column, size_type row, Pixel new_pixel);
  Image &set_pixel(size_type column, size_type row,
                   Color::color_value_type red_value,
                   Color::color_value_type green_value,
                   Color::color_value_type blue_value);

  size_type get_height();
  size_type get_width();
  Pixel get_pixel(size_type column, size_type row);

private:
  using row_type = std::vector<Pixel>;

  void check_height_and_width(size_type x, size_type y);

  size_type width_, height_;
  matrix_type matrix_;
};

} // namespace renderer::image
