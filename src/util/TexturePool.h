//
// Created by vitor on 10/3/24.
//

#ifndef TEXTUREPOOL_H
#define TEXTUREPOOL_H
#include "../pokemon.h"

namespace pk {

    class TexturePool {

    private:
        std::unordered_map<unsigned long, Texture2D> texturePool{};

    public:
        TexturePool();
        Texture2D get(const char* fileName);
        void erase(const char* fileName);
        void clear();
        std::size_t size() const;

    };

    inline pk::TexturePool gTexturePool{};

}

#endif //TEXTUREPOOL_H
