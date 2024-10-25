//
// Created by vitor on 10/24/24.
//
#include "FontPool.h"

#include "../constants.hpp"


void pk::FontPool::init() {
    this->fontPool.emplace(pk::FontId::Light, LoadFont(pk::FONT_PATH[pk::FontId::Light]));
    this->fontPool.emplace(pk::FontId::Regular, LoadFont(pk::FONT_PATH[pk::FontId::Regular]));
    this->fontPool.emplace(pk::FontId::Semibold, LoadFont(pk::FONT_PATH[pk::FontId::Semibold]));
    this->fontPool.emplace(pk::FontId::Bold, LoadFont(pk::FONT_PATH[pk::FontId::Bold]));
}


Font pk::FontPool::get(const pk::FontId fontId) {
    return this->fontPool[fontId];
}


void pk::FontPool::clear() {
    this->fontPool.clear();
}

