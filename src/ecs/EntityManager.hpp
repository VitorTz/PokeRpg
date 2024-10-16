#pragma once
#include "../pokemon.hpp"


namespace pk {


    class EntityManager {

        private:
            std::queue<pk::entity_t> q{};
            std::size_t mSize{};
        
        public:
            EntityManager();
            pk::entity_t entityCreate();
            void entityDestroy(pk::entity_t e);
            void clear();
            std::size_t size() const;

    };

}