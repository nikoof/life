#include "gui.h"

#include <raylib.h>
#include <raymath.h>

const float ZOOM_SPEED = 0.05f;

Gui::Gui(int screenWidth, int screenHeight, const char *windowTitle) {
  InitWindow(screenWidth, screenHeight, windowTitle);
  SetTargetFPS(60);

  camera.target = camera.offset =
      Vector2{screenWidth / 2.0f, screenHeight / 2.0f};

  camera.zoom = 1.0f;
  camera.rotation = 0.0f;
}

Gui::~Gui() { CloseWindow(); }

void Gui::PanCamera() {
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

void Gui::ZoomCamera() {
  float delta = GetMouseWheelMove();
  camera.zoom = Clamp(camera.zoom + delta * ZOOM_SPEED, 0.01f, 3.0f);
}
