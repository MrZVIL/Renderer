#pragma once
#include "Object.h"
#include <fstream>
#include <sstream>
#include <string>

namespace renderer {
class ObjReader {
  using container_type = Object::container_type;
  using Point = Triangle::Point;
  using index_type = ssize_t;

public:
  ObjReader(const std::string &filename);

  Object read();

private:
  std::string filename_;

  std::array<index_type, 3> parse_vertex(const std::string &vertex_data);
};
} // namespace renderer
