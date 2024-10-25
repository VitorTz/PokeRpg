//
// Created by vitor on 10/24/24.
//

#ifndef FONTPOOL_H
#define FONTPOOL_H
#include <raylib.h>
#include <unordered_map>

#include "FontId.h"


namespace pk {



    class FontPool {

    private:
        std::unordered_map<pk::FontId, Font> fontPool{};

    public:
        void init();
        Font get(pk::FontId fontId);
        void clear();

    };

    inline pk::FontPool gFontPool{};


}

#endif //FONTPOOL_H
