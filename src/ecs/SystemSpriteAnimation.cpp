//
// Created by vitor on 10/20/24.
//
#include "EcsManager.h"
#include "SystemManager.h"


void pk::SpriteAnimationSystem::update([[maybe_unused]] float dt) {
    for (const pk::entity_t e : this->entities) {
        auto& spriteAnimation = pk::EcsManager::getComponent<pk::sprite_animation_t>(e);
        spriteAnimation.frame++;
        if (spriteAnimation.frame > spriteAnimation.maxFrame) {
            spriteAnimation.frame = 0;
            spriteAnimation.spriteIndex = (spriteAnimation.spriteIndex + 1) % spriteAnimation.maxSpriteIndex;
            spriteAnimation.textureRect.x = static_cast<float>(spriteAnimation.spriteIndex) * spriteAnimation.textureRect.width;
        }
    }
}


void pk::SpriteAnimationSystem::draw(const pk::entity_t e) {
    const pk::transform_t& transform = pk::EcsManager::getTransform(e);
    const pk::sprite_animation_t& spriteAnimation = pk::EcsManager::getComponent<pk::sprite_animation_t>(e);
    DrawTextureRec(spriteAnimation.sprite.texture, spriteAnimation.textureRect, transform.pos, WHITE);
}
