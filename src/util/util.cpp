#include "util.hpp"


std::size_t pk::hash(const char *s) {
    unsigned long hash = 5381;
    int c;
    while ((c = *s++))
        hash = ((hash << 5) + hash) + c; // hash * 33 + c
    return hash;
}
