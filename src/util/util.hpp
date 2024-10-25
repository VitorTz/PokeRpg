#pragma once
#include <cstddef>
#include "raylib.h"
#include "../ecs/components.hpp"


namespace pk {


    std::size_t hash(const char* s);

    Vector2 getCenter(const pk::transform_t& transform);

}
