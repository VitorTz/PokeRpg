#pragma once
#include "../pokemon.hpp"
#include <memory>


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


    class LoadingScreen final : public pk::Scene {

        public:
            LoadingScreen();
            void update(float dt) override;
            void draw() override;

    };

    class LevelScene final : public pk::Scene {

        public:
            LevelScene();
            void update(float dt) override;
            void draw() override;

    };

    class TestScene1 final : public pk::Scene {

        public:
            TestScene1();
            void update(float dt) override;
            void draw() override;

    };

    class TestScene2 final : public pk::Scene {

    public:
        TestScene2();
        void update(float dt) override;
        void draw() override;

    };


    class SceneManager final : public pk::Scene {

        private:
            std::unique_ptr<pk::Scene> scene{};
            std::unique_ptr<pk::LoadingScreen> loadingScreen{};
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
