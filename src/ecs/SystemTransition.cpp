//
// Created by vitor on 10/20/24.
//
#include "EcsManager.h"
#include "SystemManager.h"


void pk::TransitionSystem::update([[maybe_unused]] const float dt) {
    const pk::player_t& player = pk::EcsManager::getPlayer();
    for (const pk::entity_t e : this->entities) {
        auto& t = pk::EcsManager::getComponent<pk::transition_t>(e);
        t.isHovered = CheckCollisionRecs(player.actionBox, t.actionBox);
    }
}


void pk::TransitionSystem::draw(const pk::entity_t e) {
    const auto& t = pk::EcsManager::getComponent<pk::transition_t>(e);
    if (t.isHovered) {
        DrawText(
            "Press F",
            t.actionBox.x + t.actionBox.width / 2.0f - 23.0f,
            t.actionBox.y + t.actionBox.height / 2.0f,
            16,
            WHITE
        );
    }
}
