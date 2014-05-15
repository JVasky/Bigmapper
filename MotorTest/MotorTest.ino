#include "Motor.h"
#include <NewPing.h>
#include "Navigator.h";

#define M1 4
#define M2 7

#define LMotorPin 5
#define RMotorPin 6

#define US_TRIGGER 12
#define US_ECHO 11

Motor RMotor(RMotorPin,M2);
Motor LMotor(LMotorPin,M1);

NewPing us(US_TRIGGER,US_ECHO);

Navigator robot(&RMotor,&LMotor,&us);

void setup(){
  Serial.begin(115200);
}

void loop(){
//  robot.straight();
  delay(1);
}
