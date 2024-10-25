#include "../util/TiledMap.hpp"
#include "ECS.hpp"

#include <algorithm>

#include "components.hpp"
#include "raylib.h"
#include <cassert>
#include <memory>
#include <queue>
#include <unordered_map>


std::unordered_map<pk::SceneId, std::unique_ptr<pk::ECS::ecs_instance_t>> pk::ECS::ecsInstanceMap{};
pk::ECS::ecs_instance_t* pk::ECS::currentEcsInstance{};
pk::SceneId pk::ECS::currentSceneId{};


void pk::ECS::ecsInstanceCreate(const pk::SceneId sceneId) {
    if (ecsInstanceMap.find(sceneId) == ecsInstanceMap.end()) {
        ecsInstanceMap.emplace(sceneId, std::make_unique<pk::ECS::ecs_instance_t>(sceneId));        
        setCurrentScene(sceneId);
        pk::loadTiledMap(sceneId);        
    }
}


void pk::ECS::ecsInstanceDestroy(const pk::SceneId sceneId) {
    ecsInstanceMap.erase(sceneId);
}


void pk::ECS::ecsInstanceDestroyAll() {
    ecsInstanceMap.clear();
}


void pk::ECS::setCurrentScene(const pk::SceneId sceneId) {
    assert(ecsInstanceMap.find(sceneId) != ecsInstanceMap.end());
    currentSceneId = sceneId;
    currentEcsInstance = ecsInstanceMap[sceneId].get();
}


pk::entity_t pk::ECS::entityCreate(const pk::zindex_t zindex, const bool addToCamera) {
    const pk::entity_t e = currentEcsInstance->entity.create();
    componentAdd(e, pk::transform_t{zindex});    
    if (addToCamera) currentEcsInstance->camera.insert(e, zindex);
    return e;
}


pk::entity_t pk::ECS::entityCreate(const pk::zindex_t zindex, const float x, const float y, const bool addToCamera) {
    const pk::entity_t e = currentEcsInstance->entity.create();
    componentAdd(e, pk::transform_t{zindex});    
    if (addToCamera) currentEcsInstance->camera.insert(e, zindex);
    getTransform(e).pos = Vector2{x, y};
    return e;
}


pk::entity_t pk::ECS::spriteCreate(const pk::zindex_t zindex, const char* imagePath) {
    const pk::entity_t e = entityCreate(zindex, true);
    componentAdd(e, pk::sprite_t{imagePath});
    pk::sprite_t& sprite = componentGet<pk::sprite_t>(e);
    getTransform(e).size = Vector2{
        static_cast<float>(sprite.texture.width),
        static_cast<float>(sprite.texture.height)
    };
    return e;
}


pk::entity_t pk::ECS::spriteCreate(const pk::zindex_t zindex, const float x, const float y, const char* imagePath) {
    const pk::entity_t e = entityCreate(zindex, x, y, true);
    componentAdd(e, pk::sprite_t{imagePath});
    pk::sprite_t& sprite = componentGet<pk::sprite_t>(e);
    getTransform(e).size = Vector2{
        static_cast<float>(sprite.texture.width),
        static_cast<float>(sprite.texture.height)
    };
    return e;
}


void pk::ECS::entityDestroy(const pk::entity_t e) {
    currentEcsInstance->entitiesToDestroy.push(e);
}


void pk::ECS::entityDestroyImmediate(const pk::entity_t e) {
    currentEcsInstance->camera.erase(e, getTransform(e).zindex);
    currentEcsInstance->entity.destroy(e);
    currentEcsInstance->component.entityDestroy(e);
    currentEcsInstance->system.entityDestroy(e);    
}


void pk::ECS::entityDestroyAll() {
    currentEcsInstance->shouldDestroyAllEntities = true;
}


void pk::ECS::entityDestroyAllImmediate() {
    currentEcsInstance->camera.clear();
    currentEcsInstance->entity.clear();
    currentEcsInstance->component.clear();
    currentEcsInstance->system.clear();
    currentEcsInstance->entitiesToDestroy = std::queue<pk::entity_t>();
    currentEcsInstance->shouldDestroyAllEntities = false;
}


void pk::ECS::ecsInstanceUpdate(const float dt) {
    currentEcsInstance->system.update(dt);
    pk::playerUpdate(currentEcsInstance->player, dt);
    currentEcsInstance->camera.handleInput(dt);

    if (currentEcsInstance->shouldDestroyAllEntities == true) {
        currentEcsInstance->shouldDestroyAllEntities = false;
        entityDestroyAllImmediate();
    }

    while (currentEcsInstance->entitiesToDestroy.empty() == false) {
        const pk::entity_t e = currentEcsInstance->entitiesToDestroy.front();
        currentEcsInstance->entitiesToDestroy.pop();
        entityDestroyImmediate(e);
    }
}


void pk::ECS::ecsInstanceDraw() {
    if (pk::DEBUB_MODE) {
        DrawFPS(10, 10);
    }
    currentEcsInstance->camera.beginDrawing();
    // ECS
        currentEcsInstance->camera.draw(&currentEcsInstance->system);
        currentEcsInstance->transition.draw();
    // Debug
        if (pk::DEBUB_MODE) {
            // Draw Static Collision
            for (const Rectangle& rect : currentEcsInstance->staticCollisions) {
                DrawRectangleLinesEx(rect, 2.0f, BLUE);
            }
            pk::playerDebug(currentEcsInstance->player);
        }
    currentEcsInstance->camera.endDrawing();
}


pk::Camera* pk::ECS::getCamera(const pk::SceneId sceneId) {
    assert(ecsInstanceMap.find(sceneId) != ecsInstanceMap.end());
    return &ecsInstanceMap[sceneId]->camera;
}


pk::Camera* pk::ECS::getCamera() {
    return &currentEcsInstance->camera;
}


void pk::ECS::staticCollisionAdd(const Rectangle& rect) {
    currentEcsInstance->staticCollisions.emplace_back(rect);
}


void pk::ECS::staticCollisionAdd(const float x, const float y, const float width, const float height) {
    currentEcsInstance->staticCollisions.emplace_back(Rectangle{x, y, width, height});
}


bool pk::ECS::checkCollision(const Rectangle &rect) {
    return std::any_of(
        currentEcsInstance->staticCollisions.begin(),
        currentEcsInstance->staticCollisions.end(),
        [rect](const Rectangle& otherRect) {
            return CheckCollisionRecs(rect, otherRect);
        }
    );
}


void pk::ECS::staticCollisionAdd(const pk::entity_t e, const float width, const float height) {
    const pk::transform_t& t = getTransform(e);
    currentEcsInstance->staticCollisions.emplace_back(
        Rectangle{
            t.pos.x + t.size.x / 2.0f - width / 2.0f,
            t.pos.y + t.size.y - height,
            width,
            height
        }
    );
}


void pk::ECS::staticCollisionClear() {
    currentEcsInstance->staticCollisions.clear();
}


void pk::ECS::transitionAdd(const pk::SceneId sceneId, const Rectangle &rect) {
    currentEcsInstance->transition.insert(sceneId, rect);
}


void pk::ECS::checkTransition(const Rectangle& rect) {
    currentEcsInstance->transition.checkForTransition(rect);
}


pk::transform_t& pk::ECS::getTransform(const pk::entity_t e) {
    return currentEcsInstance->component.at<pk::transform_t>(e);
}


pk::player_t& pk::ECS::getPlayer() {
    return currentEcsInstance->player;
}

