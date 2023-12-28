#include <raygui.h>
#include <raylib.h>

#include <functional>
#include <iostream>

#include "gui.hpp"
#include "props.hpp"
#include "simulation.hpp"

const int WIDTH = 800;
const int HEIGHT = 600;

props_t props;

void main_loop(std::function<void()> update_fn,
               std::function<void()> render_fn) {
  float acc_time = 0.0f;
  float delta_time = 1.0f / props.speed;

  while (!WindowShouldClose()) {
    acc_time += GetFrameTime();
    delta_time = 1.0 / props.speed;

    while (!WindowShouldClose() && acc_time >= delta_time) {
      update_fn();
      acc_time -= delta_time;
    }

    render_fn();
  }
}

int main() {
  gui_t gui(WIDTH, HEIGHT, "life", 60);
  simulation_t simulation;

  auto update_fn = [&]() {
    if (props.running) simulation.update();
  };
  auto render_fn = [&]() {
    gui.handle_camera_pan();
    gui.handle_camera_zoom();

    gui.render(props, [&](const Camera2D& camera) {
      for (const auto& [x, y] : simulation.get_living_cells()) {
        DrawRectangle(x * 10, -y * 10, 10, 10,
                      GetColor(GuiGetStyle(DEFAULT, TEXT_COLOR_NORMAL)));
      }
    });
  };

  main_loop(update_fn, render_fn);
}
