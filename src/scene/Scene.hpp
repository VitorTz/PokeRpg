#pragma once
#include <memory>
#include "../util/SceneId.hpp"
#include "../constants.hpp"


namespace pk {

    class Scene {

    public:
        virtual ~Scene() = default;
        virtual void update(float dt) = 0;
        virtual void draw() = 0;
    };

    class TitleScreen : public pk::Scene {
    
    public:
        TitleScreen();
        void update(float dt) override;
        void draw() override;
    };

    class WorldScene : public pk::Scene {

    public:
        WorldScene();
        void update(float dt) override;
        void draw() override;
    };

    class SceneManager : public pk::Scene {

    private:
        std::unique_ptr<pk::Scene> scene{};
        pk::SceneId sceneId{pk::MAIN_SCENE};
        bool shouldChangeScene{};
        void loadNextScene();

    public:
        void init();
        void changeScene(pk::SceneId sceneId);
        void update(float dt) override;
        void draw() override;

    };

    inline pk::SceneManager gSceneManager{};

}