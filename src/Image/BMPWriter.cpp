#include "BMPWriter.h"

namespace renderer {
BmpWriter::BmpWriter(std::string path) : path_(std::move(path)) {}

size_t BmpWriter::get_padding_size(size_t width) const {
  return (padding_size - (width * bytes_per_pixel) % padding_size) %
         padding_size;
}

void BmpWriter::WriteBMPHeader(unsigned char *bmp_header, size_t size) const {
  bmp_header[format_first_position] = bmp_signature[0];
  bmp_header[format_second_position] = bmp_signature[1];
  num_to_bytes(size, bmp_header + file_size_position);
  bmp_header[pixs_array_offset_position] = bmp_header_size + dib_header_size;
}

void BmpWriter::WriteDIBHeader(unsigned char *dib_header, size_t width,
                               size_t height) const {
  dib_header[dib_header_size_position] = dib_header_size;
  num_to_bytes(width, dib_header + width_position);
  num_to_bytes(height, dib_header + height_position);
  dib_header[cnt_of_planes_position] = cnt_of_planes;
  dib_header[bits_per_pixel_position] = bits_per_pixel;
}

void BmpWriter::write(const Image &image) {
  std::ofstream img_file_stream;
  img_file_stream.open(path_, std::ios::out | std::ios::binary);
  assert(img_file_stream.is_open() && "Can't open file");
  assert(errno != EACCES && "Permission denied to open file");
  const size_t size = bmp_header_size + dib_header_size +
                      image.get_width() * image.get_height() * bytes_per_pixel +
                      get_padding_size(image.get_width()) * image.get_height();

  unsigned char bmp_header[bmp_header_size] = {};
  std::fill(bmp_header, bmp_header + bmp_header_size, 0);
  WriteBMPHeader(bmp_header, size);

  unsigned char dib_header[dib_header_size] = {};
  std::fill(dib_header, dib_header + dib_header_size, 0);
  WriteDIBHeader(dib_header, image.get_width(), image.get_height());

  img_file_stream.write(reinterpret_cast<char *>(bmp_header), bmp_header_size);
  img_file_stream.write(reinterpret_cast<char *>(dib_header), dib_header_size);

  unsigned char empty_pix[bytes_per_pixel] = {0, 0, 0};
  for (ssize_t i = image.get_height() - 1; i >= 0; --i) {
    for (ssize_t j = 0; j < image.get_width(); ++j) {
      unsigned char blue = static_cast<unsigned char>(image(j, i).blue());
      unsigned char green = static_cast<unsigned char>(image(j, i).green());
      unsigned char red = static_cast<unsigned char>(image(j, i).red());
      unsigned char pix[] = {blue, green, red};
      img_file_stream.write(reinterpret_cast<char *>(pix), bytes_per_pixel);
    }
    img_file_stream.write(
        reinterpret_cast<char *>(empty_pix),
        static_cast<std::streamsize>(get_padding_size(image.get_width())));
  }
}
} // namespace renderer
