#pragma once
#include "EntityManager.hpp"
#include "ComponentManager.hpp"
#include "SystemManager.hpp"
#include "../util/Camera.hpp"


namespace pk {


    class EcsController {

        private:

            // (Each map will have its own instance)
            typedef struct ecs {
                pk::EntityManager entity{};
                pk::ComponentManager component{};
                pk::SystemManager system{};
                pk::Camera camera{};
                std::queue<pk::entity_t> entitiesToDestroy{};
                std::vector<Rectangle> staticCollisions{};
                bool shouldDestroyAllEntities{};
            } ecs_instance_t;
        
        private:
            static std::unordered_map<pk::MapId, std::unique_ptr<pk::EcsController::ecs_instance_t>> ecsInstanceMap;
            static pk::EcsController::ecs_instance_t* currentEcsInstance;

        private:
            /**
             * Cria uma instância para o mapa informado.
             * @param mapId
             */
            static void loadMap(const pk::MapId mapId) {
                if (ecsInstanceMap.find(mapId) == ecsInstanceMap.end()) {
                    ecsInstanceMap.emplace(mapId, std::make_unique<pk::EcsController::ecs_instance_t>());
                }
            }

            static void debugModeUpdate(const float dt) {
                if (pk::DEBUG_MODE) {

                }
            }

            static void drawDebugText(const char* text, const int textNum) {
                DrawText(text, 20, 20 + 20 * textNum, 16, LIME);
            }

            static void debugModeDraw() {
                if (pk::DEBUG_MODE) {
                    const Camera2D camera2D = currentEcsInstance->camera.getCamera2D();
                    DrawRectangle(18, 18, 200, 200, Color{0, 0, 0, 140});
                    DrawFPS(20, 20);
                    drawDebugText(TextFormat("ENTITIES: %ld", currentEcsInstance->entity.size()), 1);
                    drawDebugText(TextFormat("COMPONENTS: %ld", currentEcsInstance->component.countNumComponents()), 2);
                    drawDebugText(TextFormat("CAM SIZE: %ld", currentEcsInstance->camera.size()), 3);
                    drawDebugText(TextFormat("CAM TARGET: %.0f, %.0f", camera2D.target.x, camera2D.target.y), 4);
                    drawDebugText(TextFormat("CAM ZOOM: %.2f", camera2D.zoom), 5);
                }
            }

        public:

            static void setCurrentEcsInstance(const pk::MapId mapId) {
                loadMap(mapId); // Load the map instance if its no loaded
                currentEcsInstance = ecsInstanceMap[mapId].get();
            }

            static void unloadEcsInstance(const pk::MapId mapId) {
                ecsInstanceMap.erase(mapId);
            }

            static void unloadAllEcsInstances() {
                ecsInstanceMap.clear();
                currentEcsInstance = nullptr;
            }

        public:

            static pk::entity_t entityCreate(const pk::zindex_t zindex, const bool submitToCamera) {
                const pk::entity_t e = currentEcsInstance->entity.entityCreate();
                addComponent<pk::transform_t, pk::id::transform>(e, pk::transform_t{zindex});
                if (submitToCamera) currentEcsInstance->camera.insert(e, zindex);
                return e;
            }

            static pk::entity_t spriteCreate(const pk::zindex_t zindex, const char* fileName) {
                const pk::entity_t e = entityCreate(zindex, true);
                addComponent<pk::sprite_t, pk::id::sprite>(e, pk::sprite_t{fileName});
                const auto& sprite = getComponent<pk::sprite_t, pk::id::sprite>(e);
                getTransform(e).size = Vector2{
                    static_cast<float>(sprite.texture.width),
                    static_cast<float>(sprite.texture.height)
                };
                return e;
            }

            static pk::entity_t spriteAnimationCreate(const pk::zindex_t zindex, const pk::sprite_animation_source_t& source) {
                const pk::entity_t e = entityCreate(zindex, true);
                addComponent<pk::sprite_animation_t, pk::id::sprite_animation>(e, pk::sprite_animation_t{source});
                const auto& sprite_animation = getComponent<pk::sprite_animation_t, pk::id::sprite_animation>(e);
                getTransform(e).size = Vector2{
                    sprite_animation.textureRect.width,
                    sprite_animation.textureRect.height
                };
                return e;
            }

