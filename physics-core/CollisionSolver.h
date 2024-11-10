
#pragma once

#include "Vector.h"
#include "EntityStore.h"
#include <vector>

std::array<physics_type::Vector2,4> getRectangleVirtices(const physics_type::Vector2& position, float width, float height, float angle);
