#ifndef GUYS_H
#define GUYS_H

#include "raylib.h"
#include "raymath.h"

#include "../config.h"
#include "../state/state.h"

Guy initGuy();

Guys initGuys();
void resetGuys(Guys *guys);

void moveGuy(Guy *guy, State *state);

void forEachAliveGuy(State *state, void (*forEach)(Guy *guy, State *state));

void drawGuyVision(Guy *guy, State *state);
void drawGuy(Guy *guy, State *state);

void handleGuyPlayerVisionCollision(Guy *guy, State *state);

#endif