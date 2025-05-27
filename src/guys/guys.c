#include "guys.h"

#include <math.h>
#include "raylib.h"
#include "raymath.h"

#include "../state/state.h"
#include "../utils/utils.h"
#include "../obstacles/obstacles.h"

Guy initGuy()
{
  Guy guy;
  guy.alive = false;
  guy.seesPlayer = false;
  guy.body.position = Vector2Zero();
  guy.body.radius = GUY_RADIUS;
  guy.body.direction = Vector2Zero();
  guy.body.vision.distance = GUY_VISION_DISTANCE;
  guy.body.vision.width = GUY_VISION_WIDTH;
  guy.body.color = YELLOW;
  return guy;
}

void resetGuy(Guy *guy, Guys guys)
{
  guy->alive = true;
  guy->body.position = (Vector2){GetRandomValue(guy->body.radius, GetScreenWidth() - guy->body.radius), GetRandomValue(guy->body.radius, GetScreenHeight() - guy->body.radius)};
  guy->body.direction = Vector2Zero();
  guy->body.color = YELLOW;
}

Guys initGuys()
{
  Guys guys;
  guys.guyInitial = INITIAL_GUY_AMOUNT;
  guys.guysAlive = INITIAL_GUY_AMOUNT;
  guys.initialSpeed = GUY_INITIAL_SPEED;
  guys.speed = guys.initialSpeed;
  guys.speedLimit = GUY_SPEED_LIMIT;
  for (int index = 0; index < GUY_LIMIT; ++index)
  {
    guys.guy[index] = initGuy();
    if (index < INITIAL_GUY_AMOUNT)
    {
      resetGuy(&guys.guy[index], guys);
    }
  }
  return guys;
}

void resetGuys(Guys *guys)
{
  guys->guysAlive = guys->guyInitial;
  guys->speed = guys->initialSpeed;
  for (int index = 0; index < guys->guyInitial; ++index)
  {
    resetGuy(&guys->guy[index], *guys);
  }
}

void forEachAliveGuy(State *state, void (*forEach)(Guy *guy, State *state))
{
  for (int index = 0; index < state->guys.guyInitial; ++index)
  {
    if (state->guys.guy[index].alive)
    {
      (*forEach)(&state->guys.guy[index], state);
    }
  }
};

void moveGuy(Guy *guy, State *state)
{
  bool changeDirection = GetRandomValue(1, 100) < 4 || isTouchingEdge(guy->body) || guy->body.colliding;

  if (changeDirection)
  {
    guy->body.direction = Vector2Normalize((Vector2){getRandomFloat(-1, 1), getRandomFloat(-1, 1)});
    guy->body.colliding = false;
  }

  if (guy->seesPlayer)
  {
    guy->body.direction = Vector2Normalize(Vector2Subtract(guy->body.position, state->player.body.position));
  }

  guy->body.position = Vector2Add(guy->body.position,
                                  Vector2Scale(guy->body.direction,
                                               state->guys.speed));
  keepInBound(&guy->body);
  forEachObstacle(state, keepOutsideObstacle, &guy->body);
}

void drawGuyVision(Guy *guy, State *state)
{
  float degree = DirectionToDegrees(guy->body.direction);
  Vector2 width = getDegreeWedge(degree, guy->body.vision.width);
  DrawCircleSector(guy->body.position, guy->body.vision.distance, width.x, width.y, 100, DARKGRAY);
}

void drawGuy(Guy *guy, State *state)
{
  DrawCircleV(guy->body.position, guy->body.radius, guy->body.color);
}

void handleGuyPlayerVisionCollision(Guy *guy, State *state)
{
  guy->seesPlayer = checkVisionCollision(guy->body, state->player.body);
  guy->body.color = guy->seesPlayer ? RED : YELLOW;
}