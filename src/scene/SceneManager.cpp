#include "Scene.hpp"
#include <memory>


void pk::SceneManager::init() {
    this->loadNextScene();    
}


void pk::SceneManager::loadNextScene() {
    switch (this->sceneId) {
        case pk::WorldSceneId:
            this->scene = std::make_unique<pk::WorldScene>();
            break;
        case pk::TitleScreenId:
            this->scene = std::make_unique<pk::TitleScreen>();
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