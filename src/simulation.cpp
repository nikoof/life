#include "simulation.hpp"

#include <algorithm>
#include <numeric>
#include <ranges>

namespace life {
Simulation::Simulation() {
  m_LivingCells = {
      {0, 0}, {-1, 0}, {1, 0}, {1, +1}, {0, +2},
  };
}
Simulation::~Simulation() {}

const std::unordered_set<Coord>& Simulation::livingCells() {
  return m_LivingCells;
}

size_t Simulation::livingNeighbors(Coord cell) {
  const auto& [x, y] = cell;
  auto neighbors = {
      Coord{x + 1, y + 1}, Coord{x + 1, y}, Coord{x + 1, y - 1},
      Coord{x - 1, y + 1}, Coord{x - 1, y}, Coord{x - 1, y - 1},
      Coord{x, y + 1},     Coord{x, y - 1},
  };

  return std::ranges::distance(
      neighbors | std::views::filter([this](const Coord& neighbor) {
        return m_LivingCells.contains(neighbor);
      }));
}

void Simulation::update() {
  std::unordered_set<Coord> willLive = std::transform_reduce(
      m_LivingCells.cbegin(), m_LivingCells.cend(), std::unordered_set<Coord>{},
      [](std::unordered_set<Coord> acc, std::unordered_set<Coord> s) {
        acc.insert(s.begin(), s.end());
        return acc;
      },
      [this](const Coord& cell) {
        const auto& [x, y] = cell;
        std::unordered_set<Coord> newborns;
        for (int64_t dx = -1; dx <= 1; ++dx) {
          for (int64_t dy = -1; dy <= 1; ++dy) {
            Coord neighbor = {x + dx, y + dy};
            if (livingNeighbors(neighbor) == 3) {
              newborns.insert(neighbor);
            }
          }
        }

        return newborns;
      });

  auto willDieView =
      m_LivingCells | std::views::filter([this](const Coord& cell) {
        size_t living_neighbor_count = livingNeighbors(cell);
        return living_neighbor_count < 2 || living_neighbor_count > 3;
      });

  // TODO: switch to using std::ranges::to<std::unordered_set> when it becomes
  // available in a compiler
  std::unordered_set<Coord> willDie(std::begin(willDieView),
                                    std::end(willDieView));

  for (const Coord& deadCell : willDie) {
    m_LivingCells.erase(deadCell);
  }

  m_LivingCells.insert(willLive.begin(), willLive.end());
}
}  // namespace life
