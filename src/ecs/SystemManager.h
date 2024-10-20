//
// Created by vitor on 10/19/24.
//

#ifndef SYSTEMMANAGER_H
#define SYSTEMMANAGER_H
#include <cassert>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <vector>
#include "components.h"
#include "../constants.h"
#include "../util/TypeId.h"
#include "../util/types.h"


namespace pk {

    class System {

    public:
        std::unordered_set<pk::entity_t> entities{};

    public:
        virtual ~System() = default;
        virtual void update(float dt) = 0;
        virtual void draw(pk::entity_t e) = 0;
    };


    class TransformSystem final : public pk::System {

    public:
        void update(float dt) override;
        void draw(pk::entity_t e) override;
    };

    class SpriteSystem final : public pk::System {

    public:
        void update(float dt) override;
        void draw(pk::entity_t e) override;
    };

    class SpriteAnimationSystem final : public pk::System {

    public:
        void update(float dt) override;
        void draw(pk::entity_t e) override;
    };

    class TransitionSystem final : public pk::System {

    public:
        void update(float dt) override;
        void draw(pk::entity_t e) override;
    };

    class PlayerSystem final : public pk::System {

    public:
        void update(float dt) override;
        void draw(pk::entity_t e) override;
    };

    class SystemManager {

    private:
        std::unordered_map<pk::component_t, std::unique_ptr<pk::System>> systemMap{};
        std::unordered_map<pk::entity_t, std::unordered_set<pk::component_t>> entityToDrawableComponentsMap{};
        std::unordered_set<pk::component_t> drawableComponents{};
        std::vector<pk::component_t> systemOrder{};
        pk::PlayerSystem playerSystem{};

    private:
        template<typename T, typename S>
        void registerSystem() {
            const pk::component_t id = pk::gTypeId.get<T>();
            assert(this->systemMap.find(id) == this->systemMap.end());
            this->systemMap.emplace(id, std::make_unique<S>());
        }

    public:
        SystemManager() {
            for (pk::entity_t e = 0; e < pk::MAX_ENTITIES; e++) {
                this->entityToDrawableComponentsMap[e].reserve(pk::NUM_DRAWABLE_COMPONENTS);
            }

            // Register System
            this->registerSystem<pk::transform_t, pk::TransformSystem>();
            this->registerSystem<pk::sprite_t, pk::SpriteSystem>();
            this->registerSystem<pk::sprite_animation_t, pk::SpriteAnimationSystem>();
            this->registerSystem<pk::transition_t, pk::TransitionSystem>();
            assert(this->systemMap.size() == pk::NUM_COMPONENTS);

            // Register Drawable Components
            this->drawableComponents.insert(pk::gTypeId.get<sprite_t>());
            this->drawableComponents.insert(pk::gTypeId.get<sprite_animation_t>());
            this->drawableComponents.insert(pk::gTypeId.get<transition_t>());
            assert(this->drawableComponents.size() == pk::NUM_DRAWABLE_COMPONENTS);

            // Update Order
            this->systemOrder.push_back(pk::gTypeId.get<pk::sprite_t>());
            this->systemOrder.push_back(pk::gTypeId.get<pk::sprite_animation_t>());
            this->systemOrder.push_back(pk::gTypeId.get<pk::transition_t>());
        }

        template<typename T>
        void insert(const pk::entity_t e) {
            const pk::component_t id = pk::gTypeId.get<T>();
            this->systemMap[id]->entities.insert(e);
            if (this->drawableComponents.find(id) != this->drawableComponents.end()) {
                this->entityToDrawableComponentsMap[e].insert(id);
            }
        }

        template<typename T>
        void erase(const pk::entity_t e) {
            const pk::component_t id = pk::gTypeId.get<T>();
            this->systemMap[id]->entities.erase(e);
            this->entityToDrawableComponentsMap[e].erase(id);
        }

        void update(const float dt) {
            for (const pk::component_t id : this->systemOrder) {
                this->systemMap[id]->update(dt);
            }
            this->playerSystem.update(dt);
        }

        void draw(const std::vector<std::pair<float, pk::entity_t>>& entities) {
            for (const std::pair<float, pk::entity_t>& pair : entities) {
                for (const pk::component_t id : this->entityToDrawableComponentsMap[pair.second]) {
                    this->systemMap[id]->draw(pair.second);
                }
            }
        }

        void entityDestroy(const pk::entity_t e) {
            for (auto& pair : this->systemMap) {
                pair.second->entities.erase(e);
            }
            this->entityToDrawableComponentsMap[e].clear();
        }

        void clear() {
            for (auto& pair : this->systemMap) {
                pair.second->entities.clear();
            }
            for (auto& pair : this->entityToDrawableComponentsMap) {
                pair.second.clear();
            }
        }

        template<typename T>
        const std::unordered_set<pk::entity_t>& getEntitiesFromSystem() const {
            return this->systemMap[pk::gTypeId.get<T>()]->entities;
        }

    };

}


#endif //SYSTEMMANAGER_H
