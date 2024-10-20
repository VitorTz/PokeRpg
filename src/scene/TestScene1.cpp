//
// Created by vitor on 10/20/24.
//
#include "Scene.h"
#include "../ecs/EcsManager.h"


pk::TestScene1::TestScene1() {
    pk::EcsManager::ecsInstanceCreate(pk::WorldMapId);
}


void pk::TestScene1::update(const float dt) {
    pk::EcsManager::setCurrentEcsInstance(pk::WorldMapId);
    pk::EcsManager::update(dt);
}


void pk::TestScene1::draw() {
    pk::EcsManager::setCurrentEcsInstance(pk::WorldMapId);
    pk::EcsManager::draw();
}


