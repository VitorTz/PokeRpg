//
// Created by vitor on 10/3/24.
//
#include "TexturePool.h"
#include "util.h"


pk::TexturePool::TexturePool() {
    this->texturePool.reserve(256);
}


Texture2D pk::TexturePool::get(const char *fileName) {
    const unsigned long h = pk::hash(fileName);
    if (this->texturePool.find(h) == this->texturePool.end()) {
        this->texturePool.emplace(h, LoadTexture(fileName));
    }
    return this->texturePool[h];
}


void pk::TexturePool::erase(const char *fileName) {
    const unsigned long h = pk::hash(fileName);
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


