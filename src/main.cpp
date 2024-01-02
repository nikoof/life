#include <SFML/Window.hpp>
#include <cmath>
#include <cstdint>
#include <functional>

#include "gui.hpp"
#include "props.hpp"
#include "simulation.hpp"

const uint32_t WIDTH = 800;
const uint32_t HEIGHT = 600;

int main() {
  life::Props props;
  life::Simulation simulation;
  life::Gui gui(WIDTH, HEIGHT, "life");

  gui.speedSlider()->setMinimum(10.0f);
  gui.speedSlider()->setMaximum(60.0f);
  gui.speedSlider()->setValue(props.speed);
  gui.speedSlider()->onValueChange(
      [&](float sliderValue) { props.speed = sliderValue; });

  const auto inputFn = [&](sf::RenderWindow& window, sf::Event event) -> bool {
    switch (event.type) {
      case sf::Event::Closed:
        window.close();
        return true;

      case sf::Event::KeyPressed:
        switch (event.key.code) {
          case sf::Keyboard::Space:
            props.running = !props.running;
            break;

          default:
            break;
        }
        return true;

      case sf::Event::MouseButtonPressed: {
        sf::Vector2f coords =
            window.mapPixelToCoords(sf::Mouse::getPosition(window));
        life::coord_t cell = {static_cast<int32_t>(std::floor(coords.x)),
                              static_cast<int32_t>(std::floor(coords.y))};

        switch (event.mouseButton.button) {
          case sf::Mouse::Button::Left:
            simulation.addCell(cell);
            return true;

          case sf::Mouse::Button::Right:
            simulation.removeCell(cell);
            return true;

          default:
            return false;
        }
      }

      case sf::Event::MouseMoved: {
        sf::Vector2f coords =
            window.mapPixelToCoords(sf::Mouse::getPosition(window));
        life::coord_t cell = {static_cast<int32_t>(std::floor(coords.x)),
                              static_cast<int32_t>(std::floor(coords.y))};
        if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) {
          simulation.addCell(cell);
          return true;
        }
        if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Right)) {
          simulation.removeCell(cell);
          return true;
        }
        return false;
      }

      default:
        return false;
    }
  };

  const auto updateFn = [&]() {
    if (props.running) simulation.update();
  };

  const auto renderFn = [&](sf::RenderWindow& window) {
    window.clear(sf::Color::Black);

    for (const auto& [x, y] : simulation.livingCells()) {
      sf::RectangleShape rect;
      rect.setPosition(sf::Vector2f(x, y));
      rect.setSize(sf::Vector2f(1.0f, 1.0f));
      rect.setFillColor(sf::Color::White);

      window.draw(rect);
    }
  };

  gui.loop(props, updateFn, inputFn, renderFn);
}
