#pragma once

#include <raylib.h>

class Gui {
public:
  Gui(int screenWidth, int screenHeight, const char *windowTitle);
  ~Gui();

  void PanCamera();
  void ZoomCamera();

public:
  Camera2D camera = {{0}};
};
