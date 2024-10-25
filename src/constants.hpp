#pragma once
#include "raylib.h"
#include "util/SceneId.hpp"
#include "util/FontId.h"
#include "util/types.hpp"
#include <array>

#define ASSETS_PATH "./assets/"


namespace pk {

    // Window
    constexpr float SCREEN_W{1280.0f};
    constexpr float SCREEN_H{720.0f};
    constexpr float SCREEN_CENTERX{SCREEN_W / 2.0f};
    constexpr float SCREEN_CENTERY{SCREEN_H / 2.0f};
    constexpr Vector2 SCREEN_CENTER{SCREEN_CENTERX, SCREEN_CENTERY};
    constexpr char WINDOW_TITLE[]{"PokemonRpg"};
    constexpr int FPS{60};

    // Camera
    constexpr pk::zindex_t CAMERA_MIN_ZINDEX{0};
    constexpr pk::zindex_t CAMERA_ZINDEX_WATER{0};
    constexpr pk::zindex_t CAMERA_ZINDEX_TERRAIN{1};
    constexpr pk::zindex_t CAMERA_ZINDEX_SHADOW{2};
    constexpr pk::zindex_t CAMERA_ZINDEX_CHARACTER{3};
    constexpr pk::zindex_t CAMERA_ZINDEX_SKY{4};
    constexpr pk::zindex_t CAMERA_MAX_ZINDEX{4};
    constexpr float CAMERA_MIN_ZOOM{0.25f};
    constexpr float CAMERA_MAX_ZOOM{2.50f};

    // AnimationSpeed
    constexpr std::uint8_t ANIMATION_SPEED_SLOW{12};
    constexpr std::uint8_t ANIMATION_SPEED_NORMAL{8};
    constexpr std::uint8_t ANIMATION_SPEED_FAST{4};

    // Keys
    constexpr int ACTION_KEY{KEY_F};
    constexpr int M_LEFT_KEY{KEY_A};
    constexpr int M_RIGHT_KEY{KEY_D};
    constexpr int M_UP_KEY{KEY_W};
    constexpr int M_DOWN_KEY{KEY_S};

    // Game
    constexpr bool DEBUB_MODE{true};
    constexpr pk::SceneId MAIN_SCENE{pk::WorldSceneId};
    constexpr pk::entity_t MAX_ENTITIES{4096};
    constexpr float CHARACTER_SIZE{128.0f};

    // Font
    constexpr std::array<const char*, pk::NumFonts> FONT_PATH = {
        ASSETS_PATH "data/font/Nunito/static/Nunito-Light.ttf",
        ASSETS_PATH "data/font/Nunito/static/Nunito-Regular.ttf",
        ASSETS_PATH "data/font/Nunito/static/Nunito-SemiBold.ttf",
        ASSETS_PATH "data/font/Nunito/static/Nunito-Bold.ttf"
    };

    // TiledMap
    constexpr std::array<pk::map_info_t, pk::NumScenes> MAP_INFO = {
        pk::map_info_t{pk::SceneId::TitleScreenId, "title-screen", pk::SCREEN_W, pk::SCREEN_CENTERY, Vector2{0.0f, 0.0f}},
        pk::map_info_t{pk::SceneId::WorldSceneId, "world", 5504.0f, 5504.f, Vector2{0.0f, 0.0f}}
    };

    // Player
    constexpr float PLAYER_SPEED{150.0f};
    constexpr float PLAYER_COLLIDE_BOX_W{48.0f};
    constexpr float PLAYER_COLLIDE_BOX_H{48.0f};
    constexpr float PLAYER_ACTION_BOX_W{80.0f};
    constexpr float PLAYER_ACTION_BOX_H{40.0f};

}
