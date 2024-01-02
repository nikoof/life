#include "util.hpp"

size_t std::hash<life::Coord>::operator()(
    const life::Coord& coord) const noexcept {
  size_t h1 = std::hash<int64_t>{}(coord.x);
  size_t h2 = std::hash<int64_t>{}(coord.y);
  return h1 ^ (h2 << 1);
}
