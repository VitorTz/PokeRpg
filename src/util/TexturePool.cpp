//
// Created by vitor on 10/19/24.
//
#include "TexturePool.h"
#include <cassert>
#include "util.h"


pk::TexturePool::TexturePool() {
    this->texturePool.reserve(256);
}


Texture2D pk::TexturePool::load(const char *fileName) {
    const std::size_t h = pk::hash(fileName);
    if (this->texturePool.find(h) == this->texturePool.end()) {
        this->texturePool.emplace(h, LoadTexture(fileName));
        assert(this->texturePool[h].id > 0);
    }
    return this->texturePool[h];
}


void pk::TexturePool::erase(const char *fileName) {
    const std::size_t h = pk::hash(fileName);
    if (this->texturePool.find(h) != this->texturePool.end()) {
        UnloadTexture(this->texturePool[h]);
    }
    this->texturePool.erase(h);
}


void pk::TexturePool::clear() {
    for (auto& pair : this->texturePool) {
        UnloadTexture(pair.second);
    }
    this->texturePool.clear();
}


std::size_t pk::TexturePool::size() const {
    return this->texturePool.size();
}




