#pragma once

#include <cstddef>
#include <cstdint>
#include <unordered_set>

namespace life {
struct coord_t {
  int64_t x, y;
};

inline bool operator==(const coord_t& c1, const coord_t& c2) {
  return c1.x == c2.x && c1.y == c2.y;
}
}  // namespace life

template <>
struct std::hash<life::coord_t> {
  size_t operator()(const life::coord_t& coord) const noexcept;
};

namespace life {
class Simulation {
 public:
  Simulation();
  ~Simulation();

  void update();
  const std::unordered_set<coord_t>& livingCells();

  inline void addCell(coord_t cell) { m_LivingCells.insert(cell); };
  inline void removeCell(coord_t cell) { m_LivingCells.erase(cell); };

 private:
  size_t livingNeighbors(coord_t cell);

 private:
  std::unordered_set<coord_t> m_LivingCells;
};
}  // namespace life
