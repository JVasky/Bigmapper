#include "Motor.h"

Motor::Motor(byte motorPin, byte speedPin){
  pinMode(speedPin, OUTPUT);
  digitalWrite(speedPin,HIGH);

  Motor::pin = motorPin;
}
 
Motor::~Motor(){}

void Motor::on(){
  analogWrite(pin,255);
  digitalWrite(10,HIGH);
}

void Motor::off(){
  analogWrite(pin,0);
}

int Motor::isOn(){
  return pin;
}
