//
// Created by vitor on 10/13/24.
//

#ifndef MRANDOM_H
#define MRANDOM_H
#include "../pokemon.hpp"


namespace pk::random {

    inline std::random_device gen{};
    inline std::uniform_real_distribution<float> randScreenXPos(0.0f, pk::SCREEN_W);
    inline std::uniform_real_distribution<float> randScreenYPos(-pk::SCREEN_H, 0.0f);

}


#endif //MRANDOM_H
