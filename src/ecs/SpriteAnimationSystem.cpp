//
// Created by vitor on 10/13/24.
//
#include "EcsController.hpp"
#include "SystemManager.hpp"


void pk::SpriteAnimationSystem::update(const float dt) {
    for (const pk::entity_t e : this->entities) {
        auto& sprite_animation = pk::EcsController::getComponent<pk::sprite_animation_t, pk::id::sprite_animation>(e);
        sprite_animation.frame++;
        if (sprite_animation.frame >= sprite_animation.speed) {
            sprite_animation.frame = 0;
            sprite_animation.spriteIndex = (sprite_animation.spriteIndex + 1) % sprite_animation.maxSpriteIndex;
            sprite_animation.textureRect.x = (sprite_animation.spriteIndex % sprite_animation.cols) * sprite_animation.textureRect.width;
            sprite_animation.textureRect.y = (sprite_animation.spriteIndex / sprite_animation.cols) * sprite_animation.textureRect.height;
        }
    }
}


void pk::SpriteAnimationSystem::draw(const pk::entity_t e) {
    const pk::transform_t& transform = pk::EcsController::getTransform(e);
    const auto& sprite_animation = pk::EcsController::getComponent<pk::sprite_animation_t, pk::id::sprite_animation>(e);
    DrawTextureRec(sprite_animation.texture, sprite_animation.textureRect, transform.pos, WHITE);
}
