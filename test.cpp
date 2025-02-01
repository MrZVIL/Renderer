#include "src/Image/Image.h"
#include <iostream>

using namespace renderer::image;

int main() {
  Image img(128, 64);
  img.set_pixel(0, 63, 0, 0, 255);
  char *path = "test.bmp";
  img.output_image_to_file(path);
}