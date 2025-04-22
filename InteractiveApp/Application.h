#pragma once
#include "controller.h"
#include "model.h"
#include "view.h"
#include <QApplication>
#include <QMainWindow>
#include <iostream>
#include <string>

namespace InteractiveApp {
class Application : public QApplication {
  using Renderer = renderer::Renderer;
  using Camera = renderer::Camera;
  using Width = renderer::Width;
  using Height = renderer::Height;
  using World = renderer::World;

public:
  static Application make_application(int argc, char **argv);

private:
  Application(int argc, char **argv, std::string obj_filename);
  QMainWindow window_{};
  Model model_;
  Controller ctrl_;
  View view_;
};
} // namespace InteractiveApp
