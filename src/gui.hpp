#pragma once

#include <SFML/Window.hpp>
#include <TGUI/Backend/SFML-Graphics.hpp>
#include <TGUI/Core.hpp>
#include <TGUI/Widgets/Label.hpp>
#include <TGUI/Widgets/Slider.hpp>
#include <cstddef>
#include <cstdint>
#include <functional>

#include "util.hpp"

namespace life {
class Gui {
 public:
  Gui(uint32_t width, uint32_t height, const char* title);
  ~Gui() = default;

  void loop(const Props& props, std::function<void()> updateFn,
            std::function<bool(sf::RenderWindow&, sf::Event)> inputFn,
            std::function<void(sf::RenderWindow&)> renderFn);

  inline tgui::Slider::Ptr speedSlider() { return m_SpeedSlider; }

 private:
  bool updateCamera(sf::Event event);

 private:
  sf::RenderWindow m_Window;
  sf::View m_Camera;

  tgui::Gui m_Tgui;
  tgui::Slider::Ptr m_SpeedSlider;
  tgui::Label::Ptr m_HelpText;

  sf::Vector2f prevMousePos;
  float m_Zoom = 1.0f;
};
}  // namespace life
