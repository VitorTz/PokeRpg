#pragma once
#include <cstddef>
#include <queue>
#include "../util/types.hpp"


namespace pk {


    class EntityManager {

    private:
        std::queue<pk::entity_t> q{};
        std::size_t mSize{};
    
    public:
        EntityManager();
        pk::entity_t create();
        void destroy(pk::entity_t e);
        void clear();
        std::size_t size() const;

    };

}