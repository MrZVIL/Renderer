#pragma once
#include "Image.h"
#include <array>
#include <cstdint>
#include <fstream>
#include <limits>
#include <string>

namespace renderer {
class BmpWriter {
public:
  explicit BmpWriter(std::string path);
  void write(const Image &image);

private:
  void WriteBMPHeader(unsigned char *bmp_header, size_t size) const;
  void WriteDIBHeader(unsigned char *dib_header, size_t width,
                      size_t height) const;

  static constexpr std::array<size_t, 3> shifts = {8, 16, 24};

  template <typename T> void num_to_bytes(T num, unsigned char *bytes) const {
    *bytes = num;
    for (size_t i = 0; i < shifts.size(); ++i) {
      *(bytes + i + 1) =
          (num >> shifts[i]) & std::numeric_limits<uint8_t>::max();
    }
  }
  size_t get_padding_size(size_t wigth) const;

  std::string path_;

  static constexpr int padding_size = 4;
  static constexpr int bytes_per_pixel = 3;
  static constexpr std::array<char, 2> bmp_signature = {'B', 'M'};
  static constexpr int format_first_position = 0;
  static constexpr int format_second_position = 1;
  static constexpr int file_size_position = 2;
  static constexpr int pixs_array_offset_position = 10;
  static constexpr int bmp_header_size = 14;
  static constexpr int dib_header_size = 40;
  static constexpr size_t bits_per_pixel = 24;
  static constexpr int size_position = 2;
  static constexpr int width_position = 4;
  static constexpr int height_position = 8;
  static constexpr int dib_header_size_position = 0;
  static constexpr size_t cnt_of_planes = 1;
  static constexpr int cnt_of_planes_position = 12;
  static constexpr int bits_per_pixel_position = 14;
};
} // namespace renderer
