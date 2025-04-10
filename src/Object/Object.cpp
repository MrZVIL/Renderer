#include "Object.h"

namespace renderer {
Object::Object(container_type triangles, Vector3 origin, Vector3 local_x,
               Vector3 local_y, Vector3 local_z)
    : data_(triangles), origin_(origin) {
  float eps = 1e-8;
  assert((abs(local_x.dot(local_y)) < eps) &&
         "Invalid basis: x and y are not orthogonal");
  assert((abs(local_x.dot(local_z)) < eps) &&
         "Invalid basis: x and z are not orthogonal");
  assert((abs(local_y.dot(local_z)) < eps) &&
         "Invalid basis: y and z are not orthogonal");

  local_x_ = local_x;
  local_y_ = local_y;
  local_z_ = local_z;
}

Object::container_type &Object::triangles() { return data_; }
const Object::container_type &Object::triangles() const { return data_; }

} // namespace renderer