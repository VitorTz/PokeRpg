//
// Created by vitor on 10/19/24.
//
#include "Scene.h"


void pk::SceneManager::init() {
    this->loadNextScene();
    this->loadingScreen = std::make_unique<pk::LoadingScreen>();
}


void pk::SceneManager::loadNextScene() {
    switch (this->sceneId) {
        case pk::TitleScreenId:
            this->scene = std::make_unique<pk::TitleScreen>();
            break;
        case pk::WorldSceneId:
            this->scene = std::make_unique<pk::WorldScene>();
            break;
        case pk::FireArenaSceneId:
            this->scene = std::make_unique<pk::FireArenaScene>();
            break;
        case pk::PlantArenaSceneId:
            this->scene = std::make_unique<pk::PlantArenaScene>();
            break;
        case pk::WaterArenaSceneId:
            this->scene = std::make_unique<pk::WaterArenaScene>();
            break;
        case pk::HospitalSceneId:
            this->scene = std::make_unique<pk::HospitalScene>();
            break;
        case pk::HouseSceneId:
            this->scene = std::make_unique<pk::HouseScene>();
            break;
        case pk::TestScene1Id:
            this->scene = std::make_unique<pk::TestScene1>();
            break;
        default:
            break;
    }
}


void pk::SceneManager::changeScene(const pk::SceneId sceneId) {
    this->shouldChangeScene = true;
    this->sceneId = sceneId;
}


void pk::SceneManager::update(const float dt) {
    this->scene->update(dt);
    if (this->shouldChangeScene == true) {
        this->shouldChangeScene = false;
        this->loadNextScene();
    }
}


void pk::SceneManager::draw() {
    this->scene->draw();
}





