#ifndef NAVIGATOR_H
#define NAVIGATOR_H

#include <Motor.h>
#include <NewPing.h>
#include <Arduino.h>

class NavOp;

class Navigator {

  Motor* RM;
  Motor* LM;
  NewPing* us;

  //NavOp* currentOp;

  unsigned long runTime;
  unsigned long freezeTime;
  unsigned long targetTime;

public:
  Navigator(Motor*,Motor*,NewPing*);
  ~Navigator();

  void straight(unsigned long);

  void turnLeft(unsigned long);

  void turnRight(unsigned long);

  void STOP();

private:
  void straight();
  void turnLeft();
  void turnRight();

  void pause();

  boolean isObstructed();
  boolean atTarget();

  void initOp(unsigned long/*,NavOp*/);

};

#endif