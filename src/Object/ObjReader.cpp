#include "ObjReader.h"

namespace renderer {

ObjReader::ObjReader(const std::string &filename) : filename_(filename) {}

Object ObjReader::read() {
  container_type triangles_list{};
  std::ifstream file(filename_);
  assert(file.is_open() && "Failed to open file");

  std::vector<Point> vertices;
  std::vector<Vector3> normals;

  std::string line;
  while (std::getline(file, line)) {
    Color gray = Color::RGB(127, 127, 127);
    std::istringstream ss(line);
    std::string prefix;
    ss >> prefix;

    if (prefix == "v") {
      Point vertex;
      ss >> vertex.x() >> vertex.y() >> vertex.z();
      vertices.push_back(vertex);
    } else if (prefix == "vn") {
      Vector3 normal;
      ss >> normal.x() >> normal.y() >> normal.z();
      normals.push_back(normal);
    } else if (prefix == "f") {
      std::string vertex_data;
      ss >> vertex_data;
      std::array v1 = parse_vertex(vertex_data);
      std::array v2 = parse_vertex(vertex_data);
      while (ss >> vertex_data) {
        std::array v3 = parse_vertex(vertex_data);
        std::array<Vector3, 3> tr_normals;

        if (v1[2] == -1) {
          tr_normals[0] = {0, 0, 0};
        } else {
          tr_normals[0] = normals[v1[2] - 1];
        }
        if (v2[2] == -1) {
          tr_normals[1] = {0, 0, 0};
        } else {
          tr_normals[1] = normals[v2[2] - 1];
        }
        if (v3[2] == -1) {
          tr_normals[2] = {0, 0, 0};
        } else {
          tr_normals[2] = normals[v3[2] - 1];
        }

        Triangle triangle{
            {vertices[v1[0] - 1], vertices[v2[0] - 1], vertices[v3[0] - 1]},
            tr_normals,
            {gray, gray, gray}};

        triangles_list.push_back(triangle);
        std::swap(v1, v2);
        std::swap(v2, v3);
      }
    }
  }

  file.close();
  return Object(triangles_list);
}

std::array<ObjReader::index_type, 3>
ObjReader::parse_vertex(const std::string &vertex_data) {
  int v = -1, vt = -1, vn = -1;
  size_t firstSlash = vertex_data.find('/');
  size_t secondSlash = vertex_data.find('/', firstSlash + 1);

  if (firstSlash == std::string::npos) {
    // v
    v = std::stoi(vertex_data);
  } else if (secondSlash == std::string::npos) {
    // v/vt
    v = std::stoi(vertex_data.substr(0, firstSlash));
    vt = std::stoi(vertex_data.substr(firstSlash + 1));
  } else {
    // v//vn or v/vt/vn
    v = std::stoi(vertex_data.substr(0, firstSlash));
    if (secondSlash > firstSlash + 1) {
      std::string vt_str =
          vertex_data.substr(firstSlash + 1, secondSlash - firstSlash - 1);
      if (!vt_str.empty())
        vt = std::stoi(vt_str);
    }
    std::string vn_str = vertex_data.substr(secondSlash + 1);
    if (!vn_str.empty())
      vn = std::stoi(vn_str);
  }

  return {v, vt, vn};
}
} // namespace renderer
