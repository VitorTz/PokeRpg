#include "Scene.hpp"
#include "raylib.h"
#include <array>
#include "../util/TexturePool.hpp"


Texture2D backgroundImage{};
Texture2D logoImage{};
Texture2D pressStartImage{};
Vector2 logoPos{};
Vector2 pressStartPos{};
std::array<Vector2, 2> pos{
    Vector2{0.0f, 0.0f},
    Vector2{pk::SCREEN_W, 0.0f},
};


pk::TitleScreen::TitleScreen() {
    backgroundImage = pk::gTexturePool.get(ASSETS_PATH "graphics/backgrounds/title-screen.png");
    logoImage = pk::gTexturePool.get(ASSETS_PATH "graphics/ui/logo.png");
    pressStartImage = pk::gTexturePool.get(ASSETS_PATH "graphics/ui/press-space.png");
    logoPos = {
        pk::SCREEN_CENTERX - logoImage.width / 2.0f,
        pk::SCREEN_CENTERY - logoImage.height / 2.0f
    };
    pressStartPos = {
        pk::SCREEN_CENTERX - pressStartImage.width / 2.0f,
        pk::SCREEN_H - pressStartImage.height - 40.0f
    };
}


void pk::TitleScreen::update(const float dt) {
    for (Vector2& v : pos) {
        v.x -= dt * 150.0f;
        if (v.x + pk::SCREEN_W < 0.0f) {
            v.x *= pk::SCREEN_W * 2.0f;
        }
    }
    if (IsKeyPressed(KEY_SPACE)) {
        pk::gSceneManager.changeScene(pk::WorldSceneId);
    }
}


void pk::TitleScreen::draw() {
    DrawTextureRec(backgroundImage, {0.0f, 0.0f, pk::SCREEN_W, pk::SCREEN_H}, pos[0], WHITE);
    DrawTextureRec(backgroundImage, {0.0f, 0.0f, -pk::SCREEN_W, pk::SCREEN_H}, pos[1], WHITE);
    DrawTextureV(logoImage, logoPos, WHITE);
    DrawTextureV(pressStartImage, pressStartPos, WHITE);
}