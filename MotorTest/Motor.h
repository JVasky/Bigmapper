#ifndef Motor_H
#define Motor_H

#include <Arduino.h>

class Motor {
  byte pin;
public:
  Motor(byte, byte);
  ~Motor();
  void on();
  void off();
  int isOn();
};

#endif
