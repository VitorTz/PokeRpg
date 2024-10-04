//
// Created by vitor on 10/3/24.
//

#ifndef CAMERA_H
#define CAMERA_H
#include "../pokemon.h"
#include "../ecs/System.h"


namespace pk {

    class Camera {

    private:
        Camera2D camera{};
        std::map<pk::zindex_t, std::vector<std::pair<float, pk::entity_t>>> entities{};
        std::unordered_set<pk::entity_t> entitiesOnCamera{};
        const pk::TiledMapId mapId;
        float maxTargetX{};
        float maxTargetY{};

    public:
        explicit Camera(pk::TiledMapId mapId);
        void reset();
        void setTarget(float x, float y);
        void beginDrawing() const;
        void endDrawing() const;
        void insert(pk::entity_t e, pk::zindex_t zindex);
        void erase(pk::entity_t e, pk::zindex_t zindex);
        void draw(pk::SystemManager* system);
        void clear();
        std::size_t size() const;

    };

}


#endif //CAMERA_H
