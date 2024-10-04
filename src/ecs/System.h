//
// Created by vitor on 10/3/24.
//

#ifndef SYSTEM_H
#define SYSTEM_H
#include "../pokemon.h"
#include "components.h"


namespace pk {

    class System {

    protected:
        const pk::TiledMapId mapId;

    public:
        std::unordered_set<pk::entity_t> entities{};

    public:
        explicit System(const pk::TiledMapId mapId) : mapId(mapId) { }
        virtual ~System() = default;
        virtual void update(float dt) = 0;
        virtual void draw(pk::entity_t e) = 0;
    };

    class TransformSystem final : public pk::System {

    public:
        explicit TransformSystem(const pk::TiledMapId mapId) : pk::System(mapId) { }
        void update(float dt) override;
        void draw(pk::entity_t e) override;

    };

    class SpriteSystem final : public pk::System {

    public:
        explicit SpriteSystem(const pk::TiledMapId mapId) : pk::System(mapId) { }
        void update(float dt) override;
        void draw(pk::entity_t e) override;

    };

    class SpriteAnimationSystem final : public pk::System {

    public:
        explicit SpriteAnimationSystem(const pk::TiledMapId mapId) : pk::System(mapId) { }
        void update(float dt) override;
        void draw(pk::entity_t e) override;

    };

    class SystemManager {

    private:
        std::unordered_map<pk::component_t, std::unique_ptr<pk::System>> systemMap{};
        std::unordered_map<pk::entity_t, std::unordered_set<pk::component_t>> entityToDrawableComponents{};
        std::unordered_set<pk::component_t> drawableComponents{};
        std::vector<pk::component_t> systemUpdateOrder{};
        const pk::TiledMapId mapId;


    public:
        explicit SystemManager(const pk::TiledMapId mapId) : mapId(mapId) {
            this->systemMap.emplace(pk::getComponentId<pk::transform_t>(), std::make_unique<pk::TransformSystem>(this->mapId));
            this->systemMap.emplace(pk::getComponentId<pk::sprite_t>(), std::make_unique<pk::SpriteSystem>(this->mapId));
            this->systemMap.emplace(pk::getComponentId<pk::sprite_animation_t>(), std::make_unique<pk::SpriteAnimationSystem>(this->mapId));
            assert(this->systemMap.size() == pk::NUM_COMPONENTS);

            for (pk::entity_t e = 0; e < pk::MAX_ENTITIES; e++) {
                this->entityToDrawableComponents[e].reserve(pk::NUM_COMPONENTS);
            }

            this->systemUpdateOrder.push_back(pk::getComponentId<pk::sprite_t>());
            this->systemUpdateOrder.push_back(pk::getComponentId<pk::sprite_animation_t>());

            this->drawableComponents.insert(pk::getComponentId<pk::sprite_t>());
            this->drawableComponents.insert(pk::getComponentId<pk::sprite_animation_t>());

        }

        template<typename T>
        void insert(const pk::entity_t e) {
            const pk::component_t id = pk::getComponentId<T>();
            this->systemMap[id]->entities.insert(e);
            if (this->drawableComponents.find(id) != this->drawableComponents.end()) {
                this->entityToDrawableComponents[e].insert(id);
            }
        }

        template<typename T>
        void erase(const pk::entity_t e) {
            const pk::component_t id = pk::getComponentId<T>();
            this->systemMap[id]->entities.erase(e);
            this->entityToDrawableComponents[e].erase(id);
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

        template<typename T>
        const std::unordered_set<pk::entity_t>& getEntities() const {
            const pk::component_t id = pk::getComponentId<T>();
            return this->systemMap.at(id)->entities;
        }

        void update(const float dt) {
            for (const pk::component_t id : this->systemUpdateOrder) {
                this->systemMap[id]->update(dt);
            }
        }

        void draw(const std::vector<std::pair<float, pk::entity_t>>& v) {
            for (const std::pair<float, pk::entity_t>& pair : v) {
                for (const pk::component_t id : this->entityToDrawableComponents[pair.second]) {
                    this->systemMap[id]->draw(pair.second);
                }
            }
        }

    };

}

#endif //SYSTEM_H
