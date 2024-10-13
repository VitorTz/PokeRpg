#include "Scene.hpp"


void pk::SceneManager::init() {
    this->loadNextScene();
    this->loadingScreen = std::make_unique<pk::LoadingScreen>();
}


void pk::SceneManager::loadNextScene() {
    switch (this->sceneId) {
        case pk::SceneId::TestScene1Id:
            this->scene = std::make_unique<pk::TestScene1>();
            break;
        case pk::SceneId::TestScene2Id:
            this->scene = std::make_unique<pk::TestScene2>();
            break;
        case pk::SceneId::LevelSceneId:
            this->scene = std::make_unique<pk::LevelScene>();
            break;
        case pk::SceneId::TitleScreenId:
            this->scene = std::make_unique<pk::TitleScreen>();
            break;
        case pk::SceneId::LoadingScreenId:
            this->scene = std::make_unique<pk::LoadingScreen>();
            break;
        default:
            break;
    }
}


void pk::SceneManager::changeScene(const pk::SceneId sceneId) {
    this->sceneId = sceneId;
    this->shouldChangeScene = true;
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
