#include "gui.hpp"

namespace life {
Gui::Gui(uint32_t width, uint32_t height, const char* title)
    : window({width, height}, title) {
  window.setFramerateLimit(15);
  tgui.setWindow(window);
}

void Gui::loop(std::function<void()> updateFn,
               std::function<void(sf::Event)> inputFn,
               std::function<void(sf::RenderWindow&)> renderFn) {
  while (window.isOpen()) {
    updateFn();

    sf::Event event;
    while (window.pollEvent(event)) {
      if (tgui.handleEvent(event)) continue;

      if (event.type == sf::Event::Closed) {
        window.close();
      }

      inputFn(event);
    }

    renderFn(window);
    tgui.draw();
    window.display();
  }
}
}  // namespace life
