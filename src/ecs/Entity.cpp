#include "Entity.hpp"
#include "../constants.hpp"
#include <cassert>
#include <cstddef>
#include <queue>


pk::EntityManager::EntityManager() {
    for (pk::entity_t e = 0; e < pk::MAX_ENTITIES; e++) {
        this->q.push(e);
    }
}


pk::entity_t pk::EntityManager::create() {
    assert(this->q.empty() == false);
    const pk::entity_t e = this->q.front();
    this->q.pop();
    this->mSize++;
    return e;
}


void pk::EntityManager::destroy(const pk::entity_t e) {
    this->q.push(e);
    this->mSize--;
}


void pk::EntityManager::clear() {
    this->q = std::queue<pk::entity_t>();
    for (pk::entity_t e = 0; e < pk::MAX_ENTITIES; e++) {
        this->q.push(e);
    }
    this->mSize = 0;
}


std::size_t pk::EntityManager::size() const {
    return this->mSize;
}