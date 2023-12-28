#pragma once

#include <cstddef>
#include <cstdint>
#include <unordered_set>

struct coord_t {
  int64_t x, y;
};

template <>
struct std::hash<coord_t> {
  size_t operator()(const coord_t& coord) const noexcept;
};

class simulation_t {
 public:
  simulation_t();
  ~simulation_t();

  void update();
  const std::unordered_set<coord_t>& get_living_cells();

 private:
  size_t living_neighbors(coord_t cell);

 private:
  std::unordered_set<coord_t> living_cells;
};
