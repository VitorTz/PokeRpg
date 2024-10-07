//
// Created by vitor on 10/3/24.
//

#ifndef POKEMON_H
#define POKEMON_H
#include <raylib.h>
#include <raymath.h>
#include <unordered_map>
#include <cmath>
#include <algorithm>
#include <unordered_set>
#include <map>
#include <vector>
#include <array>
#include <memory>
#include <queue>
#include <cstdint>
#include <fstream>
#include <typeinfo>
#include <cassert>
#include <cstdio>
#include <iostream>


#define ASSETS_PATH "./assets/"
#define GRAPHICS_PATH ".assets/graphics/"
#define TILED_MAP_PATH "./assets/data/maps/"
#define CHARACTERS_PATH "./assets/graphics/characters/"

namespace pk {

    constexpr bool DEBUG_MODE{true};

    // Window
    constexpr float SCREEN_W{1280.0f};
    constexpr float SCREEN_H{720.0f};
    constexpr float SCREEN_CENTERX{SCREEN_W / 2.0f};
    constexpr float SCREEN_CENTERY{SCREEN_H / 2.0f};
    constexpr char WINDOW_TITLE[]{"Pokemon"};
    constexpr int FPS{60};

    // Types
    typedef std::uint32_t entity_t;
    typedef std::uint8_t component_t;
    typedef std::uint8_t zindex_t;
    typedef std::priority_queue<std::pair<double, int>, std::vector<std::pair<double, int>>, std::greater<>> PriorityQueue;
    enum PokemonType {
        WaterType,
        PlantType,
        FireType
    };

    enum ConstructionType {
        Hospital,
        Arena
    };
    enum CollisionType {
        EntityCollision,
        WorldObjectCollision
    };

    template<typename T>
    struct entity_pair_hash {
         std::size_t operator()(const std::pair<pk::entity_t, T>& p) const {
            return p.first;
        }
    };

    template<typename T>
    struct entity_pair_equal_to {
        bool operator()(const std::pair<pk::entity_t, T>& lhs, const std::pair<pk::entity_t, T>& rhs) const {
            return lhs.first == rhs.first;
        }
    };

    constexpr pk::entity_t MAX_ENTITIES{4096};

    // Camera
    constexpr pk::zindex_t CAMERA_ZINDEX_MIN{0};
        constexpr pk::zindex_t CAMERA_ZINDEX_TERRAIN{0};
        constexpr pk::zindex_t CAMERA_ZINDEX_WATER{1};
        constexpr pk::zindex_t CAMERA_ZINDEX_SHADOW{2};
        constexpr pk::zindex_t CAMERA_ZINDEX_WORLD{3};
        constexpr pk::zindex_t CAMERA_ZINDEX_WORLD_TOP{4};
        constexpr pk::zindex_t CAMERA_ZINDEX_SKY{5};
    constexpr pk::zindex_t CAMERA_ZINDEX_MAX{5};

    // Sprite Animation
    constexpr std::uint8_t ANIMATION_SPEED_SLOW{12};
    constexpr std::uint8_t ANIMATION_SPEED_NORMAL{8};
    constexpr std::uint8_t ANIMATION_SPEED_FAST{4};

    typedef struct sprite_animation_info {
        const char* fileName{};
        std::uint8_t rows{};
        std::uint8_t cols{};
        std::uint8_t speed{};
    } sprite_animation_info_t;

    // Scene
    enum SceneId {
        TitleScreenId = 0,
        LevelSceneId,
        LoadingScreenId,
        TestScene1Id,
        NumScenes
    };

    constexpr pk::SceneId MAIN_SCENE{pk::TestScene1Id};

    // TiledMap
    constexpr int TILE_SIZE{64};

    enum TiledMapId {
        WorldMapId = 0,
        NumWorldMaps
    };

    typedef struct tiled_map {
        const char* name{};
        pk::TiledMapId mapId{};
        int rows{};
        int cols{};
        float width{};
        float height{};
    } tiled_map_t;

    constexpr std::array<pk::tiled_map_t, pk::NumWorldMaps> TILED_MAPS = {
        pk::tiled_map_t{
            "world",
            pk::TiledMapId::WorldMapId,
            86,
            86,
            86.0f * pk::TILE_SIZE,
            86.0f * pk::TILE_SIZE
        }
    };

    // Player
    typedef struct player_info {
        Rectangle collideRect{};
        Rectangle actionRect{};
    } player_info_t;

}


#endif //POKEMON_H
