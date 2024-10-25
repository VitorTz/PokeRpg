//
// Created by vitor on 10/24/24.
//

#ifndef PLAYER_HPP
#define PLAYER_HPP
#include <raylib.h>
#include "../constants.hpp"
#include "../util/types.hpp"


namespace pk {

    typedef struct player {
        pk::entity_t playerEntity{};
        pk::entity_t shadowEntity{};
        Rectangle actionBox{};
        Rectangle collideBox{0.0f, 0.0f, pk::PLAYER_COLLIDE_BOX_W, pk::PLAYER_COLLIDE_BOX_H};
        player() = default;
        player(
            const pk::entity_t playerEntity,
            const pk::entity_t shadowEntity
        ) : playerEntity(playerEntity),
            shadowEntity(shadowEntity) { }
    } player_t;

    void playerUpdate(pk::player_t& player, float dt);
    void playerDebug(const pk::player_t& player);

}

#endif //PLAYER_HPP
