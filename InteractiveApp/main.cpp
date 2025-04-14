#include "controller.h"
#include "model.h"
#include "view.h"
#include <QApplication>
#include <QMainWindow>
#include <iostream>

renderer::Object generate_pyramid() {
  using namespace renderer;
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
  return renderer::Object{cont, {0, 0, 0}, {1, 0, 0}, {0, 1, 0}, {0, 0, 1}};
}

int main(int argc, char **argv) {
  std::cout << "Start" << std::endl;
  QApplication app(argc, argv);
  using namespace InteractiveApp;
  // InteractiveApp::Application app(argc, argv);
  Model model_(Model::Renderer(renderer::Width(1024), renderer::Height(512)),
               Model::Camera{{0, 0, 0}, {0, 0, -1}, {0, 1, 0}, 1, 2, 1},
               Model::World());
  View view_{};
  Controller ctrl_(&model_);
  view_.subscribe(ctrl_.port());
  std::cout << "Show" << std::endl;
  model_.world().add_new_object(generate_pyramid());
  model_.subscribe(view_.port());

  QMainWindow window;

  window.resize(1024, 512);
  window.setCentralWidget(&view_);
  window.show();

  return app.exec();
}
