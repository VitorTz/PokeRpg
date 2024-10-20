//
// Created by vitor on 10/19/24.
//
#include "util.h"


std::size_t pk::hash(const char *s) {
    unsigned long hash = 5381;
    int c;
    while ((c = *s++))
        hash = ((hash << 5) + hash) + c;
    return hash;
}



bool pk::checkTransformCollision(const pk::transform_t &l, const pk::transform_t &r) {
    bool collision = false;
    if (
        (l.pos.x < (r.pos.x + r.size.x) && (l.pos.x + l.size.x) > r.pos.x) &&
        (l.pos.y < (r.pos.y + r.size.y) && (l.pos.y + l.size.y) > r.pos.y)
    ) collision = true;
    return collision;
}


Vector2 pk::getCenter(const pk::transform_t &t) {
    const Vector2 c{
        t.pos.x + t.size.x / 2.0f,
        t.pos.y + t.size.y / 2.0f
    };
    return c;
}

