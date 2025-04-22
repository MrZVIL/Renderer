#include "Image.h"

namespace renderer {
Image::Image(Width width, Height height) {
  assert((static_cast<index_type>(width) > 0) && "Invalid image width");
  assert((static_cast<index_type>(height) > 0) && "Invalid image height");
  width_ = static_cast<index_type>(width);
  height_ = static_cast<index_type>(height);
  data_.resize(width_ * height_);
}

Image &Image::clean_image() {
  for (Color &pixel : data_) {
    pixel.set_rgb(0, 0, 0);
  }

  return *this;
}

Color &Image::operator()(index_type col, index_type row) {
  assert(are_indices_correct(row, col) && "Invalid indices");
  return data_[row * width_ + col];
}
const Color &Image::operator()(index_type col, index_type row) const {
  assert(are_indices_correct(row, col) && "Invalid indices");
  return data_[row * width_ + col];
}

Image::index_type Image::get_height() const { return height_; }
Image::index_type Image::get_width() const { return width_; }

bool Image::are_indices_correct(index_type x, index_type y) const {
  return (0 <= x && x <= height_) && (0 <= y && y <= width_);
}
} // namespace renderer
