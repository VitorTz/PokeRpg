#include "scene/Scene.h"


int main() {
    InitWindow(pk::SCREEN_W, pk::SCREEN_H, pk::WINDOW_TITLE);
    SetTargetFPS(pk::FPS);

    pk::registerComponent<pk::transform_t>();
    pk::registerComponent<pk::sprite_t>();
    pk::registerComponent<pk::sprite_animation_t>();

    pk::gSceneManager.init();

    while (WindowShouldClose() == false) {
        pk::gSceneManager.update(GetFrameTime());
        BeginDrawing();
        ClearBackground(BLACK);
        pk::gSceneManager.draw();
        EndDrawing();
    }

    pk::gTexturePool.clear();
    CloseWindow();
    return 0;
}
