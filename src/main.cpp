#include <functional>

#define RAYGUI_IMPLEMENTATION

#include <raygui.h>
#include <raylib.h>
#include <raymath.h>

#include "gui.hpp"
#include "simulation.hpp"

const int WIDTH = 800;
const int HEIGHT = 600;

void main_loop(size_t update_rate, std::function<void()> update_fn,
               std::function<void()> render_fn) {
  float acc_time = 1.0f;
  float delta_time = 1.0f / static_cast<float>(update_rate);

  while (!WindowShouldClose()) {
    acc_time += GetFrameTime();

    while (acc_time >= delta_time) {
      update_fn();
      acc_time -= delta_time;
    }

    render_fn();
  }
}

int main() {
  gui_t gui(WIDTH, HEIGHT, "life");
  simulation_t simulation;

  auto update_fn = [&]() { simulation.update(); };
  auto render_fn = [&]() {
    gui.handle_camera_pan();
    gui.handle_camera_zoom();

    gui.render(
        [&]() {
          ClearBackground(RAYWHITE);
          ClearBackground(RAYWHITE);
          ClearBackground(RAYWHITE);
          ClearBackground(RAYWHITE);
        },
        [&](const Camera2D& camera) {
          for (const auto& [x, y] : simulation.get_living_cells()) {
            DrawRectangle(x * 10, -y * 10, 10, 10, BLACK);
          }
        });
  };

  main_loop(15, update_fn, render_fn);
}
