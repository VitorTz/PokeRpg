#include "Scene.hpp"
#include "../ecs/EcsController.hpp"


pk::TestScene2::TestScene2() {
    pk::EcsController::unloadAllEcsInstances();
    pk::EcsController::setCurrentEcsInstance(pk::WorldMapId);
}


void pk::TestScene2::update(const float dt) {
    pk::EcsController::setCurrentEcsInstance(pk::WorldMapId);
    pk::EcsController::update(dt);
}


void pk::TestScene2::draw() {
    pk::EcsController::setCurrentEcsInstance(pk::WorldMapId);
    pk::EcsController::draw();
}
