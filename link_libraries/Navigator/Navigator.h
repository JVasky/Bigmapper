#ifndef NAVIGATOR_H
#define NAVIGATOR_H

#include <Motor.h>
#include <NewPing.h>
#include <Sound.h>
#include <Arduino.h>

class Navigator {

  Motor* RM;
  Motor* LM;
  NewPing* us;

  Sound* s;

  unsigned long runTime;
  unsigned long freezeTime;
  unsigned long targetTime;

public:

  Navigator(Motor*,Motor*,NewPing*);
  ~Navigator();

  void straight(unsigned long);
  void straightNTiles(byte);
  void turnLeft();
  void turnRight();

  void STOP();

private:

  void pause();

  boolean isObstructed();
  boolean atTarget();

  void initOp(unsigned long);

};

#endif