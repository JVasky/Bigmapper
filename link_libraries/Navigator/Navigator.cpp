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

void Navigator::straight(unsigned long time){
  initOp(time);

  while(!atTarget()){

    if(!isObstructed()){
      RM->on();
      LM->on();
    }
    else{
      pause();
    }
  }

  STOP();
}

void Navigator::straightNTiles(byte n){
  straight(n * (unsigned long)TILE_DISTANCE);
}

    // RIGHT //

void Navigator::turnRight(){
  initOp(TURN_DISTANCE);
  while(!atTarget()){
    RM->off();
    LM->on();
  }
  STOP();
}

    // LEFT //

void Navigator::turnLeft(){
  initOp(TURN_DISTANCE);
  while(!atTarget()){
    RM->on();
    LM->off();
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