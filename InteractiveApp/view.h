#pragma once
#include "../src/Image/Image.h"
#include "external/Observer2/Observer.h"
#include <QKeyEvent>
#include <QLabel>

namespace InteractiveApp {
class View : public QLabel {
  Q_OBJECT
  using ImagePtr = renderer::Image *;
  using Data = std::optional<ImagePtr>;
  using StateObserver = NSLibrary::CObserver<ImagePtr>;
  using StateObserverPtr = StateObserver *;
  using KeyAction = int;
  using KeyData = std::optional<KeyAction>;
  using KeyObservable = NSLibrary::CObservable<KeyAction>;
  using KeyObserverPtr = NSLibrary::CObserver<KeyAction> *;

public:
  View(QWidget *parent = nullptr);
  StateObserverPtr port();
  void subscribe(KeyObserverPtr ptr);

private:
  void keyPressEvent(QKeyEvent *event) override;
  void draw_data(Data &&data);
  void show_frame(ImagePtr image_ptr);
  StateObserver state_observer_;
  KeyObservable key_observable_;

  KeyAction key_action_; // sorry
};

} // namespace InteractiveApp
