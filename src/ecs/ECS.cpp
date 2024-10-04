//
// Created by vitor on 10/3/24.
//
#include "ECS.h"


std::unordered_map<pk::TiledMapId, std::unique_ptr<pk::ECS>> pk::ECS::ecsInstanceByMapId{};


void pk::ECS::createEcsInstance(const pk::TiledMapId mapId) {
    assert(pk::ECS::ecsInstanceByMapId.find(mapId) == pk::ECS::ecsInstanceByMapId.end());
    pk::ECS::ecsInstanceByMapId.emplace(mapId, std::unique_ptr<pk::ECS>(new pk::ECS(mapId)));
    pk::ECS* ecs = pk::ECS::ecsInstanceByMapId[mapId].get();

    const pk::tiled_map_t& tiledMapInfo = pk::TILED_MAPS[mapId];
    std::string str = TILED_MAP_PATH;

    // Load Terrain
    str += tiledMapInfo.name;
    str += ".png";
    ecs->createSprite(pk::CAMERA_ZINDEX_TERRAIN, str.c_str());

    // Load Map objects
    // str = TILED_MAP_PATH;
    // str += tiledMapInfo.name;
    // str += ".txt";
    // std::fstream file(str);
    // assert(file.is_open());
    //
    // while (std::getline(file, str)) {
    //     int n;
    //     file >> n;
    // }
    //
    //
    // file.close();
}


void pk::ECS::destroyEcsInstance(const pk::TiledMapId mapId) {
    pk::ECS::ecsInstanceByMapId.erase(mapId);
}


pk::ECS* pk::ECS::getEcsInstance(const pk::TiledMapId mapId) {
    assert(pk::ECS::ecsInstanceByMapId.find(mapId) != pk::ECS::ecsInstanceByMapId.end());
    return pk::ECS::ecsInstanceByMapId[mapId].get();
}


void pk::ECS::destroyAllInstances() {
    pk::ECS::ecsInstanceByMapId.clear();
}


pk::entity_t pk::ECS::createEntity(const pk::zindex_t zindex, const bool submitToCamera) {
    const pk::entity_t e = this->entity->entityCreate();
    this->component->insert<pk::transform_t>(e, pk::transform_t{.zindex = zindex});
    if (submitToCamera) this->camera->insert(e, zindex);
    return e;
}


pk::entity_t pk::ECS::createSprite(const pk::zindex_t zindex, const char *fileName) {
    const pk::entity_t e = this->createEntity(zindex, true);
    this->addComponent<pk::sprite_t>(e, pk::sprite_t{fileName});
    const pk::sprite_t& sprite = this->getComponent<pk::sprite_t>(e);
    this->getTransform(e).size = Vector2{
        static_cast<float>(sprite.texture.width),
        static_cast<float>(sprite.texture.height)
    };
    return e;
}


void pk::ECS::destroyEntity(const pk::entity_t e) {
    this->entitiesToDestroy.push(e);
}


void pk::ECS::update(const float dt) {
    this->system->update(dt);

    if (this->shouldDestroyAllEntities) {
        this->entitiesToDestroy = std::queue<pk::entity_t>();
        this->camera->clear();
        this->entity->clear();
        this->component->clear();
        this->system->clear();
        this->staticCollisions.clear();
    }

    while (this->entitiesToDestroy.empty() == false) {
        const pk::entity_t e = this->entitiesToDestroy.front();
        this->entitiesToDestroy.pop();
        this->camera->erase(e, this->component->at<pk::transform_t>(e).zindex);
        this->entity->entityDestroy(e);
        this->component->entityDestroy(e);
        this->system->entityDestroy(e);
        this->staticCollisions.erase({e, Rectangle{}});
    }
}


void pk::ECS::draw() {
    this->camera->draw(this->system.get());
}


void pk::ECS::clear() {
    this->shouldDestroyAllEntities = true;
}


pk::transform_t& pk::ECS::getTransform(const pk::entity_t e) {
    return this->component->at<pk::transform_t>(e);
}


const pk::Camera* pk::ECS::getCamera() const {
    return this->camera.get();
}


pk::player_info_t *pk::ECS::getPlayerInfo(const pk::TiledMapId mapId) {
    assert(pk::ECS::ecsInstanceByMapId.find(mapId) != pk::ECS::ecsInstanceByMapId.end());
    return &pk::ECS::ecsInstanceByMapId[mapId]->playerInfo;
}


const pk::tiled_map_t& pk::ECS::getMapInfo(const pk::TiledMapId mapId) {
    return pk::TILED_MAPS[mapId];
}
