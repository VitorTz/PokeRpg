//
// Created by vitor on 10/19/24.
//
#include "EcsManager.h"
#include "../util/TiledMap.h"
#include <algorithm>
#include <fstream>
#include <iostream>

#include "../util/util.h"


std::unordered_map<pk::MapId, std::unique_ptr<pk::EcsManager::ecs_instance_t>> pk::EcsManager::ecsInstanceMap{};
pk::EcsManager::ecs_instance_t* pk::EcsManager::currentMapInstance{nullptr};
pk::MapId pk::EcsManager::currentMapId{};


void pk::EcsManager::init() {
    pk::gTypeId.registerType<pk::transform_t>();
    pk::gTypeId.registerType<pk::sprite_t>();
    pk::gTypeId.registerType<pk::sprite_animation_t>();
    pk::gTypeId.registerType<pk::transition_t>();
    assert(pk::gTypeId.numRegisteredComponents() == pk::NUM_COMPONENTS);
}


void pk::EcsManager::close() {
    pk::EcsManager::ecsInstanceMap.clear();
}


pk::entity_t pk::EcsManager::spriteCreate(const pk::zindex_t zindex, const char* fileName) {
    const pk::entity_t e = entityCreate(zindex, true);
    addComponent(e, pk::sprite_t{fileName});
    const auto& sprite = getComponent<pk::sprite_t>(e);
    getTransform(e).size = Vector2{
        static_cast<float>(sprite.texture.width),
        static_cast<float>(sprite.texture.height)
    };
    return e;
}

pk::entity_t pk::EcsManager::spriteCreate(
    const pk::zindex_t zindex,
    const float posX,
    const float posY,
    const char* fileName
) {
    const pk::entity_t e = entityCreate(zindex, true);
    addComponent(e, pk::sprite_t{fileName});
    const auto& sprite = getComponent<pk::sprite_t>(e);
    pk::transform_t& transform = getTransform(e);
    transform.pos = Vector2{posX, posY};
    transform.size = Vector2{
        static_cast<float>(sprite.texture.width),
        static_cast<float>(sprite.texture.height)
    };
    return e;
}


void pk::EcsManager::setCurrentEcsInstance(const pk::MapId mapId) {
    assert(ecsInstanceMap.find(mapId) != ecsInstanceMap.end());
    currentMapId = mapId;
    currentMapInstance = ecsInstanceMap[mapId].get();
}


pk::MapId pk::EcsManager::getCurrentMapId() {
    return currentMapId;
}


void pk::EcsManager::ecsInstanceCreate(const pk::MapId mapId) {
    if (ecsInstanceMap.find(mapId) != ecsInstanceMap.end()) {
        return;
    }
    ecsInstanceMap.emplace(mapId, std::make_unique<pk::EcsManager::ecs_instance_t>(mapId));
    pk::TiledMap::loadMap(mapId);
}


pk::player_t &pk::EcsManager::getPlayer() {
    return currentMapInstance->player;
}


pk::player_t& pk::EcsManager::getPlayer(const pk::MapId mapId) {
    assert(ecsInstanceMap.find(mapId) != ecsInstanceMap.end());
    return ecsInstanceMap[mapId]->player;
}


void pk::EcsManager::ecsInstanceDestroy(const pk::MapId mapId) {
    ecsInstanceMap.erase(mapId);
}


pk::entity_t pk::EcsManager::entityCreate(
    const pk::zindex_t zindex,
    const bool addToCamera
) {
    const pk::entity_t e = currentMapInstance->entity.entityCreate();
    addComponent(e, pk::transform_t{zindex});
    if (addToCamera) currentMapInstance->camera.insert(e, zindex);
    return e;
}


void pk::EcsManager::entityDestroy(const pk::entity_t e) {
    currentMapInstance->entitiesToDestroy.push(e);
}


void pk::EcsManager::entityDestroyAll() {
    currentMapInstance->shouldDestroyAllEntities = true;
}

pk::transform_t& pk::EcsManager::getTransform(const pk::entity_t e) {
    return currentMapInstance->component.at<pk::transform_t>(e);
}


