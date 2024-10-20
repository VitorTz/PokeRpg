//
// Created by vitor on 10/19/24.
//

#ifndef COMPONENTS_H
#define COMPONENTS_H
#include <raylib.h>
#include "../util/TexturePool.h"
#include "../util/types.h"
#include "../util/TransitionType.h"
#include "../util/PokeType.h"


namespace pk {

    constexpr  std::size_t NUM_COMPONENTS{4};
    constexpr  std::size_t NUM_DRAWABLE_COMPONENTS{3};

    typedef struct transform {
        Vector2 pos{};
        Vector2 size{};
        pk::zindex_t zindex{};
        transform() = default;
        explicit transform(const pk::zindex_t zindex) : zindex(zindex) { }
    } transform_t;

    typedef struct sprite {
        Texture2D texture{};
        sprite() = default;
        explicit sprite(const char* fileName) : texture(pk::gTexturePool.load(fileName)) { }
    } sprite_t;

    typedef struct sprite_animation {
        pk::sprite_t sprite{};
        Rectangle textureRect{};
        std::uint8_t spriteIndex{};
        std::uint8_t maxSpriteIndex{};
        std::uint8_t frame{};
        std::uint8_t maxFrame{};
        sprite_animation() = default;
        explicit sprite_animation(
            const pk::sprite_animation_info_t& info
        ) : sprite(info.fileName),
            textureRect({0.0f,0.0f, info.spriteWidth, info.spriteHeight}),
            maxSpriteIndex(sprite.texture.width / static_cast<int>(info.spriteWidth)),
            maxFrame(info.speed) { }
    } sprite_animation_t;

    typedef struct transition {
        bool isHovered{};
        Rectangle actionBox{};
        pk::TransitionType type{};
    } transition_t;

}


#endif //COMPONENTS_H
