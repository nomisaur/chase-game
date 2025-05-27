#include "player.h"

#include "raylib.h"
#include "raymath.h"

#include "../config.h"
#include "../state/state.h"
#include "../controller/controller.h"
#include "../obstacles/obstacles.h"
#include "../utils/utils.h"

Player initPlayer()
{
  Player player;
  player.body.position = (Vector2){GetScreenWidth() / 2, GetScreenHeight() / 2};
  player.body.radius = PLAYER_RADIUS;
  player.body.direction = Vector2Zero();
  player.body.color = BLUE;
  player.speed = PLAYER_SPEED;
  player.boost.duration = BOOST_DURATION;
  player.boost.speed = BOOST_SPEED;
  player.stamina.total = INITIAL_STAMINA;
  player.stamina.amount = INITIAL_STAMINA;
  player.stamina.recoveryTime = BOOST_RECOVERY_TIME;
  player.stamina.recoveryTimeFromZero = BOOST_RECOVERY_TIME_FROM_ZERO;
  return player;
}

void resetPlayer(Player *player)
{
  player->body.position = (Vector2){GetScreenWidth() / 2, GetScreenHeight() / 2};
  player->stamina.total = INITIAL_STAMINA;
  player->stamina.amount = INITIAL_STAMINA;
}

void movePlayer(Player *player, Controller controller, State state)
{
  Vector2 input = (Vector2){0, 0};

  if (IsKeyDown(controller.right))
    input.x += 1.0f;
  if (IsKeyDown(controller.left))
    input.x -= 1.0f;
  if (IsKeyDown(controller.up))
    input.y -= 1.0f;
  if (IsKeyDown(controller.down))
    input.y += 1.0f;

  bool isInputing = !Vector2Equals(input, Vector2Zero());

  if (isInputing && !player->isBoosting)
  {
    player->body.direction = Vector2Normalize(input);
  }

  if (!player->isBoosting &&
      IsKeyPressed(controller.boost) &&
      isInputing &&
      player->stamina.amount > 0)
  {
    player->isBoosting = true;
    player->boost.startTime = state.time;
    if (TURN_ON_STAMINA)
    {
      player->stamina.amount -= 1;
      player->stamina.startTime = state.time;
    }
  }

  if (player->isBoosting && hasTimePassedDuration(state.time, player->boost.startTime, player->boost.duration))
  {
    player->isBoosting = false;
  }

  if (TURN_ON_STAMINA &&
      player->stamina.amount < player->stamina.total &&
      hasTimePassedDuration(state.time,
                            player->stamina.startTime,
                            player->stamina.amount == 0
                                ? player->stamina.recoveryTimeFromZero
                                : player->stamina.recoveryTime))
  {
    player->stamina.amount = player->stamina.total;
  }

  if (isInputing || player->isBoosting)
  {
    player->body.velocity = Vector2Scale(player->body.direction,
                                         player->isBoosting ? player->boost.speed : player->speed);

    player->body.potentialPosition = Vector2Add(player->body.position, player->body.velocity);

    player->body.position = player->body.potentialPosition;
  }
  forEachObstacle(&state, keepOutsideObstacle, &player->body);

  keepInBound(&player->body);
  player->body.colliding = false;
}

void drawPlayer(Player player)
{
  DrawCircleV(player.body.position, player.body.radius, player.body.color);

  // float angle = DirectionToDegrees(player.body.direction);
  // float start = angle + 45;
  // float end = angle - 45;

  // DrawCircleSector(player.body.position, player.body.radius + 0.01, start, end, 100, GREEN);
}

Player player;