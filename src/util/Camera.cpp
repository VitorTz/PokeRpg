#include "../ecs/ECS.hpp"
#include "Camera.hpp"
#include "SceneId.hpp"
#include "raylib.h"
#include "types.hpp"
#include <algorithm>
#include <cassert>
#include <cstddef>


pk::Camera::Camera(const pk::SceneId sceneId) {
    for (pk::zindex_t z = pk::CAMERA_MIN_ZINDEX; z <= pk::CAMERA_MAX_ZINDEX; z++) {
        this->entities[z].reserve(pk::MAX_ENTITIES);
    }
    const pk::map_info_t& mapInfo = pk::MAP_INFO[sceneId];
    this->maxWidth = mapInfo.width - pk::SCREEN_CENTERX;
    this->maxHeight = mapInfo.height - pk::SCREEN_CENTERY;
    this->reset();
}


void pk::Camera::reset() {
    this->camera = {
        pk::SCREEN_CENTER,
        pk::SCREEN_CENTER,
        0.0f,
        1.0f
    };
}


void pk::Camera::insert(const pk::entity_t e, const pk::zindex_t zindex) {
    assert(zindex >= pk::CAMERA_MIN_ZINDEX && zindex <= pk::CAMERA_MAX_ZINDEX);
    if (this->onCamera[e] == false) {
        this->onCamera[e] = true;
        this->entities[zindex].emplace_back(0.0f, e);
        this->mSize++;
    }
}


void pk::Camera::erase(const pk::entity_t e, const pk::zindex_t zindex) {
    assert(zindex >= pk::CAMERA_MIN_ZINDEX && zindex <= pk::CAMERA_MAX_ZINDEX);
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



void pk::Camera::setTarget(const Vector2 target) {
    this->camera.target.x = std::clamp(target.x, pk::SCREEN_CENTERX, this->maxWidth);
    this->camera.target.y = std::clamp(target.y, pk::SCREEN_CENTERY, this->maxHeight);
}


void pk::Camera::addZoom(const float delta) {
    this->camera.zoom = std::clamp(
        this->camera.zoom + delta,
        pk::CAMERA_MIN_ZOOM,
        pk::CAMERA_MAX_ZOOM
    );
}


void pk::Camera::setZoom(const float zoom) {
    this->camera.zoom = std::clamp(
        zoom,
        pk::CAMERA_MIN_ZOOM,
        pk::CAMERA_MAX_ZOOM
    );
}


void pk::Camera::handleInput(const float dt) {
    this->addZoom(GetMouseWheelMove() * 2.0f * dt);
}


void pk::Camera::beginDrawing() const {
    BeginMode2D(this->camera);
}


void pk::Camera::endDrawing() const {
    EndMode2D();
}


void pk::Camera::draw(
    const pk::SystemManager* system
) {
    for (auto& pair : this->entities) {
        for (auto& pair1 : pair.second) {
            const pk::transform_t& t = pk::ECS::getTransform(pair1.second);
            pair1.first = t.pos.y + t.size.y / 2.0f;
        }
        std::sort(pair.second.begin(), pair.second.end());
        system->draw(pair.second);
    }
}


void pk::Camera::clear() {
    for (auto& pair : this->entities) {
        pair.second.clear();
    }
    for (bool& b : this->onCamera) {
        b = false;
    }
}


std::size_t pk::Camera::size() const {
    return this->mSize;
}
