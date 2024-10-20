//
// Created by vitor on 10/19/24.
//

#ifndef TYPEID_H
#define TYPEID_H
#include <cassert>
#include <typeinfo>
#include <unordered_map>
#include "types.h"


namespace pk {


    class TypeId {

    private:
        std::unordered_map<const char*, pk::component_t> componentIdMap{};

    public:

        template<typename T>
        void registerType() {
            const char* name = typeid(T).name();
            assert(this->componentIdMap.find(name) == this->componentIdMap.end());
            this->componentIdMap.emplace(name, this->componentIdMap.size());
        }

        template<typename T>
        pk::component_t get() {
            return this->componentIdMap[typeid(T).name()];
        }

        std::size_t numRegisteredComponents() const {
            return this->componentIdMap.size();
        }

    };

    inline pk::TypeId gTypeId{};


}

#endif //TYPEID_H
