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
#define bitRead(value, bit) (((value) >> (bit)) & 0x01) // Macro for bitRead()
using namespace std;

#define image_width 16
#define image_height 16
static unsigned char image_bits[] = {
   0x00, 0x00, 0x00, 0x00, 0x20, 0x04, 0x10, 0x08, 0x00, 0x00, 0x20, 0x04,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x10, 0x08, 0x30, 0x0c, 0xd0, 0x0b,
   0x20, 0x04, 0xc0, 0x03, 0x00, 0x00, 0x00, 0x00 };

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


void setup(){
  Serial.begin(9600);
  vector<coord> coords;
  int i = 0;
  int colCount = 0;
  int rowCount = 0;
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

  queue<coord> path;
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
    Serial.print("Cur: ");
    Serial.print(cur.x);
    Serial.print(", ");
    Serial.println(cur.y);
    delay(200);
    nearest = coords[0];
  }

  while(!path.empty()){
    coord temp = path.front();
    path.pop();
    Serial.print("(");
    Serial.print(temp.x);
    Serial.print(", ");
    Serial.print(temp.y);
    Serial.print(")");
    Serial.print("-> ");
  }
  Serial.print("end\n");

}

void loop(){

}  
 





