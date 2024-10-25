//
// Created by vitor on 10/24/24.
//
#include "player.hpp"
#include "ECS.hpp"
#include "raymath.h"
#include "../util/util.hpp"


void pk::playerUpdate(pk::player_t &player, const float dt) {
    pk::transform_t& transform = pk::ECS::getTransform(player.playerEntity);
    pk::transform_t& shadowTransform = pk::ECS::getTransform(player.shadowEntity);
    auto& character = pk::ECS::componentGet<pk::character_t>(player.playerEntity);

    // movement
        Vector2 directionVec{0.0f, 0.0f};
        transform.isMoving = false;
        if (IsKeyDown(pk::M_UP_KEY)) {
            transform.direction = pk::Up;
            transform.isMoving = true;
            directionVec.y = -1.0f;
        } else if (IsKeyDown(pk::M_DOWN_KEY)) {
            transform.direction = pk::Down;
            transform.isMoving = true;
            directionVec.y = 1.0f;
        }
        if (IsKeyDown(pk::M_LEFT_KEY)) {
            transform.direction = pk::Left;
            transform.isMoving = true;
            directionVec.x = -1.0f;
        } else if (IsKeyDown(pk::M_RIGHT_KEY)) {
            transform.direction = pk::Right;
            transform.isMoving = true;
            directionVec.x = 1.0f;
        }

        directionVec = Vector2Normalize(directionVec);

        const float deltaX = dt * directionVec.x * pk::PLAYER_SPEED;
        const float deltaY = dt * directionVec.y * pk::PLAYER_SPEED;

        // horizontal movement
        transform.pos.x += deltaX;
        player.collideBox.x = transform.pos.x + transform.size.x / 2.0f - player.collideBox.width / 2.0f;
        player.collideBox.y = transform.pos.y + transform.size.y - player.collideBox.height;
        if (pk::ECS::checkCollision(player.collideBox)) {
            transform.pos.x -= deltaX;
        }

        // vertical movement
        transform.pos.y += deltaY;
        player.collideBox.x = transform.pos.x + transform.size.x / 2.0f - player.collideBox.width / 2.0f;
        player.collideBox.y = transform.pos.y + transform.size.y - player.collideBox.height;
        if (pk::ECS::checkCollision(player.collideBox)) {
            transform.pos.y -= deltaY;
        }
        const Vector2 playerCenter = pk::getCenter(transform);
        shadowTransform.pos.x = transform.pos.x + transform.size.x / 2.0f - shadowTransform.size.x / 2.0f;
        shadowTransform.pos.y = transform.pos.y + transform.size.y - shadowTransform.size.y;
        pk::ECS::getCamera()->setTarget(playerCenter);

    // Action
    switch (transform.direction) {
        case pk::Left:
            player.actionBox = {
                playerCenter.x - pk::PLAYER_ACTION_BOX_W,
                transform.pos.y + transform.size.y - pk::PLAYER_ACTION_BOX_H,
                pk::PLAYER_ACTION_BOX_W,
                pk::PLAYER_ACTION_BOX_H
            };
            break;
        case pk::Right:
            player.actionBox = {
                playerCenter.x,
                transform.pos.y + transform.size.y - pk::PLAYER_ACTION_BOX_H,
                pk::PLAYER_ACTION_BOX_W,
                pk::PLAYER_ACTION_BOX_H
            };
            break;
        case pk::Up:
            player.actionBox = {
                playerCenter.x - pk::PLAYER_ACTION_BOX_H / 2.0f,
                playerCenter.y - pk::PLAYER_ACTION_BOX_W,
                pk::PLAYER_ACTION_BOX_H,
                pk::PLAYER_ACTION_BOX_W
            };
            break;
        case pk::Down:
            player.actionBox = {
                playerCenter.x - pk::PLAYER_ACTION_BOX_H / 2.0f,
                playerCenter.y + 30.0f,
                pk::PLAYER_ACTION_BOX_H,
                pk::PLAYER_ACTION_BOX_W
            };
            break;
        default:
            break;
    }

    // Transition
    pk::ECS::checkTransition(player.actionBox);

}


void pk::playerDebug(const pk::player_t &player) {
    if (pk::DEBUB_MODE) {
        DrawRectangleLinesEx(player.collideBox, 2.0f, RED);
        DrawRectangleLinesEx(player.actionBox, 2.0f, BLUE);
    }
}
