#include "Camera.hpp"
#include "../ecs/EcsController.hpp"


pk::Camera::Camera() {
    for (pk::zindex_t z = pk::CAMERA_MIN_ZINDEX; z <= pk::CAMERA_MAX_ZINDEX; z++) {
        this->zindexToEntities[z].reserve(pk::MAX_ENTITIES);
    }
    this->reset();
}


void pk::Camera::reset() {
    this->camera2D = Camera2D{
        .offset = pk::SCREEN_CENTER,
        .target = pk::SCREEN_CENTER,
        .rotation = 0.0f,
        .zoom = 1.0f
    };
    this->cameraRect = Rectangle{
        this->camera2D.target.x - this->camera2D.offset.x,
        this->camera2D.target.y - this->camera2D.offset.y,
        pk::SCREEN_W,
        pk::SCREEN_H
    };
}

void pk::Camera::moveTarget(const float x, const float y) {
    this->camera2D.target.x += x;
    this->camera2D.target.y += y;
    this->cameraRect.x += x;
    this->cameraRect.y += y;
}


void pk::Camera::setTarget(const float x, const float y) {
    this->camera2D.target.x = x;
    this->camera2D.target.y = y;
    this->cameraRect.x = x - this->camera2D.offset.x;
    this->cameraRect.y = y - this->camera2D.offset.y;
}


void pk::Camera::insert(const pk::entity_t e, const pk::zindex_t zindex) {
    assert(zindex >= pk::CAMERA_MIN_ZINDEX && zindex <= pk::CAMERA_MAX_ZINDEX);
    if (this->onCamera[e] == false) {
        this->onCamera[e] = true;
        this->zindexToEntities[zindex].emplace_back(0.0f, e);
        this->mSize++;
    }
}


void pk::Camera::erase(const pk::entity_t e, const pk::zindex_t zindex) {
    if (this->onCamera[e] == true) {
        this->onCamera[e] = false;
        std::vector<std::pair<float, pk::entity_t>>& v = this->zindexToEntities[zindex];
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


/**
 * Draws entities based on zindex and y position
 * @param systemManager
 */
void pk::Camera::draw(pk::SystemManager* systemManager) {
    this->beginDrawing();
        for (auto&[zindex, vec] : this->zindexToEntities) {
            for (auto&[yPos, entity] : vec) {
                const pk::transform_t& transform = pk::EcsController::getTransform(entity);
                yPos = transform.pos.y + transform.size.y / 2.0f;
            }
            std::sort(vec.begin(), vec.end());
            systemManager->draw(vec);
        }
    this->endDrawing();
}


void pk::Camera::addZoom(const float zoom) {
    this->camera2D.zoom = std::clamp(
        this->camera2D.zoom + zoom,
        pk::CAMERA_MIN_ZOOM,
        pk::CAMERA_MAX_ZOOM
    );
}


void pk::Camera::handleMouseInput(const float dt) {
    this->addZoom(GetMouseWheelMove() * dt);
}


void pk::Camera::setZoom(const float zoom) {
    this->camera2D.zoom = std::clamp(
        zoom,
        pk::CAMERA_MIN_ZOOM,
        pk::CAMERA_MAX_ZOOM
    );
}


void pk::Camera::clear() {
    for (auto& pair : this->zindexToEntities) {
        pair.second.clear();
    }
    for (bool& b : this->onCamera) {
        b = false;
    }
}


std::size_t pk::Camera::size() const {
    return this->mSize;
}


const Camera2D &pk::Camera::getCamera2D() const {
    return this->camera2D;
}
