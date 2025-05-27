#ifndef OBSTACLES_H
#define OBSTACLES_H

#include "raylib.h"
#include "raymath.h"

#include "../config.h"
#include "../state/state.h"

Obstacles initObstacles();

void resetObstacles(Obstacles *obstacles);

void forEachObstacle(State *state, void (*forEach)(Rectangle *rec, State *state, Body *body), Body *body);

void keepOutsideObstacle(Rectangle *rec, State *state, Body *body);

void drawObstacle(Rectangle *rec, State *state, Body *body);

#endif