//
// Created by vitor on 10/19/24.
//
#include "constants.h"
#include "ecs/EcsManager.h"
#include "scene/Scene.h"
#include "util/TexturePool.h"


int main() {
    InitWindow(pk::SCREEN_W, pk::SCREEN_H, pk::WINDOW_TITLE);
    SetTargetFPS(pk::FPS);

    pk::EcsManager::init();
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
