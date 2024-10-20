//
// Created by vitor on 10/19/24.
//
#include "Camera.h"
#include <algorithm>
#include "../ecs/EcsManager.h"


pk::Camera::Camera(const pk::MapId mapId) {
    for (pk::zindex_t z = pk::ZINDEX_MIN; z <= pk::ZINDEX_MAX; z++) {
        this->entities[z].reserve(pk::MAX_ENTITIES);
    }
    const pk::tiled_map_info_t& mapInfo = pk::TILED_MAP_INFO[mapId];
    this->maxXOffset = mapInfo.width - pk::SCREEN_CENTERX;
    this->maxYOffset = mapInfo.height - pk::SCREEN_CENTERY;
    this->reset();
}


void pk::Camera::insert(const pk::entity_t e, const pk::zindex_t zindex) {
    if (this->onCamera[e] == false) {
        this->onCamera[e] = true;
        this->entities[zindex].emplace_back(0.0f, e);
        this->mSize++;
    }
}


void pk::Camera::erase(const pk::entity_t e, const pk::zindex_t zindex) {
    if (this->onCamera[e] == true) {
        this->onCamera[e] = false;
        std::vector<std::pair<float, pk::entity_t>>& v = this->entities[zindex];
        for (std::size_t i = 0; i < v.size(); i++) {
            if (v[i].second == e) {
                v.erase(v.begin() + i);
                this->mSize--;
                return;
            }
        }
    }
}


void pk::Camera::beginDrawing() const {
    BeginMode2D(this->camera2D);
}


void pk::Camera::endDrawing() const {
    EndMode2D();
}


void pk::Camera::draw(pk::SystemManager *system) {
    this->setTarget(pk::EcsManager::getPlayer().center);
    this->beginDrawing();
    for (auto& pair : this->entities) {
        for (auto& pair1 : pair.second) {
            const pk::transform_t& t = pk::EcsManager::getTransform(pair1.second);
            pair1.first = t.pos.y + t.size.y / 2.0f;
        }
        std::sort(pair.second.begin(), pair.second.end());
        system->draw(pair.second);
    }
    this->endDrawing();
}



void pk::Camera::setTarget(const Vector2 target) {
    this->camera2D.target.x = std::clamp(target.x, pk::SCREEN_CENTERX, this->maxXOffset);
    this->camera2D.target.y = std::clamp(target.y, pk::SCREEN_CENTERY, this->maxYOffset);
}


Vector2 pk::Camera::getTarget() const {
    return this->camera2D.target;
}


void pk::Camera::clear() {
    for (auto& pair : this->entities) {
        pair.second.clear();
    }
}


void pk::Camera::reset() {
    this->camera2D = {
        .offset = pk::SCREEN_CENTER,
        .target = pk::SCREEN_CENTER,
        .rotation = 0.0f,
        .zoom = 1.0f
    };
}


std::size_t pk::Camera::size() const {
    return this->mSize;
}

