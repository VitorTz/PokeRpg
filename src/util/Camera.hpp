#pragma once
#include "../pokemon.hpp"
#include "../ecs/SystemManager.hpp"
#include "../ecs/components.hpp"


namespace pk {

    class Camera {

        private:
            Camera2D camera2D{};
            std::map<pk::zindex_t, std::vector<std::pair<float, pk::entity_t>>> zindexToEntities{};
            std::array<bool, pk::MAX_ENTITIES> onCamera{};
            Rectangle cameraRect{};
            std::size_t mSize{};

        public:
            Camera();
            void insert(pk::entity_t e, pk::zindex_t zindex);
            void erase(pk::entity_t e, pk::zindex_t zindex);
            void beginDrawing() const;
            void endDrawing() const;
            void draw(pk::SystemManager* systemManager);
            void moveTarget(float x, float y);
            void setTarget(float x, float y);
            void handleMouseInput(float dt);
            void addZoom(float zoom);
            void setZoom(float zoom);
            void clear();
            void reset();
            const Camera2D& getCamera2D() const;
            std::size_t size() const;

    };

}
