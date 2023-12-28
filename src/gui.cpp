#include "gui.hpp"

#include <ranges>

#define RAYGUI_IMPLEMENTATION
#include <raygui.h>
#include <raylib.h>
#include <raymath.h>

#include "raygui_style_dark.h"

const float ZOOM_SPEED = 0.05f;

gui_t::gui_t(int width, int height, const char* window_title, int framerate) {
  InitWindow(width, height, window_title);
  SetWindowState(FLAG_WINDOW_RESIZABLE);

  SetTargetFPS(framerate);
  SetTraceLogLevel(LOG_NONE);

  GuiLoadStyleDark();

  float widthf = static_cast<float>(GetScreenWidth());
  float heightf = static_cast<float>(GetScreenHeight());

  camera.target = {0.0f, 0.0f};
  camera.offset = {widthf / 2.0f, heightf / 2.0f};
  camera.zoom = 1.0f;
  camera.rotation = 0.0f;

  start_button.rect = {10.0f, 10.0f, 70.0f, 25.0f};
  start_button.label = GuiIconText(ICON_PLAYER_PAUSE, "Stop");

  speed_slider.rect = {50.0f, heightf - 30.0f, widthf - 200.0f, 20.0f};
  speed_slider.label_left = "Slower";
  speed_slider.label_right = "Faster";
  speed_slider.min = 15.0f;
  speed_slider.max = 60.0f;

  help_text = {
      "Press [SPC] to start/stop the simulation.",
      "Use left-click to pan.",
      "Use the scroll wheel to zoom.",
  };
}

gui_t::~gui_t() { CloseWindow(); }

void gui_t::render_gui(props_t& props) {
  float widthf = static_cast<float>(GetScreenWidth());
  float heightf = static_cast<float>(GetScreenHeight());

  for (size_t i = 0; i < help_text.size(); ++i) {
    int length = MeasureText(help_text[i].c_str(), 20);
    DrawText(help_text[i].c_str(), widthf - (10.0f + length), 10.0f + i * 20.0f,
             20, GetColor(GuiGetStyle(DEFAULT, TEXT_COLOR_DISABLED)));
  }

  start_button.rect = {10.0f, 10.0f, 70.0f, 25.0f};
  speed_slider.rect = {50.0f, heightf - 30.0f, widthf - 100.0f, 20.0f};

  int button_pressed = GuiButton(start_button.rect, start_button.label.c_str());
  int slider_focused =
      GuiSlider(speed_slider.rect, speed_slider.label_left.c_str(),
                speed_slider.label_right.c_str(), &props.speed,
                speed_slider.min, speed_slider.max);

  if (button_pressed) {
    props.running = !props.running;

    if (props.running) {
      start_button.label = GuiIconText(ICON_PLAYER_PAUSE, "Stop");
    } else {
      start_button.label = GuiIconText(ICON_PLAYER_PLAY, "Start");
    }
  }

  if (button_pressed || slider_focused) {
    GuiSetState(STATE_FOCUSED);
  } else {
    GuiSetState(STATE_NORMAL);
  }
}

void gui_t::render(props_t& props,
                   std::function<void(const Camera2D&)> render_fn) {
  BeginDrawing();
  ClearBackground(GetColor((float)GuiGetStyle(DEFAULT, BACKGROUND_COLOR)));

  BeginMode2D(camera);
  render_fn(camera);
  EndMode2D();

  render_gui(props);
  EndDrawing();
}

void gui_t::handle_camera_pan() {
  static Vector2 prevMousePosition = {0, 0};

  if (Vector2Equals(prevMousePosition, Vector2Zero())) {
    prevMousePosition = GetMousePosition();
  }

  Vector2 currentMousePosition = GetMousePosition();
  Vector2 mouseDelta = Vector2Subtract(prevMousePosition, currentMousePosition);

  if (IsMouseButtonDown(0) && GuiGetState() != STATE_FOCUSED)
    camera.target =
        GetScreenToWorld2D(Vector2Add(camera.offset, mouseDelta), camera);

  prevMousePosition = currentMousePosition;
}

void gui_t::handle_camera_zoom() {
  if (GuiGetState() == STATE_FOCUSED) {
    return;
  }

  float delta = GetMouseWheelMove();
  camera.zoom = Clamp(camera.zoom + delta * ZOOM_SPEED, 0.01f, 3.0f);
}
