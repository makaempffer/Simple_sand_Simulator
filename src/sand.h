#ifndef SAND_H
#define SAND_H
#include "raylib.h"
#include <stdbool.h>
typedef struct {
  bool hasChanged;
  bool isAir;
  Rectangle rect;
  Color color;
} Sand;

#endif
