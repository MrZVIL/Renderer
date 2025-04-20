#include "Application.h"

namespace InteractiveApp {
Application::Application(int argc, char **argv, std::string obj_filename)
    : QApplication(argc, argv),
      model_(Renderer(Width(1024), Height(512)),
             Camera({0, 0, 5}, {0, 0, -1}, {0, 1, 0}, 1, 2, 1), World()),
      view_(), ctrl_(&model_) {

  renderer::ObjReader obj_reader(obj_filename);

  model_.world().add_new_object(obj_reader.read());
  model_.subscribe(view_.port());
  view_.subscribe(ctrl_.port());

  window_.setCentralWidget(&view_);
  window_.resize(1024, 512);
  window_.show();
}

Application Application::make_application(int argc, char *argv[]) {

  std::string obj_filename;
  int qt_argc = 1;
  std::vector<char *> qt_argv = {argv[0]};

  assert(argc > 1 && "Need .obj file in first argument");
  obj_filename = argv[1];

  for (int i = 2; i < argc; ++i) {
    qt_argv.push_back(argv[i]);
    ++qt_argc;
  }

  return Application(qt_argc, qt_argv.data(), obj_filename);
}
} // namespace InteractiveApp
