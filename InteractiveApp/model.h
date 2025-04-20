#pragma once
#include "external/Observer2/Observer.h"
#include "renderer_include.h"

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

  constexpr static float rotation_angle_ = M_PI / 120;
  constexpr static float move_distance_ = 0.4;
};
} // namespace InteractiveApp
