//
// Created by vitor on 10/19/24.
//

#ifndef UTIL_H
#define UTIL_H
#include <cstddef>
#include "../ecs/components.h"


namespace pk {

    std::size_t basicHash(const char* s);
    std::size_t hash(const char* s);
    bool checkTransformCollision(const pk::transform_t& l, const pk::transform_t& r);
    Vector2 getCenter(const pk::transform_t& t);

}

#endif //UTIL_H
