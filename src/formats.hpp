#include <expected>
#include <istream>
#include <unordered_set>

#include "util.hpp"

namespace life {
enum class Format {
  Plaintext,
};

enum class ParseError {
  MissingHeader,
};

template <Format F>
std::expected<std::unordered_set<Coord>, ParseError> parse(
    std::istream inputStream);
}  // namespace life
