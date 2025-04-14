#pragma once
#include "controller.h"
#include "model.h"
#include "view.h"

namespace InteractiveApp {
class Application {
  using Renderer = renderer::Renderer;
  using Camera = renderer::Camera;
  using Width = renderer::Width;
  using Height = renderer::Height;
  using World = renderer::World;

public:
  Application(int argc, char **argv);

private:
  Model model_;
  Controller ctrl_;
  View view_;
};
} // namespace InteractiveApp