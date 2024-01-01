#pragma once

#include <cstddef>
#include <cstdint>
#include <unordered_set>

namespace life {
struct coord_t {
  int64_t x, y;
};
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

 private:
  size_t livingNeighbors(coord_t cell);

 private:
  std::unordered_set<coord_t> m_LivingCells;
};
}  // namespace life
