#include <NewPing.h>

byte M1 = 4;
byte M2 = 7;
byte led = 10;

byte LMotor = 5;
byte RMotor = 6;

unsigned long t1 = 0;

#define USSampleSize 50

unsigned int distances[USSampleSize];
unsigned int distReg = 0;
int distCounter = 0;

#define LOOP_DELAY 1

#define velocity 1.0   // cm/ms ?
#define turnDist 500.0 // cm ?

#define TRIGGER_PIN 12
#define ECHO_PIN 11
#define MAX_DISTANCE 200

NewPing us(TRIGGER_PIN,ECHO_PIN,MAX_DISTANCE);

void setup(){
  // Turn on M1, M2
  pinMode(M1,OUTPUT);
  pinMode(M2,OUTPUT);
  digitalWrite(M1,HIGH);
  digitalWrite(M2,HIGH);
  
  pinMode(led,OUTPUT);
  
  Serial.begin(115200);
}


void loop(){
  
  unsigned int dist = us.ping() / US_ROUNDTRIP_CM;
  //int avgdist = avgSample(dist,USSampleSize,distances,&distCounter,&distReg);
  //int avgdist = avgSample(dist,USSampleSize);
  Serial.print("distance (cm): ");
  Serial.print(dist);
  //Serial.print(us.ping_median()/US_ROUNDTRIP_CM);
  Serial.print("\t");
  if((us.ping_median()/US_ROUNDTRIP_CM) < 25){
    digitalWrite(led,HIGH);
    //motorOn(LMotor);
  }
  else {
    digitalWrite(led,LOW);
    motorOff(LMotor);
  }
  Serial.println(millis()-t1);
  t1 = millis();
  
  /*goStraight(3000);
  STOP(2000);
  turnRight();
  STOP(2000);
  turnLeft();
  STOP(2000);
  goStraight(10000);
  
  TERMINATE();*/
  
  delay(LOOP_DELAY);
}

  // Basic Motor Functions

void motorOn(byte motorPin){
  analogWrite(motorPin,255);
}

void motorOff(byte motorPin){
  analogWrite(motorPin,0);
}

  // Boolean Motor Functions

  // *t is address of global timer variable
boolean runFor(byte m,int time,int *t){
  boolean complete = false;
  if(*t < time){
    motorOn(m);
    *t = *t + 1;
  }
  else{
    motorOff(m);
    complete = true;
  }
  return complete;
}

boolean STOP(int time, int *t){
  boolean complete = false;
  if(*t < time){
    motorOff(RMotor);
    motorOff(LMotor);
    *t = *t + 1;
  }
  else{
    complete = true;
  }
  return complete;
}

  // distance in cm ??
boolean goStraight(int dist,int *t){
  boolean Lcomplete = runFor(LMotor,(int)(dist*2/velocity),t);
  boolean Rcomplete = runFor(RMotor,(int)(dist*2/velocity),t);
  return Lcomplete && Rcomplete;
}

  // 90 degrees
boolean turnRight(int *t){
  motorOff(RMotor);
  return runFor(LMotor,(int)(turnDist/velocity),t);
}

  // 90 degrees

boolean turnLeft(int *t){
  motorOff(LMotor);
  return runFor(RMotor,(int)(turnDist/velocity),t);
}

// Void Motor Functions

void STOP(int time){  // move to motor class
  int timer = 0;
  while(!STOP(time,&timer)){
    delay(LOOP_DELAY);
  }
}

void STOP(){
  motorOff(RMotor);
  motorOff(LMotor);
}

void TERMINATE(){
  motorOff(LMotor);
  motorOff(RMotor);
  while(1){}
}

void goStraight(int dist){
  int timer = 0;
  while(!goStraight(dist,&timer)){
    delay(LOOP_DELAY);
  }
}

void turnRight(){
  int timer = 0;
  while(!turnRight(&timer)){
    delay(LOOP_DELAY);
  }
}

void turnLeft(){
  int timer = 0;
  while(!turnLeft(&timer)){
    delay(LOOP_DELAY);
  }
}

// Ultrasound data functions

/*int avgSample(unsigned int dist,int sampleSize){
  unsigned int a[sampleSize];
  int acounter = 0;
  unsigned int sum = 0;
  return avgSample(dist,sampleSize,a,&acounter,&sum);
}*/

int avgSample(unsigned int dist,int sampleSize,unsigned int *a,int *acounter, unsigned int *sum){
  *sum = *sum - a[*acounter] + dist;
  a[*acounter] = dist;
  *acounter = (*acounter + 1)%sampleSize;
  return *sum/sampleSize;
}
