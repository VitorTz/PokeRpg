//
// Created by vitor on 10/19/24.
//

#ifndef TEXTUREPOOL_H
#define TEXTUREPOOL_H
#include <raylib.h>
#include <unordered_map>


namespace pk {


    class TexturePool {

    private:
        std::unordered_map<std::size_t, Texture2D> texturePool{};        

    public:
        TexturePool();
        Texture2D load(const char* fileName);        
        void erase(const char* fileName);
        void clear();
        std::size_t size() const;

    };

    inline pk::TexturePool gTexturePool{};

}

#endif //TEXTUREPOOL_H
