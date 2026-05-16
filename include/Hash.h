#ifndef HASH_H
#define HASH_H

#include <algorithm>
#include "Colour.h"
template<typename T>
inline void hashCombine(std::size_t& seed, const T& value);
template<>
struct std::hash<FS::Vector> {
	std::size_t operator()(const FS::Vector& vec) const;
};
template<>
struct std::hash<FS::Colour> {
	std::size_t operator()(const FS::Colour& color)const;
};
#endif
