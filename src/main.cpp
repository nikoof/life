#include <raylib.h>
#include <raymath.h>

#include "gui.h"

const int WIDTH = 800;
const int HEIGHT = 600;

int main() {
  Gui gui(WIDTH, HEIGHT, "life");

  while (!WindowShouldClose()) {
    gui.PanCamera();
    gui.ZoomCamera();

    BeginDrawing();
    ClearBackground(RAYWHITE);

    BeginMode2D(gui.camera);
    DrawRectangle(400 - 100, 300 - 100, 200, 200, BLACK);
    EndMode2D();

    EndDrawing();
  }
}
