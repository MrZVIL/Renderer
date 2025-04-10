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
  const char *path = "cube.bmp";
  // Color red = Color::RGB(255, 0, 0);
  // Color green = Color::RGB(0, 255, 0);
  // Color blue = Color::RGB(0, 0, 255);
  Color gray = Color::RGB(128, 128, 128);

  Vector3 p1{-5, 5, -20};
  Vector3 p2{5, 5, -20};
  Vector3 p3{5, -5, -20};
  Vector3 p4{-5, -5, -20};

  Vector3 p5{-5, 5, -30};
  Vector3 p6{5, 5, -30};
  Vector3 p7{5, -5, -30};
  Vector3 p8{-5, -5, -30};

  Vector3 normal_t = {0, 1, 0};
  Vector3 normal_b = {0, -1, 0};
  Vector3 normal_l = {-1, 0, 0};
  Vector3 normal_r = {1, 0, 0};
  Vector3 normal_n = {0, 0, 1};
  Vector3 normal_f = {0, 0, -1};

  Triangle tr_t1({p1, p2, p6}, {normal_t, normal_t, normal_t},
                 {gray, gray, gray});
  Triangle tr_t2({p1, p5, p6}, {normal_t, normal_t, normal_t},
                 {gray, gray, gray});
  Triangle tr_b1({p4, p3, p7}, {normal_b, normal_b, normal_b},
                 {gray, gray, gray});
  Triangle tr_b2({p4, p8, p7}, {normal_b, normal_b, normal_b},
                 {gray, gray, gray});

  Triangle tr_l1({p1, p4, p8}, {normal_l, normal_l, normal_l},
                 {gray, gray, gray});
  Triangle tr_l2({p1, p5, p8}, {normal_l, normal_l, normal_l},
                 {gray, gray, gray});
  Triangle tr_r1({p2, p3, p7}, {normal_r, normal_r, normal_r},
                 {gray, gray, gray});
  Triangle tr_r2({p2, p6, p7}, {normal_r, normal_r, normal_r},
                 {gray, gray, gray});

  Triangle tr_n1({p1, p2, p3}, {normal_n, normal_n, normal_n},
                 {gray, gray, gray});
  Triangle tr_n2({p1, p4, p3}, {normal_n, normal_n, normal_n},
                 {gray, gray, gray});
  Triangle tr_f1({p5, p6, p7}, {normal_f, normal_f, normal_f},
                 {gray, gray, gray});
  Triangle tr_f2({p5, p8, p7}, {normal_f, normal_f, normal_f},
                 {gray, gray, gray});
  Object::container_type cont = {tr_t1, tr_t2, tr_b1, tr_b2, tr_l1, tr_l2,
                                 tr_r1, tr_r2, tr_n1, tr_n2, tr_f1, tr_f2};
  renderer::Object obj{cont, {0, 0, 0}, {1, 0, 0}, {0, 1, 0}, {0, 0, 1}};
  // Object obj{{tr124}, {0, 0, 0}, {1, 0, 0}, {0, 1, 0}, {0, 0, 1}};
  renderer::World world{};
  world.add_new_object((renderer::Object)obj);
  renderer::Camera camera{{10, -10, 0}, {-0.7, 1, -1}, {0, 1, 0}, 1, 2, 2};
  Renderer renderer(Width(512), Height(512));
  Image img = renderer.render(world, camera);
  auto start = std::chrono::high_resolution_clock::now();
  int frames_count = 30;
  for (int i = 0; i < frames_count; ++i) {
    img = renderer.render(world, camera);
  }
  auto end = std::chrono::high_resolution_clock::now();
  std::chrono::duration<double, std::milli> duration = end - start;
  std::cout << "Время отрисовки " << frames_count
            << " кадров: " << duration.count() << " миллисекунд" << std::endl;
  img.output_image_to_bmp(path);
}

int main() { test_render(); }