#pragma once

#include <raylib.h>

class gui_t {
public:
  gui_t(int screenWidth, int screenHeight, const char *windowTitle);
  ~gui_t();

  void handle_camera_pan();
  void handle_camera_zoom();

public:
  Camera2D camera = {{0}};
};
