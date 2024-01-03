#include "formats.hpp"

namespace life {
template <>
std::expected<std::unordered_set<Coord>, ParseError> parse<Format::Plaintext>(
    std::istream inputStream) {
  std::unordered_set<Coord> livingCells;
  return livingCells;
}
}  // namespace life
