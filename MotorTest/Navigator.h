#ifndef Navigator_H
#define Navigator_H

#include <NewPing.h>
#include "Motor.h"

class Navigator {
  Motor* LM;
  Motor* RM;
  NewPing* us;
  unsigned long runTime;
public:
  Navigator(Motor*,Motor*,NewPing*);
  ~Navigator();
  
  void STOP();
  void straight();
  void turnRight();
  void turnLeft();
  
  boolean isObstructed();
  unsigned long getRunTime();
  
private:
  void resetRunTime();
};
 
#endif
