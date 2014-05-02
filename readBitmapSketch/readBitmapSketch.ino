#include <QueueArray.h>

#define image_width 16
#define image_height 16

static unsigned char image_bits[] = {
   0x00, 0x00, 0x00, 0x00, 0x20, 0x04, 0x10, 0x08, 0x00, 0x00, 0x20, 0x04,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x10, 0x08, 0x30, 0x0c, 0xd0, 0x0b,
   0x20, 0x04, 0xc0, 0x03, 0x00, 0x00, 0x00, 0x00 };
struct coordinate {
  int x;
  int y;
};
void setup(){
  QueueArray<coordinate> coords; // Declare Queue
  Serial.begin(9600);
  int i = 0;
  int colCount = 0;
  int rowCount = 0;
  while(i < sizeof(image_bits)/sizeof(image_bits[0])){
    int j;
    for(j = 0;j<8;j++){
      Serial.print(bitRead(image_bits[i],j));
      if(bitRead(image_bits[i],j)){
        coordinate c = {rowCount,colCount}; //make new coordinate
        coords.enqueue(c); //enqueue the coordinate
      }
      colCount++; // New column
      if(colCount == image_width){ // Last column
        Serial.print("\n");
        rowCount++; //increment row
        colCount = 0; // reset column
      }
    }
    i++;
  }
  while(!coords.isEmpty()){
    coordinate c = coords.dequeue();
   Serial.print("Coord: (" );
   Serial.print(c.x);
   Serial.print(", ");
   Serial.print(c.y);
   Serial.println(")");
  }
}

void loop(){
}
