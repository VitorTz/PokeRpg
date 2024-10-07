//
// Created by vitor on 10/3/24.
//

#ifndef ECS_H
#define ECS_H
#include "Entity.h"
#include "Component.h"
#include "System.h"
#include "../util/Camera.h"


namespace pk {

    class ECS {

    private:
        static std::unordered_map<pk::TiledMapId, std::unique_ptr<pk::ECS>> ecsInstanceByMapId;

    public:
        static void createEcsInstance(pk::TiledMapId mapId);
        static void destroyEcsInstance(pk::TiledMapId mapId);
        static pk::ECS* getEcsInstance(pk::TiledMapId mapId);
        static void destroyAllInstances();
        static const pk::tiled_map_t& getMapInfo(pk::TiledMapId mapId);
        static pk::player_info_t* getPlayerInfo(pk::TiledMapId mapId);

    public:
        pk::entity_t createEntity(pk::zindex_t zindex, bool submitToCamera);
        pk::entity_t createSprite(pk::zindex_t zindex, const char* fileName);

        bool checkCollision(const Rectangle& rect);

        void destroyEntity(pk::entity_t e);
        void clear();

        void update(float dt);
        void draw();

        template<typename T>
        void addComponent(const pk::entity_t e, T c) {
            this->component->insert<T>(e, std::move(c));
            this->system->insert<T>(e);
        }

        template<typename T>
        void rmvComponent(const pk::entity_t e) {
            this->component->erase<T>(e);
            this->system->erase<T>(e);
        }

        template<typename T>
        T& getComponent(const pk::entity_t e) {
            return this->component->at<T>(e);
        }

        pk::transform_t& getTransform(pk::entity_t e);
        const pk::Camera* getCamera() const;

    private:
        const pk::TiledMapId mapId;
        std::unique_ptr<pk::EntityManager> entity{};
        std::unique_ptr<pk::ComponentManager> component{};
        std::unique_ptr<pk::SystemManager> system{};
        std::queue<pk::entity_t> entitiesToDestroy{};
        std::unique_ptr<pk::Camera> camera{};
        std::vector<Rectangle> staticCollisions{};
        pk::player_info_t playerInfo{};
        bool shouldDestroyAllEntities{};

        explicit ECS(
            const pk::TiledMapId mapId
        ) : mapId(mapId),
            entity(std::make_unique<pk::EntityManager>()),
            component(std::make_unique<pk::ComponentManager>()),
            system(std::make_unique<pk::SystemManager>(mapId)),
            camera(std::make_unique<pk::Camera>(mapId)) {
            this->staticCollisions.reserve(1024);
        }

    };

}


#endif //ECS_H
