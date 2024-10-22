//
// Created by vitor on 10/19/24.
//

#ifndef SCENE_H
#define SCENE_H
#include <memory>
#include <array>
#include "../constants.h"
#include "raylib.h"


namespace pk {


    class Scene {

    public:
        virtual ~Scene() = default;
        virtual void update(float dt) = 0;
        virtual void draw() = 0;
    };

    class TitleScreen final : public pk::Scene {
        
    private:
        std::array<Vector2, 2> backgroundPos{};
        Vector2 logoPos{};
        Vector2 pressSpacePos{};
        Texture2D pressSpace{};
        Texture2D logo{};
        Texture2D background{};

    public:
        TitleScreen();
        void update(float dt) override;
        void draw() override;
    };

    class WorldScene final : public pk::Scene {

    public:
        WorldScene();
        void update(float dt) override;
        void draw() override;
    };

    class FireArenaScene final : public pk::Scene {

    public:
        FireArenaScene();
        void update(float dt) override;
        void draw() override;
    };

    class PlantArenaScene final : public pk::Scene {

    public:
        PlantArenaScene();
        void update(float dt) override;
        void draw() override;
    };

    class WaterArenaScene final : public pk::Scene {

    public:
        WaterArenaScene();
        void update(float dt) override;
        void draw() override;
    };

    class HospitalScene final : public pk::Scene {

    public:
        HospitalScene();
        void update(float dt) override;
        void draw() override;
    };

    class HouseScene final : public pk::Scene {

    public:
        HouseScene();
        void update(float dt) override;
        void draw() override;
    };

    class LoadingScreen final : public pk::Scene {

    public:
        LoadingScreen();
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
        std::unique_ptr<pk::LoadingScreen> loadingScreen{};
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
