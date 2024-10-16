#pragma once
#include "../pokemon.hpp"
#include "../util/TexturePool.hpp"


namespace pk {

    namespace id {

        constexpr pk::component_id_t transform{0};
        constexpr pk::component_id_t sprite{1};
        constexpr pk::component_id_t sprite_animation{2};
    
    }

    constexpr std::size_t NUM_COMPONENTS{3};
    constexpr std::size_t NUM_DRAWABLE_COMPONENTS{2};
    constexpr std::array<pk::component_id_t, pk::NUM_DRAWABLE_COMPONENTS> ID_OF_DRAWABLE_COMPONENTS = {
        pk::id::sprite,
        pk::id::sprite_animation
    };


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
        explicit sprite(const char* fileName) : texture(pk::gTexturePool.getTexture(fileName)) { }
    } sprite_t;

    typedef struct sprite_animation {
        Texture2D texture{};
        Rectangle textureRect{};
        std::uint8_t frame{};
        std::uint8_t spriteIndex{};
        std::uint8_t maxSpriteIndex{};
        std::uint8_t speed{};
        std::uint8_t cols{};
        sprite_animation() = default;
        explicit sprite_animation(
            const pk::sprite_animation_source_t& source
        ) : texture(pk::gTexturePool.getTexture(source.fileName)),
            textureRect(
                Rectangle{
                    0.0f, 
                    0.0f, 
                    static_cast<float>(texture.width / source.cols),
                    static_cast<float>(texture.height / source.rows)
                }
            ), 
            maxSpriteIndex(source.rows * source.cols),
            speed(source.speed),
            cols(source.cols) { }
    } sprite_animation_t;

}
