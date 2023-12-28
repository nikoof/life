#include "simulation.hpp"

#include <algorithm>
#include <numeric>
#include <ranges>

size_t std::hash<coord_t>::operator()(const coord_t& coord) const noexcept {
  size_t h1 = std::hash<int64_t>{}(coord.x);
  size_t h2 = std::hash<int64_t>{}(coord.y);
  return h1 ^ (h2 << 1);
}

bool operator==(const coord_t& c1, const coord_t& c2) {
  return c1.x == c2.x && c1.y == c2.y;
}

simulation_t::simulation_t() {
  living_cells = {
      {0, 0}, {-1, 0}, {1, 0}, {1, +1}, {0, +2},
  };
}
simulation_t::~simulation_t() {}

const std::unordered_set<coord_t>& simulation_t::get_living_cells() {
  return living_cells;
}

size_t simulation_t::living_neighbors(coord_t cell) {
  const auto& [x, y] = cell;
  auto neighbors = {
      coord_t{x + 1, y + 1}, coord_t{x + 1, y}, coord_t{x + 1, y - 1},
      coord_t{x - 1, y + 1}, coord_t{x - 1, y}, coord_t{x - 1, y - 1},
      coord_t{x, y + 1},     coord_t{x, y - 1},
  };

  return std::ranges::distance(
      neighbors | std::views::filter([this](const coord_t& neighbor) {
        return living_cells.contains(neighbor);
      }));
}

void simulation_t::update() {
  std::unordered_set<coord_t> will_live = std::transform_reduce(
      living_cells.cbegin(), living_cells.cend(), std::unordered_set<coord_t>{},
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
            if (living_neighbors(neighbor) == 3) {
              newborns.insert(neighbor);
            }
          }
        }

        return newborns;
      });

  auto will_die_view =
      living_cells | std::views::filter([this](const coord_t& cell) {
        size_t living_neighbor_count = living_neighbors(cell);
        return living_neighbor_count < 2 || living_neighbor_count > 3;
      });

  // TODO: switch to using std::ranges::to<std::unordered_set> when it becomes
  // available in a compiler
  std::unordered_set<coord_t> will_die(std::begin(will_die_view),
                                       std::end(will_die_view));

  for (const coord_t& dead_cell : will_die) {
    living_cells.erase(dead_cell);
  }

  living_cells.insert(will_live.begin(), will_live.end());
}
