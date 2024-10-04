//
// Created by vitor on 10/3/24.
//

#ifndef SCENE_H
#define SCENE_H
#include "../ecs/ECS.h"


namespace pk {

    class Scene {

    public:
        virtual ~Scene() = default;
        virtual void update(float) = 0;
        virtual void draw() = 0;

    };

    class TitleScreen final : public pk::Scene {

    public:
        TitleScreen();
        void update(float) override;
        void draw() override;

    };

    class LoadingScreen final : public pk::Scene {

    public:
        LoadingScreen();
        void update(float) override;
        void draw() override;

    };

    class LevelScene final : public pk::Scene {

    public:
        LevelScene();
        void update(float) override;
        void draw() override;

    };

    class TestScene1 final : public pk::Scene {

    public:
        TestScene1();
        void update(float) override;
        void draw() override;

    };

    class SceneManager final : public pk::Scene {

    private:
        std::unique_ptr<pk::Scene> scene{};
        std::unique_ptr<pk::LoadingScreen> loadingScreen{};
        bool shouldChangeScene{};
        pk::SceneId nextScene{pk::MAIN_SCENE};

    private:
        void loadNextScene();

    public:
        void init();
        void update(float) override;
        void changeScene(pk::SceneId);
        void draw() override;

    };

    inline pk::SceneManager gSceneManager{};

}

#endif //SCENE_H
