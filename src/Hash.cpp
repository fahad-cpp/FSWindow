#include "Hash.h"
#include "Colour.h"
template <typename T>
inline void hashCombine(std::size_t &seed, const T &value) {
    seed ^= (std::hash<T>()(value) + 0x9e3779b9 + (seed << 6) + (seed >> 2));
}

std::size_t std::hash<FS::Vector>::operator()(const FS::Vector &vec) const {
    std::size_t seed = 0;
    hashCombine(seed, vec.x);
    hashCombine(seed, vec.y);
    hashCombine(seed, vec.z);
    return seed;
}

std::size_t std::hash<FS::Colour>::operator()(const FS::Colour &color) const {
    return std::size_t(FS::rgbtoHex(color));
}
