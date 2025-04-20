#include "controller.h"
#include <iostream>

namespace InteractiveApp {
Controller::Controller(ModelPtr ptr)
    : model_(ptr),
      key_observer_([this](KeyData &&kd) { update_screen(); },
                    [this](KeyData &&kd) { on_key_data(std::move(kd)); },
                    [this](KeyData &&kd) { update_screen(); }) {}

Controller::KeyObserverPtr Controller::port() { return &key_observer_; }

void Controller::on_key_data(KeyData &&key_data) {
  if (key_data.has_value()) {
    on_key_action(*key_data);
  }
}

void Controller::on_key_action(KeyAction act) {
  switch (act) {
  case Qt::Key::Key_W:
    model_->handleCameraMove(CameraMove::MoveForward);
    break;
  case Qt::Key::Key_S:
    model_->handleCameraMove(CameraMove::MoveBack);
    break;
  case Qt::Key::Key_D:
    model_->handleCameraMove(CameraMove::MoveRight);
    break;
  case Qt::Key::Key_A:
    model_->handleCameraMove(CameraMove::MoveLeft);
    break;
  case Qt::Key::Key_Z:
    model_->handleCameraMove(CameraMove::MoveUp);
    break;
  case Qt::Key::Key_X:
    model_->handleCameraMove(CameraMove::MoveDown);
    break;
  case Qt::Key::Key_E:
    model_->handleCameraMove(CameraMove::RotateRight);
    break;
  case Qt::Key::Key_Q:
    model_->handleCameraMove(CameraMove::RotateLeft);
    break;
  case Qt::Key::Key_C:
    model_->handleCameraMove(CameraMove::RotateClockwise);
    break;
  case Qt::Key::Key_V:
    model_->handleCameraMove(CameraMove::RotateAntiClocwise);
    break;
  case Qt::Key::Key_R:
    model_->handleCameraMove(CameraMove::RotateUp);
    break;
  case Qt::Key::Key_T:
    model_->handleCameraMove(CameraMove::RotateDown);
    break;
  default:
    break;
  }
}

void Controller::update_screen() {
  model_->handleCameraMove(CameraMove::UpdateScreen);
}

} // namespace InteractiveApp
