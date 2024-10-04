//
// Created by vitor on 10/3/24.
//
#include "Camera.h"
#include "../ecs/ECS.h"


pk::Camera::Camera(const pk::TiledMapId mapId) : mapId(mapId) {
    for (pk::zindex_t z = pk::CAMERA_ZINDEX_MIN; z <= pk::CAMERA_ZINDEX_MAX; z++) {
        this->entities[z].reserve(pk::MAX_ENTITIES);
    }
    this->entitiesOnCamera.reserve(pk::MAX_ENTITIES);
    this->reset();
    const pk::tiled_map_t& tiledMap = pk::TILED_MAPS[mapId];
    this->maxTargetX = tiledMap.width - pk::SCREEN_CENTERX;
    this->maxTargetY = tiledMap.height - pk::SCREEN_CENTERY;
}


void pk::Camera::reset() {
    this->camera = Camera2D{
        Vector2{pk::SCREEN_CENTERX, pk::SCREEN_CENTERY},
        Vector2{pk::SCREEN_CENTERX, pk::SCREEN_CENTERY},
        0.0f,
        1.0f
    };
}


void pk::Camera::setTarget(const float x, const float y) {
    this->camera.target.x = std::clamp(x, pk::SCREEN_CENTERX, this->maxTargetX);
    this->camera.target.y = std::clamp(y, pk::SCREEN_CENTERY, this->maxTargetY);
}


void pk::Camera::beginDrawing() const {
    BeginMode2D(this->camera);
}


void pk::Camera::endDrawing() const {
    EndMode2D();
}


void pk::Camera::insert(const pk::entity_t e, const pk::zindex_t zindex) {
    if (this->entitiesOnCamera.find(e) == this->entitiesOnCamera.end()) {
        this->entitiesOnCamera.insert(e);
        this->entities[zindex].emplace_back(0.0f, e);
    }
}


void pk::Camera::erase(const pk::entity_t e, const pk::zindex_t zindex) {
    if (this->entitiesOnCamera.find(e) != this->entitiesOnCamera.end()) {
        this->entitiesOnCamera.erase(e);
        std::vector<std::pair<float, pk::entity_t>>& v = this->entities[zindex];
        for (std::size_t i = 0; i < v.size(); i++) {
            if (v[i].second == e) {
                v.erase(v.begin() + i);
                return;
            }
        }
    }
}


void pk::Camera::draw(pk::SystemManager *system) {
    // sort by zindex and center y pos
    pk::ECS* const ecs = pk::ECS::getEcsInstance(this->mapId);
    this->beginDrawing();
        for (std::pair<const unsigned char, std::vector<std::pair<float, pk::entity_t>>>& pair : this->entities) {
            for (std::pair<float, pk::entity_t>& pair1 : pair.second) {
                const pk::transform_t& t = ecs->getTransform(pair1.second);
                pair1.first = t.pos.y + t.size.y / 2.0f;
            }
            std::sort(pair.second.begin(), pair.second.end());
            system->draw(pair.second);
        }
    this->endDrawing();
}


void pk::Camera::clear() {
    for (auto& pair : this->entities) {
        pair.second.clear();
    }
    this->entitiesOnCamera.clear();
}


std::size_t pk::Camera::size() const {
    return this->entitiesOnCamera.size();
}
