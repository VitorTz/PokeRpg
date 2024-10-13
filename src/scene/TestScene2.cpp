#include "Scene.hpp"
#include "../ecs/EcsController.hpp"


pk::TestScene2::TestScene2() {
    pk::EcsController::unloadAllMaps();
    pk::EcsController::setCurrentMapId(pk::WorldMapId);
}


void pk::TestScene2::update(const float dt) {
    pk::EcsController::setCurrentMapId(pk::WorldMapId);
    pk::EcsController::update(dt);
}


void pk::TestScene2::draw() {
    pk::EcsController::setCurrentMapId(pk::WorldMapId);
    pk::EcsController::draw();
}
