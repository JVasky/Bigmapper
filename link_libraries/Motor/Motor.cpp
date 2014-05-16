#include "Motor.h"

Motor::Motor(byte motorPin, byte speedPin){
  pinMode(speedPin, OUTPUT);
  digitalWrite(speedPin,HIGH);

  Motor::powerPin = motorPin;
}

Motor::Motor(byte powerPin, byte speedPin, byte LED){
  pinMode(speedPin, OUTPUT);
  digitalWrite(speedPin,HIGH);

  Motor::powerPin = powerPin;
}

Motor::Motor(byte powerPin, byte directionPin, byte speedPin, byte LED){
  pinMode(directionPin, OUTPUT);
  pinMode(speedPin, OUTPUT);
  pinMode(LED,OUTPUT);
  digitalWrite(speedPin,HIGH);

  Motor::powerPin = powerPin;
  Motor::directionPin = directionPin;
  
  Motor::LED = LED;    // for testing
}
 
Motor::~Motor(){}

void Motor::on(){
  analogWrite(powerPin,255);
  digitalWrite(LED,HIGH);  // test LED
}

void Motor::off(){
  analogWrite(powerPin,0);
  digitalWrite(LED,LOW);
}

void Motor::forward(){
  digitalWrite(directionPin,LOW);
}

void Motor::reverse(){
  digitalWrite(directionPin,HIGH);
}

boolean Motor::isOn(){
  return analogRead(powerPin) > 200;
}