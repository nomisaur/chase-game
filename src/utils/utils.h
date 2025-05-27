#ifndef UTILS_H
#define UTILS_H

#include "raylib.h"
#include "raymath.h"

#include "../state/state.h"

float keepBetween(float number, float min, float max);

bool isTouchingEdge(Body body);

bool hasTimePassedDuration(double time, double startTime, double duration);

bool keepOutBound(Body *body, Rectangle rec);

void keepInBound(Body *body);

float DirectionToDegrees(Vector2 direction);

Vector2 getDegreeWedge(float degree, float width);

bool checkBodyCollision(Body body1, Body body2);

bool checkVisionCollision(Body body1, Body body2);

float getRandomFloat(float min, float max);
float min(float a, float b);
float max(float a, float b);

extern int hbound;
extern int vbound;
extern float overlap;
extern Vector2 nearestPoint;
extern Vector2 rayToNearest;
extern float nearestX;
extern float nearestY;

#endif