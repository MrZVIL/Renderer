#include "src/Image/Image.h"
#include "src/Object/Triangle.h"
#include <iostream>

using namespace renderer::image;
using namespace renderer::object;

int main() {
  Image img(128, 64);
  img.set_pixel(0, 63, 0, 255, 255);
  char *path = "test.bmp";
  img.output_image_to_bmp(path);

  Triangle tr(Point(1, 0, 0), Point(2, 0, 0), Point(0, 1, 0), Color());

  std::cout << tr.calculate_normal().transpose() << std::endl;
}