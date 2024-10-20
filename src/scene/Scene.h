//
// Created by vitor on 10/19/24.
//

#ifndef SCENE_H
#define SCENE_H
#include <memory>
#include "../constants.h"


namespace pk {


    class Scene {

    public:
        virtual ~Scene() = default;
        virtual void update(float dt) = 0;
        virtual void draw() = 0;
    };

    class TitleScreen final : public pk::Scene {

    public:
        TitleScreen();
        void update(float dt) override;
        void draw() override;
    };

    class Level final : public pk::Scene {

    public:
        Level();
        void update(float dt) override;
        void draw() override;
    };

    class TestScene1 final : public pk::Scene {

    public:
        TestScene1();
        void update(float dt) override;
        void draw() override;
    };

    class SceneManager final : public pk::Scene {

    private:
        std::unique_ptr<pk::Scene> scene{};
        pk::SceneId sceneId{pk::MAIN_SCENE};
        bool shouldChangeScene{};

    private:
        void loadNextScene();

    public:
        void init();
        void changeScene(pk::SceneId sceneId);
        void update(float dt) override;
        void draw() override;
    };

    inline pk::SceneManager gSceneManager{};

}

#endif //SCENE_H
