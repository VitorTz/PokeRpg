//
// Created by vitor on 10/19/24.
//

#ifndef ECSMANAGER_H
#define ECSMANAGER_H

#include <memory>
#include "components.h"
#include "EntityManager.h"
#include "ComponentManager.h"
#include "SystemManager.h"
#include "../util/MapId.h"
#include "../util/Camera.h"
#include "../util/TypeId.h"
#include "../util/player.h"


namespace pk {

    class EcsManager {

    private:
        typedef struct ecs_instance {
            pk::EntityManager entity{};
            pk::ComponentManager component{};
            pk::SystemManager system{};
            pk::player_t player{};
            pk::Camera camera;
            std::vector<Rectangle> staticCollisions{};
            std::queue<pk::entity_t> entitiesToDestroy{};
            bool shouldDestroyAllEntities{};
            explicit ecs_instance(const pk::MapId mapId) : camera(mapId) { }
        } ecs_instance_t;

    private:
        static std::unordered_map<pk::MapId, std::unique_ptr<pk::EcsManager::ecs_instance_t>> ecsInstanceMap;
        static pk::EcsManager::ecs_instance_t* currentMapInstance;
        static pk::MapId currentMapId;

    public:
        static void init();
        static void close();

        static void ecsInstanceCreate(pk::MapId mapId);
        static void ecsInstanceDestroy(pk::MapId mapId);
        static pk::MapId getCurrentMapId();
        static void setCurrentEcsInstance(pk::MapId mapId);

        static pk::player_t& getPlayer();
        static pk::player_t& getPlayer(pk::MapId mapId);

        static void update(float dt);
        static void draw();
        static void drawDebug();

        static pk::entity_t entityCreate(pk::zindex_t zindex, bool addToCamera);
        static pk::entity_t spriteCreate(pk::zindex_t zindex, const char* fileName);
        static pk::entity_t spriteCreate(pk::zindex_t zindex, float posX, float posY, const char* fileName);

        static void entityDestroy(pk::entity_t e);
        static void entityDestroyImmediate(pk::entity_t e);
        static void entityDestroyAll();
        static void entityDestroyAllImmediate();

        static void addStaticCollision(Rectangle rect);
        static void addStaticCollision(pk::entity_t e, float width, float height);
        static pk::transform_t& getTransform(pk::entity_t e);

        static bool checkStaticCollision(const Rectangle& rect);
        static std::pair<bool, pk::entity_t> checkEntityCollision(pk::entity_t e);
        static std::pair<bool, pk::TransitionType> checkTransition(const Rectangle& rect);

        template<typename T>
        static T& getComponent(const pk::entity_t e) {
            return currentMapInstance->component.at<T>(e);
        }

        template<typename T>
        static void eraseComponent(const pk::entity_t e) {
            currentMapInstance->component.erase<T>(e);
            currentMapInstance->system.erase<T>(e);
        }

        template<typename T>
        static void addComponent(const pk::entity_t e, const T c) {
            currentMapInstance->component.insert<T>(e, std::move(c));
            currentMapInstance->system.insert<T>(e);
        }

    };

}

#endif //ECSMANAGER_H
