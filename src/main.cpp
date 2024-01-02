#include <SFML/Window.hpp>
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

  const auto inputFn = [&](sf::Window& window, sf::Event event) -> bool {
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

      case sf::Event::MouseMoved: {
        if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) {
          std::cout << event.mouseMove.x << " " << event.mouseMove.y
                    << std::endl;
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
      rect.setPosition(sf::Vector2f(10.0f * x, 10.0f * y));
      rect.setSize(sf::Vector2f(10.0f, 10.0f));
      rect.setFillColor(sf::Color::White);

      window.draw(rect);
    }
  };

  life::Gui gui(WIDTH, HEIGHT, "life");
  gui.loop(15.0f, updateFn, inputFn, renderFn);
}
