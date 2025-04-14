#include "Application.h"

namespace InteractiveApp {
Application::Application(int argc, char **argv)
    : model_(Renderer(Width(1024), Height(512)), Camera(), World()), view_(),
      ctrl_(&model_) {
  model_.subscribe(view_.port());
  view_.subscribe(ctrl_.port());

  QApplication app(argc, argv);

  QMainWindow window;

  window.setCentralWidget(&view_);
  window.resize(400, 400);
  window.show();

  app.exec();
}
} // namespace InteractiveApp