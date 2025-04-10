#include "World.h"

namespace renderer {
World::World(obj_container_type objects) : objects_(objects) {}

void World::add_new_object(Object object) { objects_.push_back(object); }

World::obj_container_type &World::objects() { return objects_; }

const World::obj_container_type &World::objects() const { return objects_; }
} // namespace renderer
