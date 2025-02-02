#include "PrimitiveColor.h"
#include "Utils.h"
#include <cmath>

namespace renderer::image {
PrimitiveColor::PrimitiveColor(primitive_color_value_type value)
    : value(value) {}

PrimitiveColor &
PrimitiveColor::set_primitive_color(primitive_color_value_type new_value) {
  this->value = new_value;
  return *this;
}

PrimitiveColor::primitive_color_value_type
PrimitiveColor::get_primitive_color_value() {
  return this->value;
}

PrimitiveColor PrimitiveColor::operator+(const PrimitiveColor &rhs) {
  if (utils::MAX_COLOR_VALUE - this->value >= rhs.value) {
    return PrimitiveColor(this->value + rhs.value);
  } else {
    return PrimitiveColor(utils::MAX_COLOR_VALUE);
  }
}

PrimitiveColor PrimitiveColor::operator-(const PrimitiveColor &rhs) {
  if (this->value - utils::MIN_COLOR_VALUE >= rhs.value) {
    return PrimitiveColor(this->value - rhs.value);
  } else {
    return PrimitiveColor(utils::MIN_COLOR_VALUE);
  }
}

PrimitiveColor PrimitiveColor::operator*(scale_type scale) {
  scale_type new_value = scale * static_cast<scale_type>(this->value);

  if (new_value < static_cast<scale_type>(utils::MIN_COLOR_VALUE)) {
    return PrimitiveColor(utils::MIN_COLOR_VALUE);
  } else if (new_value > static_cast<scale_type>(utils::MAX_COLOR_VALUE)) {
    return PrimitiveColor(utils::MAX_COLOR_VALUE);
  } else {
    return PrimitiveColor(
        static_cast<primitive_color_value_type>(roundf(new_value)));
  }
}

PrimitiveColor PrimitiveColor::operator/(scale_type scale) {
  scale_type new_value = static_cast<scale_type>(this->value) / scale;

  if (new_value < static_cast<scale_type>(utils::MIN_COLOR_VALUE)) {
    return PrimitiveColor(utils::MIN_COLOR_VALUE);
  } else if (new_value > static_cast<scale_type>(utils::MAX_COLOR_VALUE)) {
    return PrimitiveColor(utils::MAX_COLOR_VALUE);
  } else {
    return PrimitiveColor(
        static_cast<primitive_color_value_type>(roundf(new_value)));
  }
}

PrimitiveColor &PrimitiveColor::operator+=(const PrimitiveColor &rhs) {
  if (utils::MAX_COLOR_VALUE - this->value >= rhs.value) {
    this->value += rhs.value;
  } else {
    this->value = utils::MAX_COLOR_VALUE;
  }

  return *this;
}

PrimitiveColor &PrimitiveColor::operator-=(const PrimitiveColor &rhs) {
  if (this->value - utils::MIN_COLOR_VALUE >= rhs.value) {
    this->value -= rhs.value;
  } else {
    this->value = utils::MIN_COLOR_VALUE;
  }

  return *this;
}

PrimitiveColor &PrimitiveColor::operator*=(scale_type scale) {
  scale_type new_value = scale * static_cast<scale_type>(this->value);

  if (new_value < static_cast<scale_type>(utils::MIN_COLOR_VALUE)) {
    this->value = utils::MIN_COLOR_VALUE;
  } else if (new_value > static_cast<scale_type>(utils::MAX_COLOR_VALUE)) {
    this->value = utils::MAX_COLOR_VALUE;
  } else {
    this->value = static_cast<primitive_color_value_type>(roundf(new_value));
  }

  return *this;
}

PrimitiveColor &PrimitiveColor::operator/=(scale_type scale) {
  scale_type new_value = static_cast<scale_type>(this->value) / scale;

  if (new_value < static_cast<scale_type>(utils::MIN_COLOR_VALUE)) {
    this->value = utils::MIN_COLOR_VALUE;
  } else if (new_value > static_cast<scale_type>(utils::MAX_COLOR_VALUE)) {
    this->value = utils::MAX_COLOR_VALUE;
  } else {
    this->value = static_cast<primitive_color_value_type>(roundf(new_value));
  }

  return *this;
}
} // namespace renderer::image
