#include <Navigator.h>

#define MIN_COLLISION_DISTANCE 25
#define TILE_DISTANCE 1000
#define TURN_DISTANCE 750

Navigator::Navigator(Motor* RM,Motor* LM,NewPing* us){
  Navigator::RM = RM;
  Navigator::LM = LM;
  Navigator::us = us;

  Navigator::runTime = 0;
  Navigator::freezeTime = 0;
  Navigator::targetTime = 0;
}

Navigator::~Navigator(){
  delete RM;
  delete LM;
  delete us;
}

    // STRAIGHT //

void Navigator::straight(){
  RM->on();
  LM->on();
}

void Navigator::straight(unsigned long time){
  initOp(time);

  while(!atTarget()){

    if(!isObstructed()){
      straight();
    }
    else{
      pause();
    }
  }

  STOP();
}

    // RIGHT //

void Navigator::turnRight(){
  RM->off();
  LM->on();
}

void Navigator::turnRight(unsigned long time){
  initOp(time);
  while(!atTarget()){
    turnRight();
  }
  STOP();
}

    // LEFT //

void Navigator::turnLeft(){
  RM->on();
  LM->off();
}

void Navigator::turnLeft(unsigned long time){
  initOp(time);
  while(!atTarget()){
    turnLeft();
  }
  STOP();
}

void Navigator::STOP(){
  RM->off();
  LM->off();
}

void Navigator::pause(){
  unsigned long freezeStart = millis();
  while(isObstructed()){
    STOP();
  }
  freezeTime = freezeTime + millis() - freezeStart;
}

void Navigator::initOp(unsigned long time){
  freezeTime = 0;
  runTime = millis();
  targetTime = time + runTime;
}

boolean Navigator::isObstructed(){
  return (us != 0 ) && (us->ping_median()/US_ROUNDTRIP_CM) < MIN_COLLISION_DISTANCE;
}

boolean Navigator::atTarget(){
  return targetTime + freezeTime <= millis();
}