#include "model.h"
#include <iostream>

namespace InteractiveApp {
Model::Model(Renderer &&renderer, Camera &&camera, World &&world)
    : renderer_(std::move(renderer)), camera_(std::move(camera)),
      world_(std::move(world)), image_observable_([this]() {
        last_image_ = std::move(renderer_.render(world_, camera_));
        return &last_image_;
      }),
      last_image_(renderer::Width(1), renderer::Height(1)) {}

void Model::subscribe(ImageObserverPtr ptr) {
  std::cout << "uwu" << std::endl;
  image_observable_.subscribe(ptr);
  std::cout << "uwu" << std::endl;
}

void Model::handleCameraMove(CameraMove camera_move) {
  switch (camera_move) {
  case CameraMove::MoveForward:
    camera_.move_along_local_z(move_distance_);
    break;
  case CameraMove::MoveBack:
    camera_.move_along_local_z(-move_distance_);
    break;
  case CameraMove::MoveLeft:
    camera_.move_along_local_x(-move_distance_);
    break;
  case CameraMove::MoveRight:
    camera_.move_along_local_x(move_distance_);
    break;
  case CameraMove::MoveUp:
    camera_.move_along_local_y(move_distance_);
    break;
  case CameraMove::MoveDown:
    camera_.move_along_local_y(-move_distance_);
    break;
  case CameraMove::RotateRight:
    camera_.rotate_along_local_y(rotation_angle_);
    break;
  case CameraMove::RotateLeft:
    camera_.rotate_along_local_y(-rotation_angle_);
    break;
  case CameraMove::RotateClockwise:
    camera_.rotate_along_local_z(rotation_angle_);
    break;
  case CameraMove::RotateAntiClocwise:
    camera_.rotate_along_local_z(-rotation_angle_);
    break;
  case CameraMove::RotateUp:
    camera_.rotate_along_local_x(rotation_angle_);
    break;
  case CameraMove::RotateDown:
    camera_.rotate_along_local_x(-rotation_angle_);
    break;

  default:
    break;
  }
  image_observable_.notify();
}

Model::World &Model::world() { return world_; }
} // namespace InteractiveApp
