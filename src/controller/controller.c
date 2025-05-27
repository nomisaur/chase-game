#include "controller.h"

#include "raylib.h"
#include "raymath.h"

Controller controller;

Controller initController()
{
  Controller controller;
  controller.up = KEY_W;
  controller.down = KEY_S;
  controller.left = KEY_A;
  controller.right = KEY_D;
  controller.boost = KEY_SPACE;
  controller.pause = KEY_ESCAPE;
  controller.select = KEY_ENTER;
  return controller;
}