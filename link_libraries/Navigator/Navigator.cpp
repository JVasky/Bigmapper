#include <Navigator.h>
#define MIN_COLLISION_DISTANCE 25
#define TILE_DISTANCE 500
#define TURN_RIGHT_DISTANCE 2600//2312
#define TURN_LEFT_DISTANCE 2100 //1750

#include <Arduino.h>


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
/*
Serial.print(millis());
Serial.print("\t");
Serial.print(freezeTime);
Serial.print("\t");
Serial.print(targetTime+freezeTime);
Serial.print("\t");
Serial.print(atTarget());
Serial.print("\t");
Serial.println(isObstructed());
*/
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
  initOp(TURN_RIGHT_DISTANCE);
  while(!atTarget()){
    RM->off();
    LM->on();
  }
  STOP();
}

    // LEFT //

void Navigator::turnLeft(){
  initOp(TURN_LEFT_DISTANCE);
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
/*
Serial.print(millis());
Serial.print("\t");
Serial.print(freezeTime);
Serial.print("\t");
Serial.print(targetTime+freezeTime);
Serial.print("\t");
Serial.print(atTarget());
Serial.print("\t");
Serial.println(isObstructed());
*/
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
  int dist = 0;
  if(us != 0){
    dist = us->ping_median()/US_ROUNDTRIP_CM;
  }
  return (us != 0) && (dist <= MIN_COLLISION_DISTANCE) && (dist != 0);
}

boolean Navigator::atTarget(){
  return targetTime + freezeTime <= millis();
}