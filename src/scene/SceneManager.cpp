//
// Created by vitor on 10/3/24.
//
#include "Scene.h"


void pk::SceneManager::init() {
    this->loadNextScene();
    this->loadingScreen = std::make_unique<pk::LoadingScreen>();
}


void pk::SceneManager::loadNextScene() {
    switch (this->nextScene) {
        case pk::LevelSceneId:
            this->scene = std::make_unique<pk::LevelScene>();
            break;
        case pk::TitleScreenId:
            this->scene = std::make_unique<pk::TitleScreen>();
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
    this->nextScene = sceneId;
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

