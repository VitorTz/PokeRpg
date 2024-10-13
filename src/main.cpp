#include "scene/Scene.hpp"
#include "util/TexturePool.hpp"


int main() {
    InitWindow(pk::SCREEN_W, pk::SCREEN_H, pk::WINDOW_TITLE);
    SetTargetFPS(pk::FPS);
    
    pk::gSceneManager.init();

    while (WindowShouldClose() == false) {
        pk::gSceneManager.update(GetFrameTime());
        BeginDrawing();
        ClearBackground(BLACK);
        pk::gSceneManager.draw();
        EndDrawing();
    }

    pk::gTexturePool.unloadAllTextures();
    CloseWindow();
    return 0;
}
