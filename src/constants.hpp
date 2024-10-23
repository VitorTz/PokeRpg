#pragma once
#include "util/SceneId.hpp"


#define ASSETS_PATH "./src/assets/"


namespace pk {


    constexpr float SCREEN_W{1280.0f};
    constexpr float SCREEN_H{720.0f};
    constexpr float SCREEN_CENTERX{SCREEN_W / 2.0f};
    constexpr float SCREEN_CENTERY{SCREEN_H / 2.0f};
    constexpr char WINDOW_TITLE[]{"PokemonRpg"};
    constexpr int FPS{60};


    constexpr bool DEBUB_MODE{true};
    constexpr pk::SceneId MAIN_SCENE{pk::TitleScreenId};


}