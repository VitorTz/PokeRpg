//
// Created by vitor on 10/20/24.
//
#include "EcsManager.h"
#include "SystemManager.h"


void pk::SpriteSystem::update([[maybe_unused]] float dt) { }


void pk::SpriteSystem::draw(const pk::entity_t e) {
    const pk::transform_t& transform = pk::EcsManager::getTransform(e);
    const pk::sprite_t& sprite = pk::EcsManager::getComponent<pk::sprite_t>(e);
    DrawTextureV(sprite.texture, transform.pos, WHITE);
}
