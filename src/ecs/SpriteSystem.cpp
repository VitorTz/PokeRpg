//
// Created by vitor on 10/13/24.
//
#include "SystemManager.hpp"
#include "EcsController.hpp"


void pk::SpriteSystem::update([[maybe_unused]] const float dt) {

}


void pk::SpriteSystem::draw(const pk::entity_t e) {
    const pk::transform_t& transform = pk::EcsController::getTransform(e);
    const pk::sprite_t& sprite = pk::EcsController::getComponent<pk::sprite_t, pk::id::sprite>(e);
    DrawTextureV(sprite.texture, transform.pos, WHITE);
}
