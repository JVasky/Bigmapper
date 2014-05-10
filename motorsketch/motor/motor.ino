int M1 = 4;
int M2 = 7;

int LMotor = 5;
int RMotor = 6;

#define velocity 1.0   // cm/ms ?
#define turnDist 500.0 //cm ?

void setup(){
  // Turn on M1, M2
  pinMode(M1,OUTPUT);
  pinMode(M2,OUTPUT);
  digitalWrite(M1,HIGH);
  digitalWrite(M2,HIGH);
  
  Serial.begin(9600);
}


void loop(){
  
  goStraight(3000);
  STOP(2000);
  turnRight();
  STOP(2000);
  turnLeft();
  goStraight(10000);
  
  TERMINATE();
  
  delay(1);
}

  // Basic Motor Functions

void motorOn(int motorPin){
  analogWrite(motorPin,255);
}

void motorOff(int motorPin){
  analogWrite(motorPin,0);
}

  // Boolean Motor Functions

  // *t is address of global timer variable
boolean runFor(int m,int time,int *t){
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

void STOP(int time){
  int timer = 0;
  while(!STOP(time,&timer)){
    delay(1);
  }
}

void TERMINATE(){
  motorOff(LMotor);
  motorOff(RMotor);
  while(1){}
}

void goStraight(int dist){
  int timer = 0;
  while(!goStraight(dist,&timer)){
    delay(1);
  }
}

void turnRight(){
  int timer = 0;
  while(!turnRight(&timer)){
    delay(1);
  }
}

void turnLeft(){
  int timer = 0;
  while(!turnLeft(&timer)){
    delay(1);
  }
}
