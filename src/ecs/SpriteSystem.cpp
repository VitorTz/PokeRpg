#include "System.hpp"
#include "ECS.hpp"


void pk::SpriteSystem::update(
    [[maybe_unused]] const float dt,
    [[maybe_unused]] const std::unordered_set<pk::entity_t>& entities
) const {
    
}


void pk::SpriteSystem::draw(const pk::entity_t e) const {
    const pk::transform_t& transform = pk::ECS::getTransform(e);
    const pk::sprite_t& sprite = pk::ECS::componentGet<pk::sprite_t>(e);
    DrawTextureV(sprite.texture, transform.pos, WHITE);
}