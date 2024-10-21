//
// Created by vitor on 10/19/24.
//
#include "util.h"


std::size_t pk::basicHash(const char *s) {
    std::size_t hash = 5381;
    int c;
    while ((c = *s++))
        hash = (hash << 5) + hash + c;
    return hash;
}


std::size_t pk::hash(const char *s) {
    constexpr int m = 1e9 + 9;
    constexpr int p = 31;
    long long hash_value = 0;
    long long p_pow = 1;
    int c;
    while ((c = *s++)) {
        hash_value = (hash_value + (c - 'a' + 1) * p_pow) % m;
        p_pow = p_pow * p % m;
    }
    return hash_value;
}


bool pk::checkTransformCollision(const pk::transform_t &l, const pk::transform_t &r) {
    return l.pos.x < r.pos.x + r.size.x &&
           l.pos.x + l.size.x > r.pos.x &&
           l.pos.y < r.pos.y + r.size.y &&
           l.pos.y + l.size.y > r.pos.y;
}


Vector2 pk::getCenter(const pk::transform_t &t) {
    const Vector2 c{
        t.pos.x + t.size.x / 2.0f,
        t.pos.y + t.size.y / 2.0f
    };
    return c;
}
