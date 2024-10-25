#pragma once
#include <cstddef>
#include <cstdint>
#include <raylib.h>
#include "../util/CharacterId.hpp"
#include "../util/Direction.h"
#include "../util/State.hpp"
#include "../util/TexturePool.hpp"
#include "../util/types.hpp"


namespace pk {

    constexpr std::size_t NUM_COMPONENTS{5};
    constexpr std::size_t NUM_DRAWABLE_COMPONENTS{2};

    typedef struct transform {
        Vector2 pos{};
        Vector2 size{};
        pk::zindex_t zindex{};
        pk::Direction direction{pk::Down};
        bool isMoving{};
        transform() = default;
        explicit transform(const pk::zindex_t zindex) : zindex(zindex) { }
    } transform_t;

    typedef struct sprite {
        Texture2D texture{};
        sprite() = default;
        explicit sprite(const char* fileName) : texture(pk::gTexturePool.get(fileName)) { }
    } sprite_t;

    typedef struct sprite_animation {
        Texture2D texture{};
        Rectangle textureRect{};
        std::uint8_t frame{};
        std::uint8_t maxFrame{};
        std::uint8_t spriteIndex{};
        std::uint8_t maxSpriteIndex{};
        sprite_animation() = default;
        sprite_animation(
            const char* imagePath,
            const float width,
            const float height,
            const std::uint8_t speed
        ) : texture(pk::gTexturePool.get(imagePath)),
            textureRect(Rectangle{0.0f, 0.0f, width, height}),
            maxFrame(speed),
            maxSpriteIndex(texture.width / width) { }
    } sprite_animation_t;

    typedef struct random_movement {
        Rectangle movementArea{};
        pk::State state{pk::Idle};
        float speed{};
        Vector2 direction{};
        Vector2 target{};
    } random_movement_t;

    typedef struct character {
        pk::CharacterId id{};
    } character_t;


}
