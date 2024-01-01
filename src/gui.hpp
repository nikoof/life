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

  void loop(float updateRate, std::function<void()> updateFn,
            std::function<void(sf::Event)> inputFn,
            std::function<void(sf::RenderWindow&)> renderFn);

 private:
  bool updateCamera(sf::Event event);

 private:
  tgui::Gui m_Tgui;
  sf::RenderWindow m_Window;
  sf::View m_Camera;

  sf::Vector2f prevMousePos;
  float m_Zoom = 1.0f;
};
}  // namespace life
