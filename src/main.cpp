#include <raylib.h>
#include <raymath.h>

#include <iostream>
#define RAYGUI_IMPLEMENTATION
#include <raygui.h>

#include "gui.hpp"
#include "simulation.hpp"

const int WIDTH = 800;
const int HEIGHT = 600;

int main() {
  gui_t gui(WIDTH, HEIGHT, "life");
  simulation_t simulation;

  SetTargetFPS(60);
  SetTraceLogLevel(LOG_NONE);

  float delta_time = 1.0f / 15.0f;
  float acc_time = 0.0f;

  while (!WindowShouldClose()) {
    acc_time += GetFrameTime();

    while (acc_time >= delta_time) {
      simulation.update();
      acc_time -= delta_time;
    }

    gui.handle_camera_pan();
    gui.handle_camera_zoom();

    BeginDrawing();
    ClearBackground(GetColor(GuiGetStyle(DEFAULT, BACKGROUND_COLOR)));

    BeginMode2D(gui.camera);
    for (const auto& [x, y] : simulation.get_living_cells()) {
      DrawRectangle(x * 10, -y * 10, 10, 10, BLACK);
    }
    EndMode2D();

    EndDrawing();
  }
}
