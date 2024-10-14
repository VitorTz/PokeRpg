#pragma once
#include <raylib.h>
#include <raymath.h>
#include <algorithm>
#include <cstdint>
#include <unordered_map>
#include <unordered_set>
#include <map>
#include <vector>
#include <array>
#include <queue>
#include <memory>
#include <random>
#include <cassert>
#include <filesystem>
#include <iostream>
#include <fstream>
#include <cstdio>


#define ASSETS_PATH "./assets/"


namespace pk {


    // types
        typedef std::uint32_t entity_t;
        typedef std::uint8_t component_id_t;
        typedef std::uint8_t zindex_t;

        typedef struct sprite_animation_source {
            const char* fileName{};
            std::uint8_t speed{};
            std::uint8_t rows{};
            std::uint8_t cols{};
        } sprite_animation_source_t;

        enum SceneId {
            TitleScreenId,
            LevelSceneId,
            LoadingScreenId,
            TestScene1Id,
            TestScene2Id,
            NumScenes
        };

        enum MapId {
            WorldMapId,
            HospitalMapId,
            FireArenaMapId,
            TestMap,
            NumMaps
        };

    // Window
        constexpr float SCREEN_W{1280.0f};
        constexpr float SCREEN_H{720.0f};
        constexpr float SCREEN_CENTERX{SCREEN_W / 2.0f};
        constexpr float SCREEN_CENTERY{SCREEN_H / 2.0f};
        constexpr Vector2 SCREEN_SIZE{SCREEN_W, SCREEN_H};
        constexpr Vector2 SCREEN_CENTER{SCREEN_CENTERX, SCREEN_CENTERX};
        constexpr char WINDOW_TITLE[]{"PokemonRpg"};
        constexpr int FPS{60};

    // Game constants
        constexpr pk::entity_t MAX_ENTITIES{4096};
        constexpr pk::SceneId MAIN_SCENE{pk::SceneId::TestScene1Id};
        constexpr bool DEBUG_MODE{true};
        constexpr std::array<const char*, pk::NumMaps> MAP_PATHS = {
            ASSETS_PATH "data/maps/world.tmx",
            ASSETS_PATH "data/maps/hospital.tmx",
            ASSETS_PATH "data/maps/fire.tmx"
        };
        // Camera
        constexpr pk::zindex_t CAMERA_MIN_ZINDEX{0};
        constexpr pk::zindex_t CAMERA_MAX_ZINDEX{10};
        constexpr float CAMERA_MIN_ZOOM{0.25f};
        constexpr float CAMERA_MAX_ZOOM{2.50f};


}
