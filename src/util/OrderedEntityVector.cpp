//
// Created by vitor on 10/13/24.
//
#include "OrderedEntityVector.h"


pk::OrderedEntityVector::OrderedEntityVector() {
    this->entityToIndex.reserve(pk::MAX_ENTITIES);
    this->indexToEntity.reserve(pk::MAX_ENTITIES);
}


std::array<std::pair<float, pk::entity_t>, pk::MAX_ENTITIES>::iterator pk::OrderedEntityVector::begin() {
    return this->arr.begin();
}


std::array<std::pair<float, pk::entity_t>, pk::MAX_ENTITIES>::iterator pk::OrderedEntityVector::end() {
    return this->arr.begin() + this->mSize;
}


void pk::OrderedEntityVector::insert(const pk::entity_t e) {
    if (this->entityToIndex.find(e) == this->entityToIndex.end()) {
        this->entityToIndex[e] = this->mSize;
        this->indexToEntity[this->mSize] = e;
        this->arr[this->mSize++] = {0.0f, e};
    }
}


void pk::OrderedEntityVector::erase(const pk::entity_t e) {
    if (this->entityToIndex.find(e) != this->entityToIndex.end()) {
        const std::size_t lastIndex = --this->mSize;
        const std::size_t removedEntityIndex = this->entityToIndex[e];
        const pk::entity_t lastEntity = this->indexToEntity[lastIndex];

        this->entityToIndex[lastEntity] = removedEntityIndex;
        this->indexToEntity[removedEntityIndex] = lastEntity;

        this->arr[removedEntityIndex] = this->arr[lastIndex];

        this->entityToIndex.erase(e);
        this->indexToEntity.erase(lastIndex);
    }
}


void pk::OrderedEntityVector::update(const pk::entity_t e, const float y) {
    if (this->entityToIndex.find(e) == this->entityToIndex.end()) {
        this->insert(e);
    }
    this->arr[this->entityToIndex[e]].first = y;
}


void pk::OrderedEntityVector::sort() {
    std::sort(this->arr.begin(), this->arr.begin() + this->mSize);
}


void pk::OrderedEntityVector::clear() {
    this->entityToIndex.clear();
    this->indexToEntity.clear();
    this->mSize = 0;
}


std::size_t pk::OrderedEntityVector::size() const {
    return this->mSize;
}

