#pragma once

#include <raylib.h>

#include <functional>

class gui_t {
 public:
  gui_t(int screenWidth, int screenHeight, const char* windowTitle);
  ~gui_t();

  void handle_camera_pan();
  void handle_camera_zoom();

  void render(std::function<void()> render_world_fn,
              std::function<void(const Camera2D&)> render_camera_fn);

 private:
  Camera2D camera = {{0}};
};
