#pragma once
#include "Triangle.h"
#include <stdexcept>
#include <vector>

namespace renderer {
class Object {

public:
  using container_type = std::vector<Triangle>;
  Object(container_type triangles, Vector3 origin, Vector3 local_x,
         Vector3 local_y, Vector3 local_z);
  container_type &triangles();
  const container_type &triangles() const;

private:
  container_type data_{};
  Vector3 origin_{0, 0, 0};
  Vector3 local_x_{1, 0, 0};
  Vector3 local_y_{0, 1, 0};
  Vector3 local_z_{0, 0, 1};
};

} // namespace renderer
