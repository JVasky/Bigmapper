#include <utility.h>
#include <system_configuration.h>
#include <StandardCplusplus.h>
#include <unwind-cxx.h>
#include <stdio.h>
#include <queue>
#include <cmath>
#include <vector>
#include <set>
#include <algorithm>
#include <Motor.h>
#include <Navigator.h>
#include <Mapper.h>
#include <NewPing.h>
#include <Sound.h>

#define bitRead(value, bit) (((value) >> (bit)) & 0x01) // Macro for bitRead()

  // Comment this line to eliminate serial output
//#define SERIAL_OUTPUT_ENABLED

#define NORTH 1
#define SOUTH 2
#define EAST 3
#define WEST 4

#define M1 4
#define LMotorPow 5

#define M2 7
#define RMotorPow 6

#define US_TRIGGER 12
#define US_ECHO 11

#define LED 13
#define SPEAKER A0
using namespace std;

#define image_width 8
#define image_height 8
static unsigned char image_bits[] = {
   0x00, 0x00, 0x24, 0x00, 0x42, 0x3c, 0x00, 0x00 };



struct coord{
  int x;
  int y;
};

bool operator == ( coord a, coord b ) {
  return a.x == b.x && a.y == b.y;
}

bool contains(const std::vector<coord> vec, const coord &value)
{
    return std::find(vec.begin(), vec.end(), value) != vec.end();
}

int direction = 1; // start it facing north
queue<coord> path;

coord current;
coord target;

Motor RMotor(RMotorPow,M2,9);
Motor LMotor(LMotorPow,M1,13);

NewPing us(US_TRIGGER,US_ECHO);
Navigator robot(&RMotor, &LMotor,0);

Sound s(SPEAKER);

void setup(){
#ifdef SERIAL_OUTPUT_ENABLED
  Serial.begin(9600);
#endif
  pinMode(LED,OUTPUT);
  int i = 0;
  int colCount = 0;
  int rowCount = 0;
  vector<coord> coords;
  coord c = {0,0};
  coords.push_back(c);
  while(i < sizeof(image_bits)/sizeof(image_bits[0])){
    int j;
    for(j = 0;j<8;j++){
      if(bitRead(image_bits[i],j)){
	if(i == 0 && j == 0){}
	else{
	  coord c = {colCount,rowCount};
	  coords.push_back(c);
	}
      }
      colCount++;
	if(colCount == image_width){
	  rowCount++;
	  colCount = 0;
	}
    }
    i++;
  }
  
  int numOfVertices =  coords.size();

  coord cur = coords[0];
  coords.erase(find(coords.begin(), coords.end(), cur));
  coord nearest = coords[0];
  path.push(cur);
  while(coords.size() != 0){
    double nearDist = sqrt((nearest.x - cur.x)*(nearest.x - cur.x) + (nearest.y - cur.y)*(nearest.y - cur.y));;
    for(int i=0; i < coords.size(); i++){
        coord tempCoord = coords[i];
	double tempDist = sqrt((tempCoord.x - cur.x)*(tempCoord.x - cur.x) + (tempCoord.y - cur.y)*(tempCoord.y - cur.y));;
	if(tempDist < nearDist && !(tempCoord == nearest)){
	  nearDist = tempDist;
	  nearest = tempCoord;
	}
    }
    
    cur = nearest;
    path.push(cur);
    coords.erase(find(coords.begin(), coords.end(), cur));
#ifdef SERIAL_OUTPUT_ENABLED
    Serial.print("Cur: ");
    Serial.print(cur.x);
    Serial.print(", ");
    Serial.println(cur.y);
#endif
    nearest = coords[0];
  }
  current = path.front();
  path.pop();
  
  s.beepSequenceUp();

}

