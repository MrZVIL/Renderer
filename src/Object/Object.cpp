#include "Object.h"

namespace renderer {
Object::Object(container_type triangles) : data_(triangles) {}

Object::container_type &Object::triangles() { return data_; }
const Object::container_type &Object::triangles() const { return data_; }

} // namespace renderer