            template<typename T, pk::component_id_t id>
            static void addComponent(const pk::entity_t e, const T c) {
                currentEcsInstance->component.insert<T, id>(e, std::move(c));
                currentEcsInstance->system.insert<id>(e);
            }

            template<typename T, pk::component_id_t id>
            static void rmvComponent(const pk::entity_t e, const T c) {
                currentEcsInstance->component.erase<T, id>(e, std::move(c));
                currentEcsInstance->system.erase<id>(e);
            }

            template<typename T, pk::component_id_t id>
            static T& getComponent(const pk::entity_t e) {
                return currentEcsInstance->component.at<T, id>(e);
            }

            static void addStaticCollision(const Rectangle rect) {
                currentEcsInstance->staticCollisions.emplace_back(rect);
            }

            static void clearStaticCollision() {
                currentEcsInstance->staticCollisions.clear();
            }

            static bool checkStaticCollision(const Rectangle& rect) {
                return std::any_of(
                    currentEcsInstance->staticCollisions.begin(),
                    currentEcsInstance->staticCollisions.end(),
                    [rect](const Rectangle& otherRect) {
                        return CheckCollisionRecs(rect, otherRect);
                    }
                );
            }

            static pk::transform_t& getTransform(const pk::entity_t e) {
                return getComponent<pk::transform_t, pk::id::transform>(e);
            }

            static void update(const float dt) {
                currentEcsInstance->camera.handleMouseInput(dt);
                currentEcsInstance->system.update(dt);

                if (currentEcsInstance->shouldDestroyAllEntities == true) {
                    currentEcsInstance->entity.clear();
                    currentEcsInstance->component.clear();
                    currentEcsInstance->system.clear();
                    currentEcsInstance->camera.clear();
                    currentEcsInstance->entitiesToDestroy = std::queue<pk::entity_t>();
                    currentEcsInstance->shouldDestroyAllEntities = false;
                }

                while (currentEcsInstance->entitiesToDestroy.empty() == false) {
                    const pk::entity_t e = currentEcsInstance->entitiesToDestroy.front();
                    currentEcsInstance->entitiesToDestroy.pop();
                    currentEcsInstance->camera.erase(e, currentEcsInstance->component.at<pk::transform_t, pk::id::transform>(e).zindex);
                    currentEcsInstance->entity.entityDestroy(e);
                    currentEcsInstance->component.entityDestroy(e);
                    currentEcsInstance->system.entityDestroy(e);
                }
                debugModeUpdate(dt);
            }

            static void draw() {
                currentEcsInstance->camera.draw(&currentEcsInstance->system);
                debugModeDraw();
            }

            static void entityDestroy(const pk::entity_t e) {
                currentEcsInstance->entitiesToDestroy.push(e);
            }

            static void destroyAllEntities() {
                currentEcsInstance->shouldDestroyAllEntities = true;
            }

            static void resetCurrentEcsInstance() {
                currentEcsInstance->entity.clear();
                currentEcsInstance->component.clear();
                currentEcsInstance->system.clear();
                currentEcsInstance->camera.reset();
                currentEcsInstance->staticCollisions.clear();
                currentEcsInstance->entitiesToDestroy = std::queue<pk::entity_t>();
                currentEcsInstance->shouldDestroyAllEntities = false;
            }

            template<pk::component_id_t id>
            static const std::unordered_set<pk::entity_t>& getEntitiesFromSystem() {
                return currentEcsInstance->system.getEntitiesFromSystem<id>();
            }

            static const pk::EntityManager* getEntityManager() {
                return &currentEcsInstance->entity;
            }

            static const pk::ComponentManager* getComponentManager() {
                return &currentEcsInstance->component;
            }

            static const pk::SystemManager* getSystemManager() {
                return &currentEcsInstance->system;
            }

    };

}
