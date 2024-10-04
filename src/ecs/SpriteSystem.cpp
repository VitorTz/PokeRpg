//
// Created by vitor on 10/3/24.
//
#include "System.h"
#include "ECS.h"


void pk::SpriteSystem::update(const float dt) {

}


void pk::SpriteSystem::draw(const pk::entity_t e) {
    pk::ECS* ecs = pk::ECS::getEcsInstance(this->mapId);
    const pk::transform_t& t = ecs->getTransform(e);
    const pk::sprite_t& s = ecs->getComponent<pk::sprite_t>(e);
    DrawTextureV(s.texture, t.pos, WHITE);
}

