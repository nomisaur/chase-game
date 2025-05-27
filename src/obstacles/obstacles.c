#include "obstacles.h"

#include "raylib.h"
#include "raymath.h"

#include "../config.h"
#include "../state/state.h"
#include "../utils/utils.h"

#include <stdio.h>

Rectangle initRec()
{
  Rectangle rec;
  rec.height = 100;
  rec.width = 100;
  rec.x = 400;
  rec.y = 400;
  return rec;
}

void randomizeRec(Rectangle *rec)
{
  rec->height = GetRandomValue(80, 400);
  rec->width = GetRandomValue(80, 400);
  rec->x = GetRandomValue(0, GetScreenWidth()) - rec->width / 2;
  rec->y = GetRandomValue(0, GetScreenHeight()) - rec->height / 2;
}

void setRec(Rectangle *rec)
{
  rec->height = 400;
  rec->width = 800;
  rec->x = 400;
  rec->y = 400;
}

void resetObstacles(Obstacles *obstacles)
{
  for (int index = 0; index < OBSTACLE_LIMIT; ++index)
  {
    randomizeRec(&obstacles->rec[index]);
    // setRec(&obstacles->rec[index]);
  }
}

Obstacles initObstacles()
{
  Obstacles obstacles;
  obstacles.color = GREEN;

  for (int index = 0; index < OBSTACLE_LIMIT; ++index)
  {
    obstacles.rec[index] = initRec();
    // setRec(&obstacles.rec[index]);
    randomizeRec(&obstacles.rec[index]);
  }

  return obstacles;
}

void forEachObstacle(State *state, void (*forEach)(Rectangle *rec, State *state, Body *body), Body *body)
{
  for (int index = 0; index < OBSTACLE_LIMIT; ++index)
  {
    (*forEach)(&state->obstacles.rec[index], state, body);
  }
}

void keepOutsideObstacle(Rectangle *rec, State *state, Body *body)
{
  body->colliding = (bool)max(keepOutBound(body, *rec), body->colliding);

  // printf("%d\n", body->colliding);
}

void drawObstacle(Rectangle *rec, State *state, Body *body)
{
  // CLITERAL(Color){200, GetRandomValue(50, 200), GetRandomValue(50, 200), GetRandomValue(50, 200)}
  DrawRectangleRec(*rec, state->obstacles.color);
}