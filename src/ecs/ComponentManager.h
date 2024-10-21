//
// Created by vitor on 10/19/24.
//

#ifndef COMPONENTMANAGER_H
#define COMPONENTMANAGER_H
#include <array>
#include <cassert>
#include <memory>
#include <unordered_map>

#include "components.h"
#include "../constants.h"
#include "../util/TypeId.h"


namespace pk {


    class AbstractComponentArray {

    public:
        virtual ~AbstractComponentArray() = default;
        virtual void erase(pk::entity_t e) = 0;
        virtual void clear() = 0;
        virtual std::size_t size() const = 0;
    };

    template<typename T>
    class ComponentArray final : public pk::AbstractComponentArray {

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

        typename std::array<T, pk::MAX_ENTITIES>::const_iterator begin() const {
            return this->arr.begin();
        }

        typename std::array<T, pk::MAX_ENTITIES>::const_iterator end() const {
            return this->arr.begin() + this->mSize;
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

            this->indexToEntity[removedComponentIndex] = lastEntity;
            this->entityToIndex[lastEntity] = removedComponentIndex;

            this->arr[removedComponentIndex] = this->arr[lastIndex];

            this->entityToIndex.erase(e);
            this->indexToEntity.erase(lastIndex);
        }

        T& at(const pk::entity_t e) {
            assert(this->entityToIndex.find(e) != this->entityToIndex.end());
            return this->arr[this->entityToIndex[e]];
        }

        pk::entity_t entityAtIndex(const std::size_t i) const {
            assert(this->indexToEntity.find(i) != this->indexToEntity.end());
            return this->indexToEntity.at(i);
        }

        const T& componentAtIndex(const std::size_t i) const {
            return this->arr[i];
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

    public:
        ComponentManager() {
            this->componentMap.emplace(pk::gTypeId.get<pk::transform_t>(), std::make_unique<pk::ComponentArray<pk::transform_t>>());
            this->componentMap.emplace(pk::gTypeId.get<pk::sprite_t>(), std::make_unique<pk::ComponentArray<pk::sprite_t>>());
            this->componentMap.emplace(pk::gTypeId.get<pk::sprite_animation_t>(), std::make_unique<pk::ComponentArray<pk::sprite_animation_t>>());
            this->componentMap.emplace(pk::gTypeId.get<pk::transition_t>(), std::make_unique<pk::ComponentArray<pk::transition_t>>());
            assert(this->componentMap.size() == pk::NUM_COMPONENTS);
        }

        template<typename T>
        void insert(const pk::entity_t e, const T c) {
            dynamic_cast<pk::ComponentArray<T>*>(this->componentMap[pk::gTypeId.get<T>()].get())->insert(e, std::move(c));
        }

        template<typename T>
        void erase(const pk::entity_t e) {
            this->componentMap[pk::gTypeId.get<T>()]->erase(e);
        }

        template<typename T>
        T& at(const pk::entity_t e) {
            return dynamic_cast<pk::ComponentArray<T>*>(this->componentMap[pk::gTypeId.get<T>()].get())->at(e);
        }

        template<typename T>
        const pk::ComponentArray<T>* getComponentArray() {
            return dynamic_cast<pk::ComponentArray<T>*>(this->componentMap[pk::gTypeId.get<T>()].get());
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


#endif //COMPONENTMANAGER_H
