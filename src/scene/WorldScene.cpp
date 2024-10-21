//
// Created by vitor on 10/19/24.
//
#include "Scene.h"
#include "../ecs/EcsManager.h"


pk::WorldScene::WorldScene() {
    pk::EcsManager::ecsInstanceCreate(pk::WorldMapId);
}


void pk::WorldScene::update(const float dt) {
    pk::EcsManager::setCurrentEcsInstance(pk::WorldMapId);
    pk::EcsManager::update(dt);
}


void pk::WorldScene::draw() {
    pk::EcsManager::setCurrentEcsInstance(pk::WorldMapId);
    pk::EcsManager::draw();
}

