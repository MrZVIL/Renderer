#include "src/Image/BMPWriter.h"
#include "src/Image/Image.h"
#include "src/Object/Object.h"
#include "src/Object/Triangle.h"
#include "src/Renderer/Renderer.h"
#include "src/Scene/Camera.h"
#include "src/Scene/World.h"
#include <chrono>
#include <iostream>

using namespace renderer;

void test_render() {
  const char *path = "pyramid.bmp";
  Color gray = Color::RGB(128, 128, 128);

  Vector3 p1{0, 1.5, -15};
  Vector3 p2{5.5, 5, -24};
  Vector3 p3{7, -5, -30};
  Vector3 p4{-8, 5, -30};

  Vector3 normal123 = (p3 - p1).cross(p2 - p1);
  Vector3 normal124 = (p2 - p1).cross(p4 - p1);
  Vector3 normal134 = (p4 - p1).cross(p3 - p1);
  Vector3 normal234 = (p3 - p2).cross(p4 - p2);

  Triangle tr123({p1, p2, p3}, {normal123, normal123, normal123},
                 {gray, gray, gray});
  Triangle tr124({p1, p2, p4}, {normal124, normal124, normal124},
                 {gray, gray, gray});
  Triangle tr134({p1, p3, p4}, {normal134, normal134, normal134},
                 {gray, gray, gray});
  Triangle tr234({p2, p3, p4}, {normal234, normal234, normal234},
                 {gray, gray, gray});

  renderer::Object obj{{tr123, tr124, tr134, tr234}};
  renderer::World world{};
  world.add_new_object((renderer::Object)obj);
  renderer::Camera camera{{0, 0, 0}, {0, 0, -1}, {0, 1, 0}, 1, 2, 1};
  Renderer renderer(Width(2048), Height(1024));
  Image img(Width(2048), Height(1024));
  auto start = std::chrono::high_resolution_clock::now();
  int frames_count = 30;
  for (int i = 0; i < frames_count; ++i) {
    img = renderer.render(world, camera);
  }
  auto end = std::chrono::high_resolution_clock::now();
  std::chrono::duration<double, std::milli> duration = end - start;
  std::cout << "Время отрисовки " << frames_count
            << " кадров: " << duration.count() << " миллисекунд" << std::endl;
  img = renderer.render(world, camera);
  BmpWriter bmpwriter(path);
  bmpwriter.write(img);
}

int main() { test_render(); }
