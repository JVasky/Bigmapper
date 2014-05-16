#ifndef Motor_H
#define Motor_H

#include <Arduino.h>

class Motor {
  byte powerPin;
  byte directionPin;
  byte LED;
public:
  Motor(byte, byte);
  Motor(byte, byte, byte);
  Motor(byte, byte, byte, byte);
  ~Motor();
  void on();
  void off();
  void forward();
  void reverse();

  boolean isOn();
};

#endif