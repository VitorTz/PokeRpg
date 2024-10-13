#pragma once
#include "EntityManager.hpp"
#include "ComponentManager.hpp"
#include "SystemManager.hpp"
#include "../util/Camera.hpp"


namespace pk {


    class EcsController {

        private:

            typedef struct ecs {
                pk::EntityManager entity{};
                pk::ComponentManager component{};
                pk::SystemManager system{};
                pk::Camera camera{};
                std::queue<pk::entity_t> entitiesToDestroy{};
                std::vector<Rectangle> staticCollisions{};
                bool shouldDestroyAllEntities{};
            } ecs_t;            
        
        private:
            static std::unordered_map<pk::MapId, std::unique_ptr<pk::EcsController::ecs_t>> ecsInstanceMap;
            static pk::EcsController::ecs_t* ecs;
            static pk::MapId currentMapId;

        private:
            static void loadMap(pk::MapId mapId) {
                if (ecsInstanceMap.find(mapId) == ecsInstanceMap.end()) {
                    ecsInstanceMap.emplace(mapId, std::make_unique<pk::EcsController::ecs_t>());
                }
                ecs = ecsInstanceMap[mapId].get();
            }
        
        public:
            
            static void setCurrentMapId(const pk::MapId mapId) {
                currentMapId = mapId;
                loadMap(mapId);
            }

            static pk::MapId getCurrentMapId() {
                return currentMapId;
            }

            static void unloadMap(const pk::MapId mapId) {
                ecsInstanceMap.erase(mapId);
            }

            static void unloadAllMaps() {
                ecsInstanceMap.clear();
                ecs = nullptr;
            }

            static pk::entity_t entityCreate(const pk::zindex_t zindex, const bool submitToCamera) {
                const pk::entity_t e = ecs->entity.entityCreate();
                addComponent<pk::transform_t, pk::id::transform>(e, pk::transform_t{zindex});                
                if (submitToCamera) ecs->camera.insert(e, zindex);
                return e;
            }

            static pk::entity_t createSprite(const pk::zindex_t zindex, const char* fileName) {
                const pk::entity_t e = entityCreate(zindex, true);
                addComponent<pk::sprite_t, pk::id::sprite>(e, pk::sprite_t{fileName});
                const auto& sprite = getComponent<pk::sprite_t, pk::id::sprite>(e);
                getTransform(e).size = Vector2{
                    static_cast<float>(sprite.texture.width),
                    static_cast<float>(sprite.texture.height)
                };
                return e;
            }

            static pk::entity_t createSpriteAnimation(const pk::zindex_t zindex, const pk::sprite_animation_source_t& source) {
                const pk::entity_t e = entityCreate(zindex, true);
                addComponent<pk::sprite_animation_t, pk::id::sprite_animation>(e, pk::sprite_animation_t{source});
                const auto& sprite_animation = getComponent<pk::sprite_animation_t, pk::id::sprite_animation>(e);
                getTransform(e).size = Vector2{
                    sprite_animation.textureRect.width,
                    sprite_animation.textureRect.height
                };
                return e;
            }

            template<typename T, pk::component_t id>
            static void addComponent(const pk::entity_t e, const T c) {
                ecs->component.insert<T, id>(e, std::move(c));
                ecs->system.insert<id>(e);
            }

            template<typename T, pk::component_t id>
            static void rmvComponent(const pk::entity_t e, const T c) {
                ecs->component.erase<T, id>(e, std::move(c));
                ecs->system.erase<id>(e);
            }

            template<typename T, pk::component_t id>
            static T& getComponent(const pk::entity_t e) {
                return ecs->component.at<T, id>(e);
            }

            static void addCollision(const Rectangle rect) {
                ecs->staticCollisions.emplace_back(rect);
            }

            static void clearCollisions() {
                ecs->staticCollisions.clear();
            }

            static bool checkStaticCollision(const Rectangle& rect) {
                return std::any_of(
                    ecs->staticCollisions.begin(),
                    ecs->staticCollisions.end(),
                    [rect](const Rectangle& otherRect) {
                        return CheckCollisionRecs(rect, otherRect);
                    }
                );
            }

            static pk::transform_t& getTransform(const pk::entity_t e) {
                return getComponent<pk::transform_t, pk::id::transform>(e);
            }

            static void update(const float dt) {
                ecs->system.update(dt);
                ecs->camera.handleMouseInput(dt);
                if (ecs->shouldDestroyAllEntities == true) {
                    ecs->entity.clear();
                    ecs->component.clear();
                    ecs->system.clear();
                    ecs->camera.clear();
                    ecs->entitiesToDestroy = std::queue<pk::entity_t>();
                    ecs->shouldDestroyAllEntities = false;
                }

                while (ecs->entitiesToDestroy.empty() == false) {
                    const pk::entity_t e = ecs->entitiesToDestroy.front();
                    ecs->entitiesToDestroy.pop();
                    ecs->camera.erase(e, ecs->component.at<pk::transform_t, pk::id::transform>(e).zindex);
                    ecs->entity.entityDestroy(e);
                    ecs->component.entityDestroy(e);
                    ecs->system.entityDestroy(e);
                }
            }

            static void draw() {
                ecs->camera.draw(&ecs->system);
                if (pk::DEBUG_MODE) {
                    const Camera2D camera2D = ecs->camera.getCamera2D();
                    const Color color = LIME;
                    DrawRectangle(18, 18, 200, 200, Color{0, 0, 0, 120});
                    DrawFPS(20, 20);
                    DrawText(TextFormat("MAP ID: %d", currentMapId), 20, 40, 16, color);
                    DrawText(TextFormat("ENTITIES: %ld", ecs->entity.size()), 20, 60, 16, color);
                    DrawText(TextFormat("COMPONENTS: %ld", ecs->component.size()), 20, 80, 16, color);
                    DrawText(TextFormat("CAM SIZE: %ld", ecs->camera.size()), 20, 100, 16, color);
                    DrawText(
                        TextFormat("CAM TARGET: %.0f, %.0f", camera2D.target.x, camera2D.target.y),
                        20,
                        120,
                        16,
                        color
                    );
                    DrawText(
                        TextFormat("CAM ZOOM: %.2f", camera2D.zoom),
                        20,
                        140,
                        16,
                        color
                    );
                }
            }

            static void entityDestroy(const pk::entity_t e) {
                ecs->entitiesToDestroy.push(e);
            }

            static void clear() {
                ecs->shouldDestroyAllEntities = true;
            }

            static void reset() {
                ecs->entity.clear();
                ecs->component.clear();
                ecs->system.clear();
                ecs->camera.reset();
                ecs->staticCollisions.clear();
                ecs->entitiesToDestroy = std::queue<pk::entity_t>();
                ecs->shouldDestroyAllEntities = false;
            }

            template<pk::component_t id>
            static const std::unordered_set<pk::entity_t>& getEntitiesFromSystem() {
                return ecs->system.getEntitiesFromSystem<id>();
            }

            static const pk::EntityManager* getEntityManager() {
                return &ecs->entity;
            }

            static const pk::ComponentManager* getComponentManager() {
                return &ecs->component;
            }

            static const pk::SystemManager* getSystemManager() {
                return &ecs->system;
            }

    };

}
