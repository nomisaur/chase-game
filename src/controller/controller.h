#ifndef CONTROLLER_H
#define CONTROLLER_H

typedef struct Controller
{
  int up;
  int down;
  int left;
  int right;
  int boost;
  int pause;
  int select;
} Controller;

Controller initController();

#endif