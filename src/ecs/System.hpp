#pragma once
#include <cassert>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>
#include "components.hpp"
#include "../constants.hpp"
#include "../util/TypeManager.hpp"
#include "../util/types.hpp"


namespace pk {


    class System {

    public:
        virtual ~System() = default;
        virtual void update(float dt, const std::unordered_set<pk::entity_t>& entities) const = 0;
        virtual void draw(pk::entity_t e) const = 0;
    };

    class TransformSystem final : public pk::System {

    public:
        void update(float dt, const std::unordered_set<pk::entity_t>& entities) const override;
        void draw(pk::entity_t e) const override;
    };

    class SpriteSystem final : public pk::System {

    public:
        void update(float dt, const std::unordered_set<pk::entity_t>& entities) const override;
        void draw(pk::entity_t e) const override;
    };

    class SpriteAnimationSystem final : public pk::System {

    public:
        void update(float dt, const std::unordered_set<pk::entity_t>& entities) const override;
        void draw(pk::entity_t e) const override;
    };

    class CharacterSystem final : public pk::System {

    public:
        void update(float dt, const std::unordered_set<pk::entity_t>& entities) const override;
        void draw(pk::entity_t e) const override;
    };

    class RandomMovementSystem final : public pk::System {

    public:
        void update(float dt, const std::unordered_set<pk::entity_t>& entities) const override;
        void draw(pk::entity_t e) const override;
    };

    class SystemManager {

    private:
        typedef std::pair<std::unique_ptr<pk::System>, std::unordered_set<pk::entity_t>> SystemPair;

    private:        
        std::unordered_map<pk::component_t, SystemPair> systemMap{};        
        std::unordered_map<pk::entity_t, std::unordered_set<pk::component_t>> entityToDrawableComponents{};
        std::unordered_set<pk::component_t> drawableComponents{};
        std::vector<pk::component_t> systemOrder{};

    private:
        
        template<typename T, typename S>
        void registerSystem() {
            const pk::component_t id = pk::gTypeManager.at<T>();
            this->systemMap.emplace(
                id, 
                std::make_pair(
                    std::make_unique<S>(), 
                    std::unordered_set<pk::entity_t>()
                )
            );
        }

    public:

        SystemManager() {
            this->registerSystem<pk::transform_t, pk::TransformSystem>();
            this->registerSystem<pk::sprite_t, pk::SpriteSystem>();
            this->registerSystem<pk::sprite_animation_t, pk::SpriteAnimationSystem>();
            this->registerSystem<pk::random_movement_t, pk::RandomMovementSystem>();
            this->registerSystem<pk::character_t, pk::CharacterSystem>();
            assert(this->systemMap.size() == pk::NUM_COMPONENTS);

            this->drawableComponents.insert(pk::gTypeManager.at<pk::sprite_t>());
            this->drawableComponents.insert(pk::gTypeManager.at<pk::sprite_animation_t>());
            assert(this->drawableComponents.size() == pk::NUM_DRAWABLE_COMPONENTS);

            for (pk::entity_t e = 0; e < pk::MAX_ENTITIES; e++) {
                this->entityToDrawableComponents.insert(std::make_pair(e, std::unordered_set<pk::component_t>()));
            }

            this->systemOrder.reserve(pk::NUM_COMPONENTS);
            this->systemOrder.emplace_back(pk::gTypeManager.at<pk::random_movement_t>());
            this->systemOrder.emplace_back(pk::gTypeManager.at<pk::character_t>());
            this->systemOrder.emplace_back(pk::gTypeManager.at<pk::sprite_animation_t>());
        }
        
        template<typename T>
        void insert(const pk::entity_t e) {
            const pk::component_t id = pk::gTypeManager.at<T>();
            this->systemMap[id].second.insert(e);
            if (this->drawableComponents.find(id) != this->drawableComponents.end()) {
                this->entityToDrawableComponents[e].insert(id);
            }
        }
        
        template<typename T>
        void erase(const pk::entity_t e) {
            const pk::component_t id = pk::gTypeManager.at<T>();
            this->systemMap[id].second.erase(e);
            this->entityToDrawableComponents[e].erase(id);
        }

        template<typename T>
        const std::unordered_set<pk::entity_t>& getEntitiesFromSystem() {
            return this->systemMap[pk::gTypeManager.at<T>()].second;
        }

        void update(const float dt) {
            for (const pk::component_t id : this->systemOrder) {
                const pk::SystemManager::SystemPair& pair = this->systemMap[id];
                pair.first->update(dt, pair.second);
            }
        }

        void draw(const std::vector<std::pair<float, pk::entity_t>>& entities) const {
            for (const auto& pair : entities) {
                for (const pk::component_t id : this->entityToDrawableComponents.at(pair.second)) {
                    this->systemMap.at(id).first->draw(pair.second);
                }
            }
        }

        void entityDestroy(const pk::entity_t e) {
            for (auto& pair : this->systemMap) {
                pair.second.second.erase(e);
            }
            this->entityToDrawableComponents.clear();
        }

        void clear() {
            for (auto& pair : this->systemMap) {
                pair.second.second.clear();
            }
            for (auto& pair : this->entityToDrawableComponents) {
                pair.second.clear();
            }
        }


    };


}
