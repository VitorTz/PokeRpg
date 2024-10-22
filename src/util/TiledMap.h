#ifndef TILED_MAP_H
#define TILED_MAP_H
#include "MapId.h"
#include "types.h"


namespace pk {


    class TiledMap {

    public:        
        static float mapWidth(pk::MapId mapId);
        static float mapHeight(pk::MapId mapId);
        static void loadMap(pk::MapId mapId);
        static const pk::tiled_map_info_t& mapInfo(pk::MapId mapId);

    };
    

}


#endif