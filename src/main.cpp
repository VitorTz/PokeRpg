#include <raylib.h>
#include "constants.hpp"
#include "scene/Scene.hpp"
#include "util/TexturePool.hpp"


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
    
    pk::gSceneManager.init();
    
    #if defined(PLATFORM_WEB)
        emscripten_set_main_loop(mainloop, 60, 1);
    #else
        SetTargetFPS(60);
    
    while (!WindowShouldClose()) {
        mainloop();
    }

    #endif
    
    pk::gTexturePool.clear();
    CloseWindow();
    return 0;
}