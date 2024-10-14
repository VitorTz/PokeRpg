#pragma once
#include "../pokemon.hpp"


namespace pk {


    class TexturePool {

        private:
            std::unordered_map<std::size_t, Texture2D> texturePool{};

        public:
            TexturePool();
            Texture2D getTexture(const char* fileName);
            void eraseTexture(const char* fileName);
            void unloadAllTextures();
            std::size_t size() const;

    };

    inline pk::TexturePool gTexturePool{};

}
