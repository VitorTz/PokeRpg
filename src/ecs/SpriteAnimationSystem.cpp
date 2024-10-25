#include <unordered_set>
#include "components.hpp"
#include "ECS.hpp"
#include "raylib.h"
#include "System.hpp"


void pk::SpriteAnimationSystem::update(
    [[maybe_unused]] const float dt,
    const std::unordered_set<pk::entity_t>& entities
) const {
    for (const pk::entity_t e : entities) {
        auto& spriteAnimation = pk::ECS::componentGet<pk::sprite_animation_t>(e);
        const pk::transform_t& transform = pk::ECS::getTransform(e);

        if (transform.isMoving == false) {
            spriteAnimation.textureRect.x = 0.0f;
            spriteAnimation.frame = 0;
            continue;
        }

        spriteAnimation.frame++;
        if (spriteAnimation.frame > spriteAnimation.maxFrame) {
            spriteAnimation.frame = 0;
            spriteAnimation.spriteIndex = (spriteAnimation.spriteIndex + 1) % spriteAnimation.maxSpriteIndex;
            spriteAnimation.textureRect.x = spriteAnimation.textureRect.width * spriteAnimation.spriteIndex;
        }

        switch (transform.direction) {
            case pk::Down:
                spriteAnimation.textureRect.y = 0.0f;
                break;
            case pk::Left:
                spriteAnimation.textureRect.y = pk::CHARACTER_SIZE;
                break;
            case pk::Right:
                spriteAnimation.textureRect.y = pk::CHARACTER_SIZE * 2.0f;
                break;
            case pk::Up:
                spriteAnimation.textureRect.y = pk::CHARACTER_SIZE * 3.0f;
                break;
            default:
                break;
        }

    }
}


void pk::SpriteAnimationSystem::draw(const pk::entity_t e) const {
    const pk::sprite_animation_t& spriteAnimation = pk::ECS::componentGet<pk::sprite_animation_t>(e);
    const pk::transform_t& transform = pk::ECS::getTransform(e);
    DrawTextureRec(spriteAnimation.texture, spriteAnimation.textureRect, transform.pos, WHITE);
}
