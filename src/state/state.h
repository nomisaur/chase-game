#ifndef STATE_H
#define STATE_H

#include "raylib.h"
#include "raymath.h"

#include "../config.h"

typedef struct Body
{
  int radius;
  Vector2 position;
  Vector2 velocity;
  Vector2 potentialPosition;
  Vector2 direction;
  bool colliding;
  Color color;
  struct
  {
    int distance;
    float width;
  } vision;
} Body;

typedef struct Player
{
  Body body;
  int speed;
  bool isBoosting;

  struct
  {
    Vector2 travel;
    double startTime;
    double duration;
    int speed;
  } boost;

  struct stamina
  {
    int total;
    int amount;
    double recoveryTime;
    double recoveryTimeFromZero;
    double startTime;
  } stamina;

} Player;

typedef struct Guy
{
  Body body;
  bool seesPlayer;
  bool alive;
} Guy;

typedef struct Guys
{
  Guy guy[GUY_LIMIT];
  int guysAlive;
  int guyInitial;
  int speed;
  int initialSpeed;
  int speedLimit;
} Guys;

typedef struct Obstacles
{
  Rectangle rec[OBSTACLE_LIMIT];
  Color color;
} Obstacles;

typedef enum
{
  Win,
  Pause,
  Play
} Scene;

typedef struct State
{
  double time;
  Scene scene;
  bool paused;
  Player player;
  Guys guys;
  Obstacles obstacles;
} State;

State initState();
void handlePlayerGuyCollision(Guy *guy, State *state);

#endif