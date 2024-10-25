#include "util.hpp"


std::size_t pk::hash(const char *s) {
    std::size_t hash = 5381;
    int c;
    while ((c = *s++))
        hash = ((hash << 5) + hash) + c;
    return hash;
}


Vector2 pk::getCenter(const pk::transform_t &transform) {
    const Vector2 v{
        transform.pos.x + transform.size.x / 2.0f,
        transform.pos.y + transform.size.y / 2.0f
    };
    return v;
}

