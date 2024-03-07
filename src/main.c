#include "raylib.h"
#include "constants.h"
#include "sand.h"
#include <stdio.h>
#include <stdlib.h>
// TODO
// Color random
// To add: LAVA, AWA, EXPLOSIVO, Gusanito

void getHoveredSand(Sand sandArray[ROWS][COLS], Color color, int tick) {
  Vector2 mousePos = GetMousePosition();
  int x = (int) mousePos.x / SIZE;
  int y = (int) mousePos.y / SIZE;
  if (x > ROWS || x < 0) return;
  if (y > COLS || y < 0) return;
  if (IsMouseButtonDown(MOUSE_BUTTON_LEFT) && tick > MAX_TICK) {
    sandArray[x][y].isAir = false;
    sandArray[x][y].color = color;
    printf("r:%d, g:%d, b:%d", color.r, color.g, color.b);
  }
}

void drawSand(Sand sandArray[ROWS][COLS]) {
  for (int x = 0; x < ROWS; x++) {
    for (int y = 0; y < COLS; y++) {
      sandArray[x][y].hasChanged = false;
      if (!sandArray[x][y].isAir) {
        DrawRectangle(sandArray[x][y].rect.x, sandArray[x][y].rect.y, sandArray[x][y].rect.width, sandArray[x][y].rect.height, sandArray[x][y].color);
      }
    }
  }
}

void updateSand(Sand sandArray[ROWS][COLS], int tick) {
  if (tick < MAX_TICK) return;

  for (int x = 1; x < ROWS - 1; x++) {
    for (int y = 1; y < COLS - 1; y++){

      if (!sandArray[x][y].isAir && !sandArray[x][y].hasChanged) {
        // TOP
        if (sandArray[x][y + 1].isAir) {
          // Flagged
          sandArray[x][y].hasChanged = true;
          sandArray[x][y + 1].hasChanged = true;

          sandArray[x][y].isAir = true;
          sandArray[x][y + 1].isAir = false;
          sandArray[x][y + 1].color = sandArray[x][y].color;

        } else if (sandArray[x + 1][y +1].isAir) {
          // RIGHT

          sandArray[x][y].hasChanged = true;
          sandArray[x + 1][y + 1].hasChanged = true;

          sandArray[x][y].isAir = true;
          sandArray[x + 1][y + 1].isAir = false;
          sandArray[x + 1][y + 1].color = sandArray[x][y].color;
        } else if (sandArray[x - 1][y + 1].isAir) {
          // LEFT
          sandArray[x][y].hasChanged = true;
          sandArray[x - 1][y + 1].hasChanged = true;

          sandArray[x][y].isAir = true;
          sandArray[x - 1][y + 1].isAir = false;
          sandArray[x - 1][y + 1].color = sandArray[x][y].color;
        }
      }
    }
  }
}

int main(void)
{
  int tick = 0;
  InitWindow(WIDTH, HEIGHT, "Sand simulator");
  SetTargetFPS(FPS);
  printf("TOTAL ROWS = %d\n", ROWS);
  Sand sandArray[ROWS][COLS];
  for (int x = 0; x < ROWS; x++) {
    for (int y = 0; y < COLS; y++) {
      Rectangle rect = {x * SIZE, y * SIZE, SIZE, SIZE};
      Color color = {180, 100, 0, 255};
      Sand sand = {false ,true, rect, color};
      sandArray[x][y] = sand;  
    }
  }
  Color color;
  color.r = 255;
  color.g = 255;
  color.b = 255;
  color.a = 255;
  while (!WindowShouldClose()) {
    if (tick > MAX_TICK) tick = 0;
    tick++;
    
    if (IsKeyPressed(KEY_V)) {
      printf("KEY PRESSED\n");
      int r = rand() % 256;
      int g = rand() % 256;
      int b = rand() % 256;
      color.r = r;
      color.g = g;
      color.b = b;
      color.a = 255;
    }
    getHoveredSand(sandArray, color, tick);
    BeginDrawing();
    updateSand(sandArray, tick);
    drawSand(sandArray);
    ClearBackground(BLACK);
    EndDrawing();
  }

  CloseWindow();
  return 0;
}
