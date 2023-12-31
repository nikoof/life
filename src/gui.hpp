#pragma once

#include <SFML/Window.hpp>
#include <TGUI/Backend/SFML-Graphics.hpp>
#include <TGUI/TGUI.hpp>
#include <cstddef>
#include <cstdint>
#include <functional>

namespace life {
class Gui {
 public:
  Gui(uint32_t width, uint32_t height, const char* title);
  ~Gui() = default;

  void loop(std::function<void()> updateFn,
            std::function<void(sf::Event)> inputFn,
            std::function<void(sf::RenderWindow&)> renderFn);

 private:
  tgui::Gui tgui;
  sf::RenderWindow window;
};
}  // namespace life
