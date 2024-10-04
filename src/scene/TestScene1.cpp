//
// Created by vitor on 10/3/24.
//
#include "Scene.h"


pk::TestScene1::TestScene1() {
    pk::ECS::createEcsInstance(pk::WorldMapId);
}


void pk::TestScene1::update(const float dt) {
    pk::ECS* const ecs = pk::ECS::getEcsInstance(pk::WorldMapId);
    ecs->update(dt);
}


void pk::TestScene1::draw() {
    pk::ECS* const ecs = pk::ECS::getEcsInstance(pk::WorldMapId);
    ecs->draw();
}

