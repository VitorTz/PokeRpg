#include "TiledMap.h"
#include "../constants.h"
#include "../ecs/EcsManager.h"
#include "MapId.h"
#include "player.h"
#include "types.h"
#include <string>
#include <cassert>
#include <fstream>


float pk::TiledMap::mapWidth(const pk::MapId mapId) {
    return pk::TILED_MAP_INFO[mapId].width;
}


float pk::TiledMap::mapHeight(const pk::MapId mapId) {
    return pk::TILED_MAP_INFO[mapId].height;
}


const pk::tiled_map_info_t& pk::TiledMap::mapInfo(const pk::MapId mapId) {
    return pk::TILED_MAP_INFO[mapId];
}


void pk::TiledMap::loadMap(const pk::MapId mapId) {
    
    // Setting Ecs Instance to Instance of MapId
        const pk::MapId lastMapId = pk::EcsManager::getCurrentMapId();
        const pk::tiled_map_info_t& mMapinfo = mapInfo(mapId);
        pk::EcsManager::setCurrentEcsInstance(mapId);    

    // Player
        pk::player_t& player = pk::EcsManager::getPlayer();
        
        player = pk::player_t{
        pk::EcsManager::entityCreate(pk::ZINDEX_PLAYER, true),
        pk::EcsManager::entityCreate(pk::ZINDEX_SHADOW, true)
        };
        pk::transform_t& playerTransform = pk::EcsManager::getTransform(player.playerEntity);
        playerTransform.pos.x = mMapinfo.playerStartPos.x - pk::PLAYER_SIZE.x / 2.0f;
        playerTransform.pos.y = mMapinfo.playerStartPos.x - pk::PLAYER_SIZE.y / 2.0f;
        playerTransform.size = pk::PLAYER_SIZE;
        pk::EcsManager::addComponent(player.playerEntity, pk::sprite_animation_t{pk::PLAYER_SPRITE_ANIMATION});    

    // Ground image
        pk::EcsManager::spriteCreate(pk::ZINDEX_GROUND, mMapinfo.groundImagePath);

    // Game Objects
        std::string gameObjectGroup{};        
        std::fstream mapFile(mMapinfo.txtFile);
        assert(mapFile.is_open());

        while (mapFile >> gameObjectGroup) {            
            float x, y, width, height;
            std::string str;
            int n;
            
            mapFile >> n;

            for (int i = 0; i < n; i++) {
                mapFile >> x >> y >> width >> height;

                if (gameObjectGroup == "Collision") {
                    pk::EcsManager::addStaticCollision(Rectangle{x, y, width, height});                    
                    continue;
                }

                if (gameObjectGroup == "Sprites") {                    
                    mapFile >> str;
                    str = ASSETS_PATH + str;
                    pk::EcsManager::spriteCreate(pk::ZINDEX_PLAYER, x, y, str.c_str());
                    continue;
                }

                if (gameObjectGroup == "Trees") {                    
                    mapFile >> str;
                    str = ASSETS_PATH + str;
                    pk::EcsManager::addStaticCollision(
                        pk::EcsManager::spriteCreate(pk::ZINDEX_PLAYER, x, y, str.c_str()),
                        48.0f,
                        48.0f
                    );
                    continue;
                }

                if (gameObjectGroup == "Houses") {                    
                    mapFile >> str;
                    str = ASSETS_PATH + str;
                    pk::EcsManager::spriteCreate(pk::ZINDEX_PLAYER, x, y, str.c_str());
                    continue;
                }

                if (gameObjectGroup == "Arena") {                    
                    mapFile >> str;
                    str = ASSETS_PATH + str;
                    pk::EcsManager::spriteCreate(pk::ZINDEX_PLAYER, x, y, str.c_str());
                    continue;
                }

                if (gameObjectGroup == "Hospital") {                    
                    mapFile >> str;
                    str = ASSETS_PATH + str;
                    pk::EcsManager::spriteCreate(pk::ZINDEX_PLAYER, x, y, str.c_str());
                    continue;
                }

                if (gameObjectGroup == "Transition") {                    
                    mapFile >> str;
                    assert(pk::gStringToTransitionType.find(str) != pk::gStringToTransitionType.end());
                    pk::EcsManager::addComponent(
                        pk::EcsManager::entityCreate(pk::ZINDEX_MAX, true),
                        pk::transition_t{
                            false,
                            Rectangle{x, y, width, height},
                            pk::gStringToTransitionType.at(str)
                        }
                    );
                    continue;
                }
            }
        }

        mapFile.close();    

    // Set back last Ecs Instance
    pk::EcsManager::setCurrentEcsInstance(lastMapId);
}