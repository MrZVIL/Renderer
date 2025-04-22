#pragma once
#include "model.h"
#include <QLabel>

namespace InteractiveApp {
class Controller {
  using ModelPtr = Model *;
  using KeyAction = int;
  using KeyData = std::optional<KeyAction>;
  using KeyObserver = NSLibrary::CObserver<KeyAction>;
  using KeyObserverPtr = KeyObserver *;

public:
  Controller(ModelPtr ptr);
  KeyObserverPtr port();

  void on_key_data(KeyData &&key_data);
  void on_key_action(KeyAction key_act);
  void update_screen();

private:
  ModelPtr model_;
  KeyObserver key_observer_;
};
} // namespace InteractiveApp
