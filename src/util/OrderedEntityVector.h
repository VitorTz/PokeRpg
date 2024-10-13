//
// Created by vitor on 10/13/24.
//

#ifndef ORDEREDENTITYVECTOR_H
#define ORDEREDENTITYVECTOR_H
#include "../pokemon.hpp"


namespace pk {

    class OrderedEntityVector {

    private:
        std::array<std::pair<float, pk::entity_t>, pk::MAX_ENTITIES> arr{};
        std::unordered_map<pk::entity_t, std::size_t> entityToIndex{};
        std::unordered_map<std::size_t, pk::entity_t> indexToEntity{};
        std::size_t mSize{};


    public:
        OrderedEntityVector();
        pk::entity_t& operator[](const std::size_t i) {
            return this->arr[i].second;
        }
        const pk::entity_t& operator[](const std::size_t i) const {
            return this->arr[i].second;
        }
        std::array<std::pair<float, pk::entity_t>, pk::MAX_ENTITIES>::iterator begin();
        std::array<std::pair<float, pk::entity_t>, pk::MAX_ENTITIES>::iterator end();

        void insert(pk::entity_t e);
        void update(pk::entity_t e, float y);
        void erase(pk::entity_t e);
        void sort();
        void clear();
        std::size_t size() const;


    };

}

#endif //ORDEREDENTITYVECTOR_H
