#pragma once
#include "Color.h"
#include <stdexcept>
#include <string>
#include <vector>

namespace renderer {
enum Width : ssize_t;
enum Height : ssize_t;

class Image {

private:
  using container_type = std::vector<Color>;

public:
  using index_type = ssize_t;

  Image(Width width, Height height);

  Image &clean_image();

  Color &operator()(index_type col, index_type row);
  const Color &operator()(index_type col, index_type row) const;

  index_type get_height() const;
  index_type get_width() const;

private:
  bool are_indices_correct(index_type x, index_type y) const;

  index_type width_;
  index_type height_;
  container_type data_;
};

} // namespace renderer
