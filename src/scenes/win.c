#include "win.h"

#include "raylib.h"
#include "raymath.h"

#include "../state/state.h"
#include "../controller/controller.h"
#include "../player/player.h"
#include "../guys/guys.h"
#include "../obstacles/obstacles.h"

void winScene(State *state, Controller controller)
{
  movePlayer(&state->player, controller, *state);
  if (IsKeyPressed(KEY_ENTER))
  {
    resetPlayer(&state->player);
    state->guys.guyInitial += GUY_INCREMENT;
    resetGuys(&state->guys);
    resetObstacles(&state->obstacles);
    state->scene = Play;
  }
}