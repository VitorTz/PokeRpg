#include "Camera.hpp"
#include "../ecs/EcsController.hpp"


pk::Camera::Camera() {
    for (pk::zindex_t z = pk::CAMERA_MIN_ZINDEX; z <= pk::CAMERA_MAX_ZINDEX; z++) {
        this->entities[z].reserve(pk::MAX_ENTITIES);
    }
    this->reset();
}


void pk::Camera::reset() {
    this->camera = Camera2D{
        .offset = pk::SCREEN_CENTER,
        .target = pk::SCREEN_CENTER,
        .rotation = 0.0f,
        .zoom = 1.0f
    };
    this->cameraRect = Rectangle{
        this->camera.target.x - this->camera.offset.x,
        this->camera.target.y - this->camera.offset.y,
        pk::SCREEN_W,
        pk::SCREEN_H
    };
}

void pk::Camera::move(const float x, const float y) {
    this->camera.target.x += x;
    this->camera.target.y += y;
    this->cameraRect.x += x;
    this->cameraRect.y += y;
}


void pk::Camera::setTarget(const float x, const float y) {
    this->camera.target.x = x;
    this->camera.target.y = y;
    this->cameraRect.x = x - this->camera.offset.x;
    this->cameraRect.y = y - this->camera.offset.y;
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
    BeginMode2D(this->camera);
}


void pk::Camera::endDrawing() const {
    EndMode2D();
}


void pk::Camera::draw(pk::SystemManager* system) {
    this->beginDrawing();
        for (auto& p1 : this->entities) {
            for (std::pair<float, pk::entity_t>& p2 : p1.second) {
                const pk::transform_t& transform = pk::EcsController::getTransform(p2.second);
                p2.first = transform.pos.y + transform.size.y / 2.0f;
            }
            std::sort(p1.second.begin(), p1.second.end());
            system->draw(p1.second);
        }
    this->endDrawing();
}


void pk::Camera::addZoom(const float zoom) {
    this->camera.zoom = std::clamp(
        this->camera.zoom + zoom,
        pk::CAMERA_MIN_ZOOM,
        pk::CAMERA_MAX_ZOOM
    );
}


void pk::Camera::handleMouseInput(const float dt) {
    this->addZoom(GetMouseWheelMove() * dt);
}


void pk::Camera::setZoom(const float zoom) {
    this->camera.zoom = std::clamp(
        zoom,
        pk::CAMERA_MIN_ZOOM,
        pk::CAMERA_MAX_ZOOM
    );
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


const Camera2D &pk::Camera::getCamera2D() const {
    return this->camera;
}
