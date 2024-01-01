#include "gui.hpp"

namespace life {
Gui::Gui(uint32_t width, uint32_t height, const char* title)
    : m_Window({width, height}, title) {
  m_Window.setFramerateLimit(60);
  m_Tgui.setWindow(m_Window);

  m_Camera = m_Window.getDefaultView();
  m_Camera.setViewport({0.0f, 0.0f, 1.0f, 1.0f});
  m_Camera.setCenter({0.0f, 0.0f});
}

void Gui::loop(float updateRate, std::function<void()> updateFn,
               std::function<void(sf::Event)> inputFn,
               std::function<void(sf::RenderWindow&)> renderFn) {
  sf::Clock clock;
  sf::Time accTime = sf::Time::Zero;
  sf::Time deltaTime = sf::seconds(1.0f / updateRate);
  while (m_Window.isOpen()) {
    sf::Event event;
    while (m_Window.pollEvent(event)) {
      if (event.type == sf::Event::Closed) m_Window.close();
      if (m_Tgui.handleEvent(event)) continue;
      if (updateCamera(event)) continue;
      inputFn(event);
    }

    while (accTime >= deltaTime) {
      accTime -= deltaTime;
      updateFn();
    }
    accTime += clock.restart();

    renderFn(m_Window);

    m_Window.setView(m_Window.getDefaultView());
    m_Tgui.draw();
    m_Window.setView(m_Camera);

    m_Window.display();
  }
}

bool Gui::updateCamera(sf::Event event) {
  switch (event.type) {
    case sf::Event::MouseWheelScrolled: {
      auto initialMousePos =
          m_Window.mapPixelToCoords(sf::Mouse::getPosition(m_Window));
      float factor = 1.0f - event.mouseWheelScroll.delta * 0.05f;
      m_Zoom *= factor;
      m_Camera.zoom(factor);
      m_Window.setView(m_Camera);
      auto zoomedMousePos =
          m_Window.mapPixelToCoords(sf::Mouse::getPosition(m_Window));
      m_Camera.move(initialMousePos - zoomedMousePos);
      m_Window.setView(m_Camera);
      return true;
    }

    case sf::Event::MouseMoved: {
      sf::Vector2f newMousePos =
          static_cast<sf::Vector2f>(sf::Mouse::getPosition(m_Window));
      if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) {
        m_Camera.move(m_Zoom * ((prevMousePos - newMousePos)));
        m_Window.setView(m_Camera);
      }
      prevMousePos = newMousePos;
      return true;
    }

    default:
      return false;
  }
}
}  // namespace life
