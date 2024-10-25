#pragma once
#include "SceneId.hpp"
#include "raylib.h"
#include <unordered_map>


namespace pk {

    struct transition_pair_hash {
        inline std::size_t operator()(const std::pair<pk::SceneId, Rectangle> & pair) const {
            return pair.first;
        }
    };

    class Transition {

    private:
        std::unordered_map<pk::SceneId, Rectangle> transitionMap{};
        pk::SceneId transition{};        
        bool isTransitionHovered{};        

    public:
        Transition();
        void insert(pk::SceneId sceneId, Rectangle rect);
        void erase(pk::SceneId sceneId);
        void checkForTransition(const Rectangle& rect);
        void draw();

    };

}
