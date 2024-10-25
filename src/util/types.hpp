#pragma once
#include <cstdint>
#include "SceneId.hpp"
#include "raylib.h"


namespace pk {

    typedef std::uint32_t entity_t;
    typedef std::uint8_t component_t;
    typedef std::uint8_t zindex_t;

    typedef struct map_info {
        pk::SceneId sceneId{};
        const char* name{};
        float width{};
        float height{};
        Vector2 worldOffset{};
    } map_info_t;

}