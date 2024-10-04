//
// Created by vitor on 10/3/24.
//

#ifndef COMPONENTS_H
#define COMPONENTS_H
#include "../pokemon.h"
#include "../util/TexturePool.h"


namespace pk {

    constexpr std::size_t NUM_COMPONENTS{3};

    typedef struct transform {
        Vector2 pos{};
        Vector2 size{};
        pk::zindex_t zindex{};
    } transform_t;

    typedef struct sprite {
        Texture2D texture{};
        sprite() = default;
        explicit sprite(const char* fileName) : texture(pk::gTexturePool.get(fileName)) { }
    } sprite_t;

    typedef struct sprite_animation {
        Texture2D texture{};
        Rectangle textureRect{};
        std::uint8_t counter{};
        std::uint8_t frame{};
        std::uint8_t maxFrame{};
        std::uint8_t speed{};
        std::uint8_t cols{};
        sprite_animation() = default;
        explicit sprite_animation(
            const pk::sprite_animation_info_t& info
        ) : texture(pk::gTexturePool.get(info.fileName)),
            textureRect(
                Rectangle{
                    0.0f,
                    0.0f,
                    static_cast<float>(texture.width / info.cols),
                    static_cast<float>(texture.height / info.rows)
                }
            ),
            maxFrame(info.rows * info.cols),
            speed(info.speed),
            cols(info.cols) {

        }
    } sprite_animation_t;

    inline std::unordered_map<const char*, pk::component_t> gComponentIdMap{};

    template<typename T>
    void registerComponent() {
        const char* name = typeid(T).name();
        assert(pk::gComponentIdMap.find(name) == pk::gComponentIdMap.end());
        pk::gComponentIdMap.emplace(name, pk::gComponentIdMap.size());
    }

    template<typename T>
    pk::component_t getComponentId() {
        const char* name = typeid(T).name();
        assert(pk::gComponentIdMap.find(name) != pk::gComponentIdMap.end());
        return pk::gComponentIdMap[typeid(T).name()];
    }

}

#endif //COMPONENTS_H