void pk::EcsManager::addStaticCollision(const Rectangle rect) {
    currentMapInstance->staticCollisions.emplace_back(rect);
}


void pk::EcsManager::addStaticCollision(const pk::entity_t e, const float width, const float height) {
    const pk::transform_t& t = getTransform(e);
    addStaticCollision(
        {
            t.pos.x + t.size.x / 2.0f - width / 2.0f,
            t.pos.y + t.size.y - height,
            width,
            height
        }
    );
}


bool pk::EcsManager::checkStaticCollision(const Rectangle& rect) {
    return std::any_of(
        currentMapInstance->staticCollisions.begin(),
        currentMapInstance->staticCollisions.end(),
        [rect](const Rectangle& otherRect) {
            return CheckCollisionRecs(rect, otherRect);;
        }
    );
}


std::pair<bool, pk::entity_t> pk::EcsManager::checkEntityCollision(const pk::entity_t e) {
    std::pair<bool, pk::entity_t> r{false, 0};
    const pk::transform_t& transform = getTransform(e);
    const pk::ComponentArray<pk::transform_t>* arr = currentMapInstance->component.getComponentArray<pk::transform_t>();
    for (std::size_t i = 0; i < arr->size(); i++) {
        if (pk::checkTransformCollision(transform, arr->componentAtIndex(i))) {
            r.first = true;
            r.second = arr->entityAtIndex(i);
            break;
        }
    }
    return r;
}


std::pair<bool, pk::TransitionType> pk::EcsManager::checkTransition(const Rectangle& rect) {
    std::pair<bool, pk::TransitionType> r{};
    const pk::ComponentArray<pk::transition_t>* arr = currentMapInstance->component.getComponentArray<pk::transition_t>();
    if (IsKeyPressed(pk::ACTION_KEY)) {
        for (const pk::transition_t& t : *arr) {
            if (CheckCollisionRecs(t.actionBox, rect) && t.isHovered) {
                r.first = true;
                r.second = t.type;
                break;
            }
        }
    }
    return r;
}


void pk::EcsManager::entityDestroyImmediate(const pk::entity_t e) {
    currentMapInstance->camera.erase(e, getTransform(e).zindex);
    currentMapInstance->entity.entityDestroy(e);
    currentMapInstance->component.entityDestroy(e);
    currentMapInstance->system.entityDestroy(e);
}


void pk::EcsManager::entityDestroyAllImmediate() {
    currentMapInstance->camera.clear();
    currentMapInstance->entity.clear();
    currentMapInstance->component.clear();
    currentMapInstance->system.clear();
    currentMapInstance->shouldDestroyAllEntities = false;
    currentMapInstance->entitiesToDestroy = std::queue<pk::entity_t>();
}


void pk::EcsManager::update(const float dt) {
    currentMapInstance->system.update(dt);
    currentMapInstance->camera.handleMouseInput(dt);

    if (currentMapInstance->shouldDestroyAllEntities) {
        entityDestroyAllImmediate();
    }

    while (currentMapInstance->entitiesToDestroy.empty() == false) {
        const pk::entity_t e = currentMapInstance->entitiesToDestroy.front();
        currentMapInstance->entitiesToDestroy.pop();
        entityDestroyImmediate(e);
    }
}


void pk::EcsManager::drawDebug() {
    DrawFPS(10, 10);
    currentMapInstance->camera.beginDrawing();
        // Draw Collisions
        for (const Rectangle& rect : currentMapInstance->staticCollisions) {
            DrawRectangleLinesEx(rect, 2.0f, BLUE);
        }
        // Draw Player CollideBox and ActionBox
        DrawRectangleLinesEx(currentMapInstance->player.collisionBox, 2.0f, RED);
        DrawRectangleLinesEx(currentMapInstance->player.actionBox, 2.0f, YELLOW);
    currentMapInstance->camera.endDrawing();
}


void pk::EcsManager::draw() {
    currentMapInstance->camera.draw(&currentMapInstance->system);
    if (pk::DEBUG_MODE) {
        pk::EcsManager::drawDebug();
    }
}


