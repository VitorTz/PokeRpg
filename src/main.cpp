#include <cassert>
#include <raylib.h>
#include "constants.hpp"
#include "scene/Scene.hpp"
#include "util/TexturePool.hpp"
#include "ecs/components.hpp"
#include "util/TypeManager.hpp"
#include "util/FontPool.h"


#if defined(PLATFORM_WEB)
    #include <emscripten/emscripten.h>
#endif


void mainloop() {
    pk::gSceneManager.update(GetFrameTime());
    BeginDrawing();
    ClearBackground(BLACK);
    pk::gSceneManager.draw();
    EndDrawing();
}


int main() {
    InitWindow(pk::SCREEN_W, pk::SCREEN_H, pk::WINDOW_TITLE);

    pk::gTypeManager.insert<pk::transform_t>();
    pk::gTypeManager.insert<pk::sprite_t>();
    pk::gTypeManager.insert<pk::sprite_animation_t>();
    pk::gTypeManager.insert<pk::random_movement_t>();
    pk::gTypeManager.insert<pk::character_t>();
    assert(pk::gTypeManager.size() == pk::NUM_COMPONENTS);

    pk::gFontPool.init();
    pk::gSceneManager.init();
    
    #if defined(PLATFORM_WEB)
        emscripten_set_main_loop(mainloop, 60, 1);
    #else
        SetTargetFPS(60);
    
    while (!WindowShouldClose()) {
        mainloop();
    }

    #endif

    pk::gFontPool.clear();
    pk::gTexturePool.clear();
    CloseWindow();
    return 0;
}
