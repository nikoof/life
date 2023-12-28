#pragma once

#include <raylib.h>

#include <functional>
#include <string>
#include <vector>

#include "props.hpp"

struct button_t {
  Rectangle rect;
  std::string label;
};

struct slider_t {
  Rectangle rect;
  std::string label_left, label_right;
  float min, max;
};

class gui_t {
 public:
  gui_t(int width, int height, const char* window_title, int framerate);
  ~gui_t();

  void handle_camera_pan();
  void handle_camera_zoom();

  void render(props_t& props, std::function<void(const Camera2D&)> render_fn);

 private:
  void render_gui(props_t& props);

 private:
  std::vector<std::string> help_text;
  Camera2D camera = {{0}};
  button_t start_button;
  slider_t speed_slider;
};
