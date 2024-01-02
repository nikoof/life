#pragma once

#include <cstddef>
#include <cstdint>
#include <unordered_set>

namespace life {
struct Props {
  bool running = true;
  float speed = 15.0f;
};

struct Coord {
  int64_t x, y;
};

inline bool operator==(const Coord& c1, const Coord& c2) {
  return c1.x == c2.x && c1.y == c2.y;
}
}  // namespace life

template <>
struct std::hash<life::Coord> {
  size_t operator()(const life::Coord& coord) const noexcept;
};
