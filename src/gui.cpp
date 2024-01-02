#include "gui.hpp"

static const char* HELP_TEXT =
    "Press [SPC] to start/stop the simulation.\n"
    "Zoom the camera with the scroll wheel.\n"
    "Pan it with middle-click.\n"
    "Paint cells with left-click.\n"
    "Erase them with right-click.\n";

namespace life {
Gui::Gui(uint32_t width, uint32_t height, const char* title)
    : m_Window({width, height}, title) {
  m_Window.setFramerateLimit(60);
  m_Tgui.setWindow(m_Window);

  m_Camera = m_Window.getDefaultView();
  m_Camera.setViewport({0.0f, 0.0f, 1.0f, 1.0f});
  m_Camera.setCenter({0.0f, 0.0f});
  m_Camera.zoom(0.1f);
  m_Zoom *= 0.1f;

  m_SpeedSlider = tgui::Slider::create();
  m_SpeedSlider->setOrigin(0.5f, 0.5f);
  m_SpeedSlider->setPosition("50%", "95%");
  m_SpeedSlider->setWidth("70%");
  m_Tgui.add(m_SpeedSlider, "speedSlider");

  m_HelpText = tgui::Label::create(HELP_TEXT);
  m_HelpText->setTextSize(16);
  m_HelpText->setAutoSize(true);
  m_HelpText->setHorizontalAlignment(tgui::Label::HorizontalAlignment::Right);
  m_HelpText->setOrigin(1.0f, 0.0f);
  m_HelpText->setPosition("98%", "2%");
  m_Tgui.add(m_HelpText, "helpText");
}

void Gui::loop(const Props& props, std::function<void()> updateFn,
               std::function<bool(sf::RenderWindow&, sf::Event)> inputFn,
               std::function<void(sf::RenderWindow&)> renderFn) {
  sf::Clock clock;
  sf::Time accTime = sf::Time::Zero;
  sf::Time deltaTime = sf::seconds(1.0f / props.speed);
  while (m_Window.isOpen()) {
    sf::Event event;
    while (m_Window.pollEvent(event)) {
      if (m_Tgui.handleEvent(event)) continue;
      if (updateCamera(event)) continue;
      if (inputFn(m_Window, event)) continue;
    }

    deltaTime = sf::seconds(1.0f / props.speed);
    while (m_Window.isOpen() && accTime >= deltaTime) {
      accTime -= deltaTime;
      updateFn();
    }
    accTime += clock.restart();

    if (props.running) {
      m_Tgui.remove(m_HelpText);
    } else {
      m_Tgui.add(m_HelpText);
    }

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
      if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Middle)) {
        m_Camera.move(m_Zoom * (prevMousePos - newMousePos));
        m_Window.setView(m_Camera);
        prevMousePos = newMousePos;
        return true;
      }
      prevMousePos = newMousePos;
      return false;
    }

    default:
      return false;
  }
}
}  // namespace life
