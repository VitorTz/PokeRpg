//
// Created by vitor on 10/20/24.
//
#include <iostream>
#include "EcsManager.h"
#include "raymath.h"
#include "SystemManager.h"
#include "../util/util.h"


void pk::PlayerSystem::update(const float dt) {
    pk::player_t& player = pk::EcsManager::getPlayer();
    auto& spriteAnimation = pk::EcsManager::getComponent<pk::sprite_animation_t>(player.playerEntity);
    pk::transform_t& playerTransform = pk::EcsManager::getTransform(player.playerEntity);

    // movement
        Vector2 direction{};
        const pk::Direction lastDirection = player.status.direction;
        const bool lastMovingStatus = player.status.isMoving;
        player.status.isMoving = false;

        if (IsKeyDown(KEY_W)) {
            direction.y = -1.0f;
            player.status.direction = pk::Up;
            player.status.isMoving = true;
        } else if (IsKeyDown(KEY_S)) {
            direction.y = 1.0f;
            player.status.direction = pk::Down;
            player.status.isMoving = true;
        }

        if (IsKeyDown(KEY_A)) {
            direction.x = -1.0f;
            player.status.direction = pk::Left;
            player.status.isMoving = true;
        } else if (IsKeyDown(KEY_D)) {
            direction.x = 1.0f;
            player.status.direction = pk::Right;
            player.status.isMoving = true;
        }

        direction = Vector2Normalize(direction);
        const float deltaX = direction.x * pk::PLAYER_SPEED * dt;
        const float deltaY = direction.y * pk::PLAYER_SPEED * dt;

        // horizontal movement
            playerTransform.pos.x += deltaX;
            player.collisionBox.x = playerTransform.pos.x + playerTransform.size.x / 2.0f - player.collisionBox.width / 2.0f;
            player.collisionBox.y = playerTransform.pos.y + playerTransform.size.y - player.collisionBox.height;
            if (pk::EcsManager::checkStaticCollision(player.collisionBox)) {
                playerTransform.pos.x -= deltaX;
            }

        // vertical movement
            playerTransform.pos.y += deltaY;
            player.collisionBox.x = playerTransform.pos.x + playerTransform.size.x / 2.0f - player.collisionBox.width / 2.0f;
            player.collisionBox.y = playerTransform.pos.y + playerTransform.size.y - player.collisionBox.height;
            if (pk::EcsManager::checkStaticCollision(player.collisionBox)) {
                playerTransform.pos.y -= deltaY;
            }
            player.center = pk::getCenter(playerTransform);

    // Sprite Animation and ActionBox
        if (player.status.isMoving == false) {
            spriteAnimation.textureRect.x = 0.0f;
            spriteAnimation.spriteIndex = 0;
            spriteAnimation.frame = 0;
        } else if (
            player.status.direction != lastDirection ||
            player.status.isMoving != lastMovingStatus
        ) {
            spriteAnimation.textureRect.x = pk::PLAYER_SIZE.x;
            spriteAnimation.spriteIndex = 1;
            spriteAnimation.frame = 0;
        }

        switch (player.status.direction) {
            case pk::Down:
                spriteAnimation.textureRect.y = 0.0f;
                player.actionBox.width = pk::PLAYER_ACTION_BOX.height;
                player.actionBox.height = pk::PLAYER_ACTION_BOX.width;
                player.actionBox.x = player.center.x - pk::PLAYER_ACTION_BOX.height / 2.0f;
                player.actionBox.y = player.center.y + 20.0f;
                break;
            case pk::Left:
                spriteAnimation.textureRect.y = pk::PLAYER_SIZE.y;
                player.actionBox.width = pk::PLAYER_ACTION_BOX.width;
                player.actionBox.height = pk::PLAYER_ACTION_BOX.height;
                player.actionBox.x = player.center.x - pk::PLAYER_ACTION_BOX.width;
                player.actionBox.y = playerTransform.pos.y + playerTransform.size.y - pk::PLAYER_ACTION_BOX.height;
                break;
            case pk::Right:
                spriteAnimation.textureRect.y = pk::PLAYER_SIZE.y * 2.0f;
                player.actionBox.width = pk::PLAYER_ACTION_BOX.width;
                player.actionBox.height = pk::PLAYER_ACTION_BOX.height;
                player.actionBox.x = player.center.x;
                player.actionBox.y = playerTransform.pos.y + playerTransform.size.y - pk::PLAYER_ACTION_BOX.height;
                break;
            case pk::Up:
                spriteAnimation.textureRect.y = pk::PLAYER_SIZE.y * 3.0f;
                player.actionBox.width = pk::PLAYER_ACTION_BOX.height;
                player.actionBox.height = pk::PLAYER_ACTION_BOX.width;
                player.actionBox.x = player.center.x - pk::PLAYER_ACTION_BOX.height / 2.0f;
                player.actionBox.y = player.center.y - pk::PLAYER_ACTION_BOX.width;
                break;
        }

    // Transition
        const std::pair<bool, pk::TransitionType> transitionCollide = pk::EcsManager::checkTransitionCollide(player.actionBox);
        if (transitionCollide.first == true) {
            std::cout << static_cast<int>(transitionCollide.second) << '\n';
        }

}


void pk::PlayerSystem::draw([[maybe_unused]] const pk::entity_t e) {

}


