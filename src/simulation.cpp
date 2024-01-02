#include "simulation.hpp"

#include <algorithm>
#include <numeric>
#include <ranges>

size_t std::hash<life::coord_t>::operator()(
    const life::coord_t& coord) const noexcept {
  size_t h1 = std::hash<int64_t>{}(coord.x);
  size_t h2 = std::hash<int64_t>{}(coord.y);
  return h1 ^ (h2 << 1);
}

namespace life {
Simulation::Simulation() {
  m_LivingCells = {
      {0, 0}, {-1, 0}, {1, 0}, {1, +1}, {0, +2},
  };
}
Simulation::~Simulation() {}

const std::unordered_set<coord_t>& Simulation::livingCells() {
  return m_LivingCells;
}

size_t Simulation::livingNeighbors(coord_t cell) {
  const auto& [x, y] = cell;
  auto neighbors = {
      coord_t{x + 1, y + 1}, coord_t{x + 1, y}, coord_t{x + 1, y - 1},
      coord_t{x - 1, y + 1}, coord_t{x - 1, y}, coord_t{x - 1, y - 1},
      coord_t{x, y + 1},     coord_t{x, y - 1},
  };

  return std::ranges::distance(
      neighbors | std::views::filter([this](const coord_t& neighbor) {
        return m_LivingCells.contains(neighbor);
      }));
}

void Simulation::update() {
  std::unordered_set<coord_t> willLive = std::transform_reduce(
      m_LivingCells.cbegin(), m_LivingCells.cend(),
      std::unordered_set<coord_t>{},
      [](std::unordered_set<coord_t> acc, std::unordered_set<coord_t> s) {
        acc.insert(s.begin(), s.end());
        return acc;
      },
      [this](const coord_t& cell) {
        const auto& [x, y] = cell;
        std::unordered_set<coord_t> newborns;
        for (int64_t dx = -1; dx <= 1; ++dx) {
          for (int64_t dy = -1; dy <= 1; ++dy) {
            coord_t neighbor = {x + dx, y + dy};
            if (livingNeighbors(neighbor) == 3) {
              newborns.insert(neighbor);
            }
          }
        }

        return newborns;
      });

  auto willDieView =
      m_LivingCells | std::views::filter([this](const coord_t& cell) {
        size_t living_neighbor_count = livingNeighbors(cell);
        return living_neighbor_count < 2 || living_neighbor_count > 3;
      });

  // TODO: switch to using std::ranges::to<std::unordered_set> when it becomes
  // available in a compiler
  std::unordered_set<coord_t> willDie(std::begin(willDieView),
                                      std::end(willDieView));

  for (const coord_t& deadCell : willDie) {
    m_LivingCells.erase(deadCell);
  }

  m_LivingCells.insert(willLive.begin(), willLive.end());
}
}  // namespace life
