#include "Color.h"
#include "Utils.h"
#include <cmath>

namespace renderer::image {
Color::Color(color_value_type value) : value(value) {}

Color &Color::set_color(color_value_type new_value) {
  this->value = new_value;
  return *this;
}

Color::color_value_type Color::get_color_value() { return this->value; }

Color Color::operator+(const Color &rhs) {
  if (utils::MAX_COLOR_VALUE - this->value >= rhs.value) {
    return Color(this->value + rhs.value);
  } else {
    return Color(utils::MAX_COLOR_VALUE);
  }
}

Color Color::operator-(const Color &rhs) {
  if (this->value - utils::MIN_COLOR_VALUE >= rhs.value) {
    return Color(this->value - rhs.value);
  } else {
    return Color(utils::MIN_COLOR_VALUE);
  }
}

Color Color::operator*(scale_type scale) {
  scale_type new_value = scale * static_cast<scale_type>(this->value);

  if (new_value < static_cast<scale_type>(utils::MIN_COLOR_VALUE)) {
    return Color(utils::MIN_COLOR_VALUE);
  } else if (new_value > static_cast<scale_type>(utils::MAX_COLOR_VALUE)) {
    return Color(utils::MAX_COLOR_VALUE);
  } else {
    return Color(static_cast<color_value_type>(roundf(new_value)));
  }
}

Color Color::operator/(scale_type scale) {
  scale_type new_value = static_cast<scale_type>(this->value) / scale;

  if (new_value < static_cast<scale_type>(utils::MIN_COLOR_VALUE)) {
    return Color(utils::MIN_COLOR_VALUE);
  } else if (new_value > static_cast<scale_type>(utils::MAX_COLOR_VALUE)) {
    return Color(utils::MAX_COLOR_VALUE);
  } else {
    return Color(static_cast<color_value_type>(roundf(new_value)));
  }
}

Color &Color::operator+=(const Color &rhs) {
  if (utils::MAX_COLOR_VALUE - this->value >= rhs.value) {
    this->value += rhs.value;
  } else {
    this->value = utils::MAX_COLOR_VALUE;
  }

  return *this;
}

Color &Color::operator-=(const Color &rhs) {
  if (this->value - utils::MIN_COLOR_VALUE >= rhs.value) {
    this->value -= rhs.value;
  } else {
    this->value = utils::MIN_COLOR_VALUE;
  }

  return *this;
}

Color &Color::operator*=(scale_type scale) {
  scale_type new_value = scale * static_cast<scale_type>(this->value);

  if (new_value < static_cast<scale_type>(utils::MIN_COLOR_VALUE)) {
    this->value = utils::MIN_COLOR_VALUE;
  } else if (new_value > static_cast<scale_type>(utils::MAX_COLOR_VALUE)) {
    this->value = utils::MAX_COLOR_VALUE;
  } else {
    this->value = static_cast<color_value_type>(roundf(new_value));
  }

  return *this;
}

Color &Color::operator/=(scale_type scale) {
  scale_type new_value = static_cast<scale_type>(this->value) / scale;

  if (new_value < static_cast<scale_type>(utils::MIN_COLOR_VALUE)) {
    this->value = utils::MIN_COLOR_VALUE;
  } else if (new_value > static_cast<scale_type>(utils::MAX_COLOR_VALUE)) {
    this->value = utils::MAX_COLOR_VALUE;
  } else {
    this->value = static_cast<color_value_type>(roundf(new_value));
  }

  return *this;
}
} // namespace renderer::image
