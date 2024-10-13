#pragma once
#include "../pokemon.hpp"
#include "components.hpp"
#include <cassert>
#include <unordered_map>
#include <unordered_set>


namespace pk {


    class System {

        public:
            std::unordered_set<pk::entity_t> entities{};

        public:
            virtual ~System() = default;
            virtual void update(float dt) = 0;
            virtual void draw(pk::entity_t e) = 0;

    };

    class TransformSystem : public pk::System {

        public:
            void update(float dt) override;
            void draw(pk::entity_t e) override;

    };


    class SpriteSystem : public pk::System {

        public:
            void update(float dt) override;
            void draw(pk::entity_t e) override;

    };

    class SpriteAnimationSystem : public pk::System {

        public:
            void update(float dt) override;
            void draw(pk::entity_t e) override;

    };

    class SystemManager {

        private:
            std::unordered_map<pk::component_t, std::unique_ptr<pk::System>> systemMap{};
            std::unordered_map<pk::entity_t, std::unordered_set<pk::component_t>> entityToDrawableComponents{};
            std::unordered_set<pk::component_t> drawableComponents{};
            std::vector<pk::component_t> systemOrder{};

        public:
            SystemManager() {
                this->systemMap.reserve(pk::NUM_COMPONENTS);
                this->systemMap.emplace(pk::id::transform, std::make_unique<pk::TransformSystem>());
                this->systemMap.emplace(pk::id::sprite, std::make_unique<pk::SpriteSystem>());
                this->systemMap.emplace(pk::id::sprite_animation, std::make_unique<pk::SpriteAnimationSystem>());
                assert(this->systemMap.size() == pk::NUM_COMPONENTS);
                
                for (pk::entity_t e = 0; e < pk::MAX_ENTITIES; e++) {
                    this->entityToDrawableComponents[e].reserve(pk::NUM_COMPONENTS);
                }

                this->drawableComponents.reserve(pk::NUM_COMPONENTS);
                this->drawableComponents.insert(pk::id::sprite);
                this->drawableComponents.insert(pk::id::sprite_animation);

                this->systemOrder.reserve(pk::NUM_COMPONENTS);
                this->systemOrder.emplace_back(pk::id::sprite_animation);
            }

            template<pk::component_t id>
            void insert(const pk::entity_t e) {
                this->systemMap[id]->entities.insert(e);
                if (this->drawableComponents.find(id) != this->drawableComponents.end()) {
                    this->entityToDrawableComponents[e].insert(id);
                }                
            }

            template<pk::component_t id>
            void erase(const pk::entity_t e) {
                this->systemMap[id]->entities.erase(e);
                this->entityToDrawableComponents[e].erase(e);                
            }

            void update(const float dt) {
                for (const pk::component_t id : this->systemOrder) {
                    this->systemMap[id]->update(dt);
                }
            }

            void draw(const std::vector<std::pair<float, pk::entity_t>>& entities) {
                for (const std::pair<float, pk::entity_t>& pair : entities) {
                    for (const pk::component_t id : this->entityToDrawableComponents[pair.second]) {
                        this->systemMap[id]->draw(pair.second);
                    }
                }
            }

            void entityDestroy(const pk::entity_t e) {
                for (auto& pair : this->systemMap) {
                    pair.second->entities.erase(e);
                }
                this->entityToDrawableComponents[e].clear();
            }

            void clear() {
                for (auto& pair : this->systemMap) {
                    pair.second->entities.clear();
                }
                for (auto& pair : this->entityToDrawableComponents) {
                    pair.second.clear();
                }
            }

            template<pk::component_t id>
            const std::unordered_set<pk::entity_t>& getEntitiesFromSystem() const {
                return this->systemMap.at(id)->entities;
            }

    };

}
