#pragma once
#include "../src/Renderer/Renderer.h"
#include "MyObservable.h"

namespace InteractiveApp {
enum CameraMove {
  MoveForward,
  MoveBack,
  MoveLeft,
  MoveRight,
  MoveUp,
  MoveDown,
  UpdateScreen,
  RotateLeft,
  RotateRight,
  RotateUp,
  RotateDown,
  RotateClockwise,
  RotateAntiClocwise,
};

class Model {
public:
  using Image = renderer::Image;
  // using Data = std::optional<Image>;
  using Renderer = renderer::Renderer;
  using Camera = renderer::Camera;
  using World = renderer::World;
  using ImageObservable = NSLibrary::CObservableMono<Image *>;
  using ImageObserverPtr = NSLibrary::CObserver<Image *> *;

  Model(Renderer &&renderer, Camera &&camera, World &&world);
  void handleCameraMove(CameraMove camera_move);
  void subscribe(ImageObserverPtr ptr);
  World &world();

private:
  ImageObservable image_observable_;
  Renderer renderer_;
  Camera camera_;
  World world_;
  Image last_image_;

  constexpr static float rotation_angle_ = M_PI / 30.0;
  constexpr static float move_distance_ = 1;
};
} // namespace InteractiveApp