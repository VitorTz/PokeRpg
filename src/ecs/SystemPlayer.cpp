//
// Created by vitor on 10/20/24.
//
#include "EcsManager.h"
#include "raymath.h"
#include "SystemManager.h"
#include "../scene/Scene.h"
#include "../util/util.h"


void pk::PlayerSystem::update(const float dt) {
    pk::player_t& player = pk::EcsManager::getPlayer();
    auto& spriteAnimation = pk::EcsManager::getComponent<pk::sprite_animation_t>(player.playerEntity);
    pk::transform_t& playerTransform = pk::EcsManager::getTransform(player.playerEntity);

    // movement
        Vector2 direction{};
        const pk::Direction lastDirection = player.direction;
        const bool lastMovingStatus = player.isMoving;
        player.isMoving = false;

        if (IsKeyDown(pk::UP_KEY)) {
            direction.y = -1.0f;
            player.direction = pk::Up;
            player.isMoving = true;
        } else if (IsKeyDown(pk::DOWN_KEY)) {
            direction.y = 1.0f;
            player.direction = pk::Down;
            player.isMoving = true;
        }
        if (IsKeyDown(pk::LEFT_KEY)) {
            direction.x = -1.0f;
            player.direction = pk::Left;
            player.isMoving = true;
        } else if (IsKeyDown(pk::RIGHT_KEY)) {
            direction.x = 1.0f;
            player.direction = pk::Right;
            player.isMoving = true;
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
        if (player.isMoving == false) {
            spriteAnimation.textureRect.x = 0.0f;
            spriteAnimation.spriteIndex = 0;
            spriteAnimation.frame = 0;
        } else if (
            player.direction != lastDirection ||
            player.isMoving != lastMovingStatus
        ) {
            spriteAnimation.textureRect.x = pk::PLAYER_SIZE.x;
            spriteAnimation.spriteIndex = 1;
            spriteAnimation.frame = 0;
        }

        switch (player.direction) {
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
        const std::pair<bool, pk::TransitionType> transitionCollide = pk::EcsManager::checkTransition(player.actionBox);
        if (transitionCollide.first == true) {
            switch (transitionCollide.second) {
                case pk::TransitionType::HospitalTransition:
                    pk::gSceneManager.changeScene(pk::HospitalSceneId);
                    break;
                case pk::TransitionType::HouseTransition:
                    pk::gSceneManager.changeScene(pk::HouseSceneId);
                    break;
                case pk::TransitionType::FireArenaTransition:
                    pk::gSceneManager.changeScene(pk::FireArenaSceneId);
                    break;
                case pk::TransitionType::PlantArenaTransition:
                    pk::gSceneManager.changeScene(pk::PlantArenaSceneId);
                    break;
                case pk::TransitionType::WaterArenaTransition:
                    pk::gSceneManager.changeScene(pk::WaterArenaSceneId);
                    break;
                default:
                    break;
            }
        }

}


void pk::PlayerSystem::draw([[maybe_unused]] const pk::entity_t e) {

}


