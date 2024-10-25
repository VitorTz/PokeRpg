#include "ObjectGroupId.hpp"
#include "../ecs/ECS.hpp"
#include "TiledMap.hpp"
#include "SceneId.hpp"
#include "CharacterId.hpp"
#include "raylib.h"
#include "types.hpp"
#include <cassert>
#include <fstream>
#include <string>


void pk::loadTiledMap(const pk::SceneId sceneId) {
    const pk::map_info_t& mapInfo = pk::MAP_INFO[sceneId];
    
    // Terrain
    std::string str = ASSETS_PATH "data/maps/" + std::string(mapInfo.name) + ".png";
    pk::ECS::spriteCreate(pk::CAMERA_ZINDEX_TERRAIN, str.c_str());
    
    // Game Objects
    str = ASSETS_PATH "data/maps/" + std::string(mapInfo.name) + ".txt";
    std::fstream file(str);
    assert(file.is_open());

    while (file >> str) {
        std::string imagePath{};
        pk::entity_t e{};

        float x, y, width, height;
        int objectGroupId, objectId, numObjects;

        file >> numObjects >> objectGroupId;
        
        for (int i = 0; i < numObjects; i++) {
            file >> x >> y >> width >> height >> objectId;
            x += mapInfo.worldOffset.x;
            y += mapInfo.worldOffset.y;
            
            switch (objectGroupId) {
                case pk::SpritesId:
                    file >> imagePath;
                    imagePath = ASSETS_PATH + imagePath;
                    pk::ECS::spriteCreate(pk::CAMERA_ZINDEX_CHARACTER, x, y, imagePath.c_str());
                    break;

                case pk::TreesId:
                    file >> imagePath;
                    imagePath = ASSETS_PATH + imagePath;
                    pk::ECS::staticCollisionAdd(
                        pk::ECS::spriteCreate(pk::CAMERA_ZINDEX_CHARACTER, x, y, imagePath.c_str()),
                        width, 
                        height
                    );
                    break;

                case pk::CollisionId:
                    pk::ECS::staticCollisionAdd(x, y, width, height);
                    break;

                case pk::EntitiesId:
                    e = pk::ECS::entityCreate(pk::CAMERA_ZINDEX_CHARACTER, x, y, true);
                    pk::ECS::getTransform(e).size = Vector2{pk::CHARACTER_SIZE, pk::CHARACTER_SIZE};
                    pk::ECS::componentAdd(e, pk::character_t{static_cast<pk::CharacterId>(objectId)});
                    
                    switch (objectId) {
                        case pk::PlayerId:
                            pk::ECS::getPlayer() = {
                                e,
                            pk::ECS::spriteCreate(
                                    pk::CAMERA_ZINDEX_SHADOW,
                                    ASSETS_PATH
                                    "graphics/other/shadow.png"
                                )
                            };
                            pk::ECS::componentAdd(
                                e,
                                pk::sprite_animation_t{
                                    ASSETS_PATH "graphics/characters/player.png",
                                    pk::CHARACTER_SIZE,
                                    pk::CHARACTER_SIZE,
                                    pk::ANIMATION_SPEED_NORMAL
                                }
                            );
                            break;
                        default:
                            break;
                    }

                    break;

                case pk::TransitionId:
                    pk::ECS::transitionAdd(
                        static_cast<pk::SceneId>(objectId),
                        Rectangle{x, y, width, height}
                    );
                    break;

                default:
                    break;
            }

        }

    }

}
