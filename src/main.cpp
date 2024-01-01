#include <SFML/Window.hpp>
#include <TGUI/Backend/SFML-Graphics.hpp>
#include <cstdint>
#include <functional>

#include "gui.hpp"
#include "props.hpp"
#include "simulation.hpp"

const uint32_t WIDTH = 800;
const uint32_t HEIGHT = 600;

int main() {
  life::Simulation simulation;

  const auto inputFn = [&](sf::Event event) {};
  const auto updateFn = [&]() { simulation.update(); };
  const auto renderFn = [&](sf::RenderWindow& window) {
    window.clear(sf::Color::Black);

    for (const auto& [x, y] : simulation.livingCells()) {
      sf::RectangleShape rect;
      rect.setPosition(sf::Vector2f(10.0f * x, 10.0f * -y));
      rect.setSize(sf::Vector2f(10.0f, 10.0f));
      rect.setFillColor(sf::Color::White);

      window.draw(rect);
    }
  };

  life::Gui gui(WIDTH, HEIGHT, "life");
  gui.loop(15.0f, updateFn, inputFn, renderFn);
}
