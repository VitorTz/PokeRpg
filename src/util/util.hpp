#pragma once
#include "../pokemon.hpp"


namespace pk {


    std::size_t hash(const char* s);

    void loadMap(pk::MapId mapId);

}