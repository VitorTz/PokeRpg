#include "Transition.hpp"
#include <utility>
#include "FontPool.h"
#include "raylib.h"
#include "SceneId.hpp"
#include "../constants.hpp"
#include "../scene/Scene.hpp"


pk::Transition::Transition() = default;


void pk::Transition::insert(const pk::SceneId sceneId, const Rectangle rect) {
    this->transitionMap.emplace(sceneId, rect);    
}


void pk::Transition::erase(const pk::SceneId sceneId) {
    this->transitionMap.erase(sceneId);    
}


void pk::Transition::checkForTransition(const Rectangle& rect) {
    this->isTransitionHovered = false;
    for (const auto& pair : this->transitionMap) {
        if (CheckCollisionRecs(rect, pair.second)) {
            this->transition = pair.first;
            this->isTransitionHovered = true;
            break;
        }
    }

    if (this->isTransitionHovered && IsKeyPressed(ACTION_KEY)) {
        pk::gSceneManager.changeScene(this->transition);
    }
}


void pk::Transition::draw() {
    if (this->isTransitionHovered) {
        const Rectangle& rect = this->transitionMap[this->transition];
        DrawTextEx(
            pk::gFontPool.get(pk::FontId::Regular),
            "PRESS F",
            Vector2{rect.x, rect.y},
            16.0f,
            1.0f,
            WHITE
        );
    }
}