void loop(){
#ifdef SERIAL_OUTPUT_ENABLED
  Serial.println("Beginning of loop");
#endif
  if(path.empty()){
   target.x = 0;
   target.y = 0;
  }
  else{
   target = path.front();
   path.pop();
  }
#ifdef SERIAL_OUTPUT_ENABLED
  Serial.print("Current: ");
  Serial.print(current.x);
  Serial.print(", ");
  Serial.println(current.y);
  
  Serial.print("Target: ");
  Serial.print(target.x);
  Serial.print(", ");
  Serial.println(target.y);
  
  // first get to correct row
  
  Serial.println("Go to row");
#endif
  if(target.x > current.x){ // target is North
   toNorth(&robot);
   delay(500);
#ifdef SERIAL_OUTPUT_ENABLED
   Serial.println("TO NORTH");
   Serial.print("Target - Current = ");
   Serial.println(target.x - current.x);
#endif
   robot.straightNTiles(target.x - current.x);
#ifdef SERIAL_OUTPUT_ENABLED
   Serial.println("WENT STRAIGHT");
#endif
  } 
  else if(target.x < current.x){  // target South
   toSouth(&robot);
   delay(500);
#ifdef SERIAL_OUTPUT_ENABLED
   Serial.println("TO SOUTH");
#endif
   robot.straightNTiles(current.x - target.x);
  }
  else{} // it is in the same row so don't do anything
  
  delay(1000);
  
  // now correct column
#ifdef SERIAL_OUTPUT_ENABLED
  Serial.println("Go to col");
#endif
  if(target.y > current.y){ // target East
   toEast(&robot);
   delay(500);
#ifdef SERIAL_OUTPUT_ENABLED
   Serial.println("TO EAST");
#endif
   robot.straightNTiles(target.y - current.y); 
  }
  else if(target.y < current.y){  // target West
   toWest(&robot);
   delay(500);
#ifdef SERIAL_OUTPUT_ENABLED
   Serial.println("TO WEST");
#endif
   robot.straightNTiles(current.y - target.y);
  }
  else{} // in same column, nothing to do
  
  current = target;
#ifdef SERIAL_OUTPUT_ENABLED
  Serial.println("New current assigned");
#endif 
  digitalWrite(LED, HIGH);
  s.beep();
  delay(3000);
  digitalWrite(LED, LOW);
  s.beepSequenceDn();
  while(path.empty() && target.x == 0 && target.y == 0){
#ifdef SERIAL_OUTPUT_ENABLED
    Serial.println("IN END WHILE");
#endif
  } 
}

void toNorth(Navigator* n){
  if(direction == NORTH){}
  else if(direction == EAST){
   n->turnLeft();
  }
  else if(direction == WEST){
   n->turnRight(); 
  }
  else if(direction == SOUTH){
   n->turnRight();
   n->turnRight(); 
  }
  direction = NORTH;
}

void toSouth(Navigator* n){
  if(direction == SOUTH){}
  else if(direction == EAST){
   n->turnRight();
  }
  else if(direction == WEST){
   n->turnLeft(); 
  }
  else if(direction == NORTH){
#ifdef SERIAL_OUTPUT_ENABLED
    Serial.println("First Right");
#endif
    n->turnRight();
#ifdef SERIAL_OUTPUT_ENABLED
    Serial.println("Second Right");
#endif
    n->turnRight(); 
  }
  direction = SOUTH;
}

void toEast(Navigator* n){
  if(direction == EAST){}
  else if(direction == NORTH){
   n->turnRight();
  }
  else if(direction == SOUTH){
   n->turnLeft(); 
  }
  else if(direction == WEST){
   n->turnRight();
   n->turnRight(); 
  }
  direction = EAST;
}

void toWest(Navigator* n){
  if(direction == WEST){}
  else if(direction == SOUTH){
   n->turnRight();
  }
  else if(direction == NORTH){
   n->turnLeft(); 
  }
  else if(direction == EAST){
   n->turnRight();
   n->turnRight(); 
  }
  direction = WEST;
}
