#include "state.h"

#include "raylib.h"
#include "raymath.h"

#include "../config.h"
#include "../utils/utils.h"
#include "../player/player.h"
#include "../guys/guys.h"
#include "../obstacles/obstacles.h"

State initState()
{
  State state;
  state.scene = Play;
  state.paused = false;
  state.player = initPlayer();
  state.guys = initGuys();
  state.obstacles = initObstacles();
  return state;
}

void handlePlayerGuyCollision(Guy *guy, State *state)
{
  Player *player = &state->player;
  Guys *guys = &state->guys;
  if (checkBodyCollision(player->body, guy->body))
  {
    guys->guysAlive -= 1;
    guy->alive = false;
    player->stamina.total += STAMINA_INCREMENT;
    player->stamina.amount = player->stamina.total;
    int newSpeed = guys->speed + GUY_SPEED_INCREMENT;
    guys->speed = newSpeed > guys->speedLimit ? guys->speedLimit : newSpeed;
  }
}