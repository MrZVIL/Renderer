#pragma once
#include "../Object/Object.h"
#include <vector>

namespace renderer {
class World {
public:
  using obj_container_type = std::vector<Object>;
  World() = default;
  World(obj_container_type objects);

  void add_new_object(Object object);
  obj_container_type &objects();
  const obj_container_type &objects() const;

private:
  obj_container_type objects_{};
};
} // namespace renderer
