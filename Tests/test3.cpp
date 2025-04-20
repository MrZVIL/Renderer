#include "renderer_include.h"
#include <chrono>
#include <iostream>
#include <string>

using namespace renderer;

void test_render(std::string obj_path) {
  const char *path = "teapot.bmp";
  ObjReader objreader(obj_path);
  renderer::Object obj = objreader.read();
  // Object obj{{tr124}, {0, 0, 0}, {1, 0, 0}, {0, 1, 0}, {0, 0, 1}};
  renderer::World world{};
  world.add_new_object((renderer::Object)obj);
  renderer::Camera camera{{0, 0, 3}, {0, 0, -1}, {0, 1, 0}, 1, 2, 2};
  Renderer renderer(Width(512), Height(512));
  Image img = renderer.render(world, camera);
  auto start = std::chrono::high_resolution_clock::now();
  int frames_count = 120;
  for (int i = 0; i < frames_count; ++i) {
    img = renderer.render(world, camera);
  }
  auto end = std::chrono::high_resolution_clock::now();
  std::chrono::duration<double, std::milli> duration = end - start;
  std::cout << "Время отрисовки " << frames_count
            << " кадров: " << duration.count() << " миллисекунд" << std::endl;
  BmpWriter bmpwriter(path);
  bmpwriter.write(img);
}

int main(int argc, char *argv[]) {
  if (argc < 2) {
    std::cout << "Нужен obj файл" << std::endl;
  } else {
    test_render(argv[1]);
  }
}