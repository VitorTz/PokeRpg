//
// Created by vitor on 10/19/24.
//

#ifndef CONSTANTS_H
#define CONSTANTS_H
#include <array>
#include <raylib.h>
#include "util/SceneId.h"
#include "util/types.h"
#include "util/MapId.h"


#define ASSETS_PATH "./assets/"


namespace pk {

    // Window
    constexpr float SCREEN_W{1280.0f};
    constexpr float SCREEN_H{720.0f};
    constexpr float SCREEN_CENTERX{SCREEN_W / 2.0f};
    constexpr float SCREEN_CENTERY{SCREEN_H / 2.0f};
    constexpr Vector2 SCREEN_SIZE{SCREEN_W, SCREEN_H};
    constexpr Vector2 SCREEN_CENTER{SCREEN_CENTERX, SCREEN_CENTERY};
    constexpr char WINDOW_TITLE[]{"PokemonRpg"};
    constexpr int FPS{60};

    // Game
    constexpr bool DEBUG_MODE{true};
    constexpr pk::SceneId MAIN_SCENE{pk::WorldSceneId};
    constexpr pk::entity_t MAX_ENTITIES{4096};
    constexpr int LEFT_KEY{KEY_A};
    constexpr int RIGHT_KEY{KEY_D};
    constexpr int UP_KEY{KEY_W};
    constexpr int DOWN_KEY{KEY_S};
    constexpr int ACTION_KEY{KEY_F};

    // Camera
    constexpr pk::zindex_t ZINDEX_MIN{0};
    constexpr pk::zindex_t ZINDEX_GROUND{1};
    constexpr pk::zindex_t ZINDEX_WATER{2};
    constexpr pk::zindex_t ZINDEX_SHADOW{3};
    constexpr pk::zindex_t ZINDEX_PLAYER{4};
    constexpr pk::zindex_t ZINDEX_TOP{5};
    constexpr pk::zindex_t ZINDEX_SKY{6};
    constexpr pk::zindex_t ZINDEX_MAX{6};
    constexpr float CAMERA_MIN_ZOOM{0.25};
    constexpr float CAMERA_MAX_ZOOM{2.5};

    // TiledMap
    constexpr std::array<pk::tiled_map_info_t, pk::MapId::MapsNum> TILED_MAP_INFO = {
        pk::tiled_map_info_t{"world", 5504, 5504, 86, 86, Vector2{4257.0f, 3489.0f}}
    };

    // Player
    constexpr Vector2 PLAYER_SIZE{128.0f, 128.0f};
    constexpr float PLAYER_SPEED{150.0f};
    constexpr Rectangle PLAYER_COLLISION_RECT{0.0f, 0.0f, 40.0f, 40.0f};
    constexpr Rectangle PLAYER_ACTION_BOX{0.0f, 0.0f, 80.0f, 64.0f};
    constexpr pk::sprite_animation_info_t PLAYER_SPRITE_ANIMATION{
        ASSETS_PATH "graphics/characters/player.png",
        pk::PLAYER_SIZE.x,
        pk::PLAYER_SIZE.y,
        12
    };

}

#endif //CONSTANTS_H
