#include <SFML/Window.hpp>
#include <functional>
#include <iostream>

#include "props.hpp"
#include "simulation.hpp"

const int WIDTH = 800;
const int HEIGHT = 600;

int main() {
  simulation_t simulation;
  props_t props;

  sf::Window window(sf::VideoMode(WIDTH, HEIGHT), "life");
  while (window.isOpen()) {
    sf::Event event;
    while (window.pollEvent(event)) {
      if (event.type == sf::Event::Closed) {
        window.close();
      }
    }
  }

  auto update_fn = [&]() {
    if (props.running) simulation.update();
  };
  auto render_fn = [&]() {};
}
