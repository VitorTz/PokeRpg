//
// Created by vitor on 10/19/24.
//

#ifndef ENTITYMANAGER_H
#define ENTITYMANAGER_H
#include <queue>
#include "../constants.h"


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

#endif //ENTITYMANAGER_H
