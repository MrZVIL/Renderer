#pragma once
#include "Triangle.h"
#include <stdexcept>
#include <vector>

namespace renderer {
class Object {

public:
  using container_type = std::vector<Triangle>;
  Object(container_type triangles);
  container_type &triangles();
  const container_type &triangles() const;

private:
  container_type data_{};
};

} // namespace renderer
