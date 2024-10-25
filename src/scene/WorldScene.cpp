#include "Scene.hpp"
#include "../ecs/ECS.hpp"


pk::WorldScene::WorldScene() {
    pk::ECS::ecsInstanceCreate(pk::WorldSceneId);    
}


void pk::WorldScene::update(const float dt) {
    pk::ECS::setCurrentScene(pk::WorldSceneId);
    pk::ECS::ecsInstanceUpdate(dt);
}


void pk::WorldScene::draw() {
    pk::ECS::setCurrentScene(pk::WorldSceneId);
    pk::ECS::ecsInstanceDraw();
}