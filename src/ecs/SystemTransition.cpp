//
// Created by vitor on 10/20/24.
//
#include "EcsManager.h"
#include "SystemManager.h"


void pk::TransitionSystem::update([[maybe_unused]] const float dt) {
    const pk::player_t& player = pk::EcsManager::getPlayer();
    for (const pk::entity_t e : this->entities) {
        auto& transition = pk::EcsManager::getComponent<pk::transition_t>(e);
        transition.isHovered = CheckCollisionRecs(player.actionBox, transition.actionBox);
    }
}


void pk::TransitionSystem::draw(const pk::entity_t e) {
    const auto& transition = pk::EcsManager::getComponent<pk::transition_t>(e);
    if (transition.isHovered) {
        DrawText(
            "Press F",
            transition.actionBox.x + transition.actionBox.width / 2.0f - 23.0f,
            transition.actionBox.y + transition.actionBox.height / 2.0f,
            16,
            WHITE
        );
    }
}
