#include "Image.h"

namespace renderer::image {
Image::Image(size_type width, size_type height)
    : width_(width), height_(height), matrix_(height, row_type(width)) {}

Image &Image::clean_image() {
  for (size_type i = 0; i < height_; ++i)
    for (size_type j = 0; j < width_; ++j) {
      matrix_[i][j].clean_pixel();
    }

  return *this;
}

Image &Image::set_pixel(size_type column, size_type row, Pixel new_pixel) {
  check_height_and_width(row, column);
  matrix_[row][column] = new_pixel;

  return *this;
}

Image &Image::set_pixel(size_type column, size_type row,
                        Color::color_value_type red_value,
                        Color::color_value_type blue_value,
                        Color::color_value_type green_value) {
  check_height_and_width(row, column);
  matrix_[row][column].set_pixel(red_value, blue_value, green_value);

  return *this;
}

Image::size_type Image::get_height() { return this->height_; }
Image::size_type Image::get_width() { return this->width_; }

Pixel Image::get_pixel(size_type column, size_type row) {
  check_height_and_width(row, column);
  return this->matrix_[row][column];
}

void Image::output_image_to_bmp(char *path) {
  using namespace cimg_library;

  CImg<Color::color_value_type> output_image(width_, height_, 1, 3, 0);
  for (size_type i = 0; i < height_; ++i)
    for (size_type j = 0; j < width_; ++j) {
      std::tuple pixel_as_tuple = matrix_[i][j].as_tuple();
      output_image(j, i, 0) = std::get<0>(pixel_as_tuple);
      output_image(j, i, 1) = std::get<1>(pixel_as_tuple);
      output_image(j, i, 2) = std::get<2>(pixel_as_tuple);
    }

  output_image.save(path);
}

void Image::check_height_and_width(size_type x, size_type y) {
  if (x >= height_ || y >= width_) {
    throw std::invalid_argument(std::string("Invalid pixel coordinates: (") +
                                std::to_string(x) + std::string(", ") +
                                std::to_string(y) + std::string(")"));
  }
}
} // namespace renderer::image
