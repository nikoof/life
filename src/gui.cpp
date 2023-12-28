#include "gui.hpp"

#include <raylib.h>
#include <raymath.h>

const float ZOOM_SPEED = 0.05f;

gui_t::gui_t(int screenWidth, int screenHeight, const char* windowTitle) {
  InitWindow(screenWidth, screenHeight, windowTitle);
  SetTargetFPS(60);
  SetTraceLogLevel(LOG_NONE);

  camera.target = camera.offset =
      Vector2{screenWidth / 2.0f, screenHeight / 2.0f};

  camera.zoom = 1.0f;
  camera.rotation = 0.0f;
}

gui_t::~gui_t() { CloseWindow(); }

void gui_t::render(std::function<void()> render_world_fn,
                   std::function<void(const Camera2D&)> render_camera_fn) {
  BeginDrawing();
  render_world_fn();

  BeginMode2D(camera);
  render_camera_fn(camera);
  EndMode2D();

  EndDrawing();
}

void gui_t::handle_camera_pan() {
  static Vector2 prevMousePosition = {0, 0};

  if (Vector2Equals(prevMousePosition, Vector2Zero())) {
    prevMousePosition = GetMousePosition();
  }

  Vector2 currentMousePosition = GetMousePosition();
  Vector2 mouseDelta = Vector2Subtract(prevMousePosition, currentMousePosition);

  if (IsMouseButtonDown(0))
    camera.target =
        GetScreenToWorld2D(Vector2Add(camera.offset, mouseDelta), camera);

  prevMousePosition = currentMousePosition;
}

void gui_t::handle_camera_zoom() {
  float delta = GetMouseWheelMove();
  camera.zoom = Clamp(camera.zoom + delta * ZOOM_SPEED, 0.01f, 3.0f);
}
