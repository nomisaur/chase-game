#include "utils.h"

#include <math.h>
#include <stdlib.h>
#include "raylib.h"
#include "raymath.h"

#include "../state/state.h"
#include "../config.h"

int hbound = false;
int vbound = false;
float overlap = 0;
Vector2 nearestPoint = (Vector2){0, 0};
Vector2 rayToNearest = (Vector2){0, 0};
float nearestX = 0;
float nearestY = 0;

bool isTouchingEdge(Body body)
{
  return body.position.x - body.radius == 0 ||
         body.position.x + body.radius == GetScreenWidth() ||
         body.position.y - body.radius == 0 ||
         body.position.y + body.radius == GetScreenHeight();
}

bool hasTimePassedDuration(double time, double startTime, double duration)
{
  return duration < time - startTime;
}

void keepInBound(Body *body)
{
  body->position.x = Clamp(body->position.x, 0.0f + body->radius, (float)GetScreenWidth() - body->radius);
  body->position.y = Clamp(body->position.y, 0.0f + body->radius, (float)GetScreenHeight() - body->radius);
}

// y = mx + b

float vectorMagnitude(Vector2 v)
{
  return sqrt(v.x * v.x + v.y * v.y);
}

float min(float a, float b)
{
  return a < b ? a : b;
}

float max(float a, float b)
{
  return a > b ? a : b;
}

bool keepOutBound(Body *body, Rectangle rec)
{

  if (CheckCollisionPointRec(body->position, rec))
  {
    nearestX = fabsf(body->position.x - rec.x) < fabsf(body->position.x - (rec.x + rec.width)) ? rec.x : rec.x + rec.width;
    nearestY = fabsf(body->position.y - rec.y) < fabsf(body->position.y - (rec.y + rec.height)) ? rec.y : rec.y + rec.height;

    nearestPoint = fabsf(body->position.x - nearestX) < fabsf(body->position.y - nearestY)
                       ? (Vector2){nearestX, body->position.y}
                       : (Vector2){body->position.x, nearestY};
    rayToNearest = Vector2Subtract(nearestPoint, body->position);
    overlap = body->radius + vectorMagnitude(rayToNearest);
    if (overlap > 0)
    {
      body->position = Vector2Add(body->position, Vector2Scale(Vector2Normalize(rayToNearest), overlap));
    }
    return true;
  }
  nearestPoint = (Vector2){Clamp(body->position.x, rec.x, rec.x + rec.width),
                           Clamp(body->position.y, rec.y, rec.y + rec.height)};

  rayToNearest = Vector2Subtract(nearestPoint, body->position);

  overlap = body->radius - vectorMagnitude(rayToNearest);

  if (overlap > 0)
  {
    body->position = Vector2Subtract(body->position, Vector2Scale(Vector2Normalize(rayToNearest), overlap));
    return true;
  }
  return false;
}

float DirectionToDegrees(Vector2 direction)
{
  return atan2f(direction.x, direction.y) * RAD2DEG;
}

Vector2 getDegreeWedge(float degree, float width)
{
  float half = width / 2;
  return (Vector2){degree - half, degree + half};
}

bool checkBodyCollision(Body body1, Body body2)
{
  return CheckCollisionCircles(body1.position, body1.radius, body2.position, body2.radius);
}

bool isDegreeBetweenDegrees(float target, float start, float end)
{
  if (start < end)
  {
    return target >= start && target <= end;
  }
  else
  {
    return target <= start && target >= end;
  }
}

float getRandomFloat(float min, float max)
{
  float randomNum = ((float)rand()) / RAND_MAX;
  return (randomNum * (max - min)) + min;
}

bool checkVisionCollision(Body looker, Body target)
{
  if (!CheckCollisionCircles(looker.position, looker.vision.distance, target.position, target.radius))
  {
    return false;
  }

  float degree = DirectionToDegrees(looker.direction);

  Vector2 width = getDegreeWedge(degree, looker.vision.width);

  float targetDegree = DirectionToDegrees(Vector2Subtract(target.position, looker.position));

  if (!isDegreeBetweenDegrees(targetDegree, width.x, width.y))
  {
    return false;
  }

  return true;
}