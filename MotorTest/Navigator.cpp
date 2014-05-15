#include "Navigator.h"

#define MIN_COLLISION_DISTANCE 25
#define TILE_DISTANCE 1000

Navigator::Navigator(Motor *RM,Motor *LM,NewPing *us){
  Navigator::RM = RM;
  Navigator::LM = LM;
  Navigator::us = us;
  Navigator::runTime = 0;
  
  pinMode(10,OUTPUT);
}

Navigator::~Navigator(){
  delete RM;
  delete LM;
  delete us;
}

void Navigator::STOP(){
  RM->off();
  LM->off();
  digitalWrite(10,LOW);
}

void Navigator::straight(){
  runTime = millis();
  if(!isObstructed()){
    RM->on();
    LM->on();
  }
  else{
    STOP();
  }
}

void Navigator::turnRight(){
  runTime = millis();
  if(!isObstructed()){
    RM->off();
    LM->on();
  }
  else{
    STOP();
  }
}

void Navigator::turnLeft(){
  runTime = millis();
  if(!isObstructed()){
    RM->on();
    LM->off();
  }
  else{
    STOP();
  }
}

boolean Navigator::isObstructed(){
  return (Navigator::us->ping_median()/US_ROUNDTRIP_CM) < 25;
}

unsigned long Navigator::getRunTime(){
  return millis() - runTime;
}
