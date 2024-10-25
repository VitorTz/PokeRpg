#pragma once
#include "SceneId.hpp"
#include "raylib.h"
#include "types.hpp"
#include "../ecs/System.hpp"
#include "../constants.hpp"
#include <array>
#include <cstddef>
#include <map>
#include <vector>


namespace pk {


    class Camera {

    private:
        Camera2D camera{};
        std::map<pk::zindex_t, std::vector<std::pair<float, pk::entity_t>>> entities{};
        std::array<bool, pk::MAX_ENTITIES> onCamera{};
        std::size_t mSize{};
        float maxWidth{};
        float maxHeight{};

    public:
        explicit Camera(const pk::SceneId sceneId);
        void setTarget(Vector2 target);
        void addZoom(float delta);
        void setZoom(float zoom);
        void insert(pk::entity_t e, pk::zindex_t zindex);
        void erase(pk::entity_t e, pk::zindex_t zindex);
        void handleInput(float dt);
        void beginDrawing() const;
        void endDrawing() const;
        void draw(const pk::SystemManager* systemManager);
        void reset();
        void clear();
        std::size_t size() const;

    };

}