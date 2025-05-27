#ifndef PLAYER_H
#define PLAYER_H

#include "raylib.h"
#include "raymath.h"

#include "../state/state.h"
#include "../controller/controller.h"

Player initPlayer();
void resetPlayer(Player *player);
void movePlayer(Player *player, Controller controller, State state);
void drawPlayer(Player player);

#endif