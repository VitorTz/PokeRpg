#include "Scene.hpp"
#include "../ecs/EcsController.hpp"
#include "../util/mrandom.h"


std::unordered_map<pk::entity_t, float> speed{};

pk::TestScene1::TestScene1() {
    pk::EcsController::unloadAllMaps();
    pk::EcsController::setCurrentMapId(pk::WorldMapId);
    std::uniform_real_distribution<float> randX(0.0f, pk::SCREEN_W);
    std::uniform_real_distribution<float> randY(-pk::SCREEN_H, 0.0f);
    std::uniform_real_distribution<float> randSpeed(50.0f, 200.0f);
    for (pk::entity_t i = 0; i < pk::MAX_ENTITIES; i++) {
        const pk::entity_t e = pk::EcsController::createSprite(0, ASSETS_PATH "graphics/objects/arean_fire.png");
        pk::transform_t& transform = pk::EcsController::getTransform(e);
        transform.pos = Vector2{
            randX(pk::random::gen),
            randY(pk::random::gen)
        };
        speed[e] = randSpeed(pk::random::gen);
    }
}


void pk::TestScene1::update(const float dt) {
    pk::EcsController::setCurrentMapId(pk::WorldMapId);
    const std::unordered_set<pk::entity_t>& ent = pk::EcsController::getEntitiesFromSystem<pk::id::sprite>();
    if (ent.empty() == true) {
        pk::gSceneManager.changeScene(pk::TestScene2Id);
    }
    for (const pk::entity_t e : ent) {
        pk::transform_t& transform = pk::EcsController::getTransform(e);
        transform.pos.y += speed[e] * dt;
        if (transform.pos.y > pk::SCREEN_H) {
            pk::EcsController::entityDestroy(e);
        }
    }
    pk::EcsController::update(dt);
}


void pk::TestScene1::draw() {
    pk::EcsController::setCurrentMapId(pk::WorldMapId);
    pk::EcsController::draw();
}
