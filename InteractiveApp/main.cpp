#include "Application.h"

int main(int argc, char **argv) {
  try {
    InteractiveApp::Application app =
        InteractiveApp::Application::make_application(argc, argv);
    return app.exec();
  } catch (...) {
    std::cout << "Something went wrong" << std::endl;
  }
  return 0;
}
