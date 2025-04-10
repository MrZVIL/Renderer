#pragma once
#undef Success
#include <Eigen/Dense>

namespace renderer {
using Matrix4 = Eigen::Matrix4f;
using Vector4 = Eigen::Vector4f;
using Vector3 = Eigen::Vector3f;
using Vector2 = Eigen::Vector2f;
using scale_type = float;
} // namespace renderer
