//
// Created by vitor on 10/19/24.
//

#ifndef TYPES_H
#define TYPES_H
#include <cstdint>


namespace pk {

    typedef std::uint32_t entity_t;
    typedef std::uint8_t component_t;
    typedef std::uint8_t zindex_t;

    typedef struct sprite_animation_info {
        const char* fileName{};
        float spriteWidth{};
        float spriteHeight{};
        std::uint8_t speed{};
    } sprite_animation_info_t;

    typedef struct tiled_map_info {
        const char* name{};
        float width{};
        float height{};
        std::size_t rows{};
        std::size_t cols{};
        Vector2 playerStartPos{};
    } tiled_map_info_t;

}

#endif //TYPES_H
