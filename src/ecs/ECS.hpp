#pragma once
#include <memory>
#include <queue>
#include <unordered_map>
#include <unordered_set>
#include <vector>
#include "Component.hpp"
#include "components.hpp"
#include "Entity.hpp"
#include "player.hpp"
#include "raylib.h"
#include "System.hpp"
#include "../util/Camera.hpp"
#include "../util/SceneId.hpp"
#include "../util/Transition.hpp"


namespace pk {


    class ECS {

    private:
        typedef struct ecs_instance {
            EntityManager entity{};
            ComponentManager component{};
            SystemManager system{};
            pk::Camera camera;
            std::vector<Rectangle> staticCollisions{};
            pk::Transition transition{};            
            std::queue<pk::entity_t> entitiesToDestroy{};
            bool shouldDestroyAllEntities{};
            pk::player_t player{};
            explicit ecs_instance(const pk::SceneId sceneId) : camera(sceneId) { }
        } ecs_instance_t;
        
    public:
        static std::unordered_map<pk::SceneId, std::unique_ptr<pk::ECS::ecs_instance_t>> ecsInstanceMap;
        static pk::ECS::ecs_instance_t* currentEcsInstance;
        static pk::SceneId currentSceneId;

    public:
        static void setCurrentScene(pk::SceneId sceneId);
        static void ecsInstanceCreate(pk::SceneId sceneId);
        static void ecsInstanceDestroy(pk::SceneId sceneId);
        static void ecsInstanceDestroyAll();

        static pk::entity_t entityCreate(pk::zindex_t zindex, bool addToCamera);
        static pk::entity_t entityCreate(pk::zindex_t zindex, float x, float y, bool addToCamera);
        static pk::entity_t spriteCreate(pk::zindex_t zindex, const char* imagePath);
        static pk::entity_t spriteCreate(pk::zindex_t zindex, float x, float y, const char* imagePath);

        static void entityDestroy(pk::entity_t e);
        static void entityDestroyImmediate(pk::entity_t e);
        static void entityDestroyAll();
        static void entityDestroyAllImmediate();        

        static void ecsInstanceUpdate(float dt);
        static void ecsInstanceDraw();

        static void staticCollisionAdd(const Rectangle& rect);
        static void staticCollisionAdd(float x, float y, float width, float height);
        static void staticCollisionAdd(pk::entity_t e, float width, float height);
        static void staticCollisionClear();
        static bool checkCollision(const Rectangle& rect);

        static void transitionAdd(pk::SceneId sceneId, const Rectangle& rect);
        static void checkTransition(const Rectangle& rect);

        static pk::player_t& getPlayer();

        static pk::Camera* getCamera(pk::SceneId sceneId);
        static pk::Camera* getCamera();

        static pk::transform_t& getTransform(pk::entity_t e);

        template<typename T>
        static const std::unordered_set<pk::entity_t>& getEntitiesFromSystem() {
            return currentEcsInstance->system.getEntitiesFromSystem<T>();
        }

        template<typename T>
        static void componentAdd(const pk::entity_t e, const T c) {
            currentEcsInstance->component.insert(e, c);
            currentEcsInstance->system.insert<T>(e);
        }

        template<typename T>
        static void componentErase(const pk::entity_t e) {
            currentEcsInstance->component.erase<T>(e);
            currentEcsInstance->system.erase<T>(e);
        }

        template<typename T>
        static T& componentGet(const pk::entity_t e) {
            return currentEcsInstance->component.at<T>(e);
        }


    };
   

}
