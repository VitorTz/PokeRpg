#pragma once
#include "../constants.hpp"
#include <array>
#include "../util/TypeManager.hpp"
#include "components.hpp"
#include <cassert>
#include <cstddef>
#include <memory>
#include <unordered_map>


namespace pk {

    
    class AbstractComponentArray {

    public:
        virtual ~AbstractComponentArray() = default;
        virtual void erase(pk::entity_t e) = 0;
        virtual void clear() = 0;
        virtual std::size_t size() const = 0;
    };

    template<typename T>
    class ComponentArray : public pk::AbstractComponentArray {

    private:
        std::array<T, pk::MAX_ENTITIES> arr{};
        std::unordered_map<pk::entity_t, std::size_t> entityToIndex{};
        std::unordered_map<std::size_t, pk::entity_t> indexToEntity{};
        std::size_t mSize{};

    public:
        ComponentArray() {
            this->entityToIndex.reserve(pk::MAX_ENTITIES);
            this->indexToEntity.reserve(pk::MAX_ENTITIES);
        }

        void insert(const pk::entity_t e, const T c) {
            assert(this->entityToIndex.find(e) == this->entityToIndex.end());
            this->entityToIndex[e] = this->mSize;
            this->indexToEntity[this->mSize] = e;
            this->arr[this->mSize++] = c;
        }

        void erase(const pk::entity_t e) override {
            if (this->entityToIndex.find(e) == this->entityToIndex.end()) {
                return;
            }

            const std::size_t lastIndex = --this->mSize;
            const std::size_t removedComponentIndex = this->entityToIndex[e];
            const pk::entity_t lastEntity = this->indexToEntity[lastIndex];

            this->arr[removedComponentIndex] = this->arr[lastIndex];

            this->entityToIndex[lastEntity] = removedComponentIndex;
            this->indexToEntity[removedComponentIndex] = lastEntity;

            this->entityToIndex.erase(e);
            this->indexToEntity.erase(lastIndex);
        }

        T& at(const pk::entity_t e) {
            assert(this->entityToIndex.find(e) != this->entityToIndex.end());
            return this->arr[this->entityToIndex[e]];
        }

        void clear() override {
            this->entityToIndex.clear();
            this->indexToEntity.clear();
            this->mSize = 0;
        }

        std::size_t size() const override {
            return this->mSize;
        }

    };


    class ComponentManager {

    private:
        std::unordered_map<pk::component_t, std::unique_ptr<pk::AbstractComponentArray>> componentMap{};

    private:
        template<typename T>
        void registerComponent() {
            this->componentMap.emplace(pk::gTypeManager.at<T>(), std::make_unique<pk::ComponentArray<T>>());
        }

    public:
        ComponentManager() {
            this->registerComponent<pk::transform_t>();
            this->registerComponent<pk::sprite_t>();
            this->registerComponent<pk::sprite_animation_t>();
            this->registerComponent<pk::character_t>();
            this->registerComponent<pk::random_movement_t>();
            assert(this->componentMap.size() == pk::NUM_COMPONENTS);
        }

        template<typename T>
        void insert(const pk::entity_t e, const T c) {
            dynamic_cast<pk::ComponentArray<T>*>(this->componentMap[pk::gTypeManager.at<T>()].get())->insert(e, c);
        }

        template<typename T>
        void erase(const pk::entity_t e) {
            this->componentMap[pk::gTypeManager.at<T>()]->erase(e);
        }

        template<typename T>
        T& at(const pk::entity_t e) {
            return dynamic_cast<pk::ComponentArray<T>*>(this->componentMap[pk::gTypeManager.at<T>()].get())->at(e);
        }

        void entityDestroy(const pk::entity_t e) {
            for (auto& pair : this->componentMap) {
                pair.second->erase(e);
            }
        }

        void clear() {
            for (auto& pair : this->componentMap) {
                pair.second->clear();
            }
        }

    };

}
