#include "view.h"
#include <iostream>

namespace InteractiveApp {
View::View(QWidget *parent = nullptr)
    : QLabel(parent), state_observer_(
                          [this](Data &&data) {
                            std::cout << "uwu" << std::endl;
                            draw_data(std::move(data));
                          },
                          [this](Data &&data) { draw_data(std::move(data)); },
                          [this](Data &&data) { draw_data(std::move(data)); }),
      key_observable_{[this]() { return std::move(this->key_action_); }} {
  setFocusPolicy(Qt::StrongFocus);
}

View::StateObserverPtr View::port() { return &state_observer_; }
void View::subscribe(KeyObserverPtr ptr) { key_observable_.subscribe(ptr); }

void View::keyPressEvent(QKeyEvent *event) {
  key_action_ = event->key();
  key_observable_.notify();
}

void View::draw_data(Data &&data) {
  if (data.has_value()) {
    show_frame(*data);
  }
}

void View::show_frame(ImagePtr image_ptr) {
  QImage qimage(image_ptr->get_width(), image_ptr->get_height(),
                QImage::Format_RGB32);
  for (ssize_t x = 0; x < image_ptr->get_width(); ++x) {
    for (ssize_t y = 0; y < image_ptr->get_height(); ++y) {
      renderer::Color color = image_ptr->operator()(x, y);
      qimage.setPixelColor(x, y,
                           QColor(color.red(), color.green(), color.blue()));
    }
  }
  setPixmap(QPixmap::fromImage(std::move(qimage)));
}
} // namespace InteractiveApp