//
// Created by vitor on 10/19/24.
//

#ifndef PLAYER_H
#define PLAYER_H
#include <array>
#include <raylib.h>
#include "Action.h"
#include "Direction.h"
#include "types.h"
#include "../constants.h"


namespace pk {

    typedef struct player {
        pk::entity_t playerEntity{};
        pk::entity_t playerShadowEntity{};
        Rectangle collisionBox{pk::PLAYER_COLLISION_RECT};
        Rectangle actionBox{pk::PLAYER_ACTION_BOX};
        Vector2 center{};
        pk::Direction direction{pk::Direction::Down};
        pk::Action action{pk::Action::NoAction};
        bool isMoving{};
        player() = default;
        player(
            const pk::entity_t playerEntity,
            const pk::entity_t playerShadowEntity
        ) : playerEntity(playerEntity),
            playerShadowEntity(playerShadowEntity) { }
    } player_t;

}

#endif //PLAYER_H
