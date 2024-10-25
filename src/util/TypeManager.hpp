#pragma once
#include <cstddef>
#include <typeinfo>
#include <unordered_map>
#include "types.hpp"


namespace pk {

    class TypeManager {
    
    private:
        std::unordered_map<const char*, pk::component_t> typeMap{};

    public:

        template<typename T>
        void insert() {
            this->typeMap.emplace(typeid(T).name(), this->typeMap.size());
        }

        template<typename T>
        pk::component_t at() {
            return this->typeMap.at(typeid(T).name());
        }

        std::size_t size() const {
            return this->typeMap.size();
        }

    };

    inline pk::TypeManager gTypeManager{};

}