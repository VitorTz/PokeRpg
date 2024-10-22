//
// Created by vitor on 10/19/24.
//
#include "Scene.h"
#include "raylib.h"
#include "../util/TexturePool.h"


pk::TitleScreen::TitleScreen() {
    this->backgroundPos[0] = Vector2{0.0f, 0.0f};
    this->backgroundPos[1] = Vector2{pk::SCREEN_W, 0.0f};
    this->background = pk::gTexturePool.load(ASSETS_PATH "graphics/backgrounds/title-screen-background.png");
    this->logo = pk::gTexturePool.load(ASSETS_PATH "graphics/ui/logo.png");
    this->pressSpace = pk::gTexturePool.load(ASSETS_PATH "graphics/ui/press-space.png");
    this->logoPos = Vector2{
        pk::SCREEN_CENTERX - this->logo.width / 2.0f,
        pk::SCREEN_CENTERY - this->logo.height / 2.0f
    };
    this->pressSpacePos = Vector2{
        pk::SCREEN_CENTERX - this->pressSpace.width / 2.0f,
        this->logoPos.y + this->logo.height + 40.0f
    };
}


void pk::TitleScreen::update(const float dt) {
    for (Vector2& pos : this->backgroundPos) {
        pos.x -= dt * 150.0f;
        if (pos.x + pk::SCREEN_W <= 0.0f) {
            pos.x += pk::SCREEN_W * 2.0f;
        }
    }
    if (IsKeyPressed(KEY_SPACE)) {
        pk::gSceneManager.changeScene(pk::WorldSceneId);
    }
}


void pk::TitleScreen::draw() {
    DrawTextureRec(this->background, Rectangle{0.0f, 0.0f, pk::SCREEN_W, pk::SCREEN_H}, this->backgroundPos[0], WHITE);
    DrawTextureRec(this->background, Rectangle{0.0f, 0.0f, -pk::SCREEN_W, pk::SCREEN_H}, this->backgroundPos[1], WHITE);
    DrawTextureV(this->logo, this->logoPos, WHITE);
    DrawTextureV(this->pressSpace, this->pressSpacePos, WHITE);
}



