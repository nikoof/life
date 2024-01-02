#pragma once

#include <cstddef>
#include <cstdint>
#include <unordered_set>

#include "util.hpp"

namespace life {
class Simulation {
 public:
  Simulation();
  ~Simulation();

  void update();
  const std::unordered_set<Coord>& livingCells();

  inline void addCell(Coord cell) { m_LivingCells.insert(cell); };
  inline void removeCell(Coord cell) { m_LivingCells.erase(cell); };

 private:
  size_t livingNeighbors(Coord cell);

 private:
  std::unordered_set<Coord> m_LivingCells;
};
}  // namespace life
