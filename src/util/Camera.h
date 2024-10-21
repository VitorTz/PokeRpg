//
// Created by vitor on 10/19/24.
//

#ifndef CAMERA_H
#define CAMERA_H
#include <array>
#include <map>
#include <raylib.h>
#include <vector>

#include "MapId.h"
#include "types.h"
#include "../constants.h"
#include "../ecs/SystemManager.h"


namespace pk {


    class Camera {

    private:
        Camera2D camera2D{};
        std::map<pk::zindex_t, std::vector<std::pair<float, pk::entity_t>>> entities{};
        std::array<bool, pk::MAX_ENTITIES> onCamera{};
        std::size_t mSize{};
        float maxYOffset;
        float maxXOffset;

    public:
        explicit Camera(pk::MapId mapId);
        void reset();

        void addZoom(float delta);
        void setZoom(float zoom);
        float getZoom() const;

        void setTarget(Vector2 target);
        Vector2 getTarget() const;

        void beginDrawing() const;
        void endDrawing() const;

        void insert(pk::entity_t e, pk::zindex_t zindex);
        void erase(pk::entity_t e, pk::zindex_t zindex);

        void handleMouseInput(float dt);
        void draw(pk::SystemManager* system);

        void clear();
        std::size_t size() const;

    };

}


#endif //CAMERA_H
