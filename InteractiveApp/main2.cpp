#include "../src/Object/ObjReader.h"
#include "controller.h"
#include "model.h"
#include "view.h"
#include <QApplication>
#include <QMainWindow>
#include <iostream>

int main(int argc, char **argv) {
  std::cout << "Start" << std::endl;
  QApplication app(argc, argv);
  using namespace InteractiveApp;
  // InteractiveApp::Application app(argc, argv);
  Model model_(Model::Renderer(renderer::Width(1024), renderer::Height(512)),
               Model::Camera{{0, 0, 5}, {0, 0, -1}, {0, 1, 0}, 1, 2, 1},
               Model::World());
  View view_{};
  Controller ctrl_(&model_);
  view_.subscribe(ctrl_.port());
  std::cout << "Show" << std::endl;
  renderer::ObjReader obj_reader("../teapot.obj");
  model_.world().add_new_object(obj_reader.read());
  model_.subscribe(view_.port());

  QMainWindow window;

  window.resize(1024, 512);
  window.setCentralWidget(&view_);
  window.show();

  return app.exec();
}
