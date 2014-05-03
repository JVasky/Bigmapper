#include "image.xbm"
#include<stdio.h>
#include<queue>
#define bitRead(value, bit) (((value) >> (bit)) & 0x01) // Macro for bitRead()

struct coordinate{
  int x;
  int y;
};

int main(){
  std::queue<coordinate> coords;
  int i = 0;
  int colCount = 0;
  int rowCount = 0;
  while(i < sizeof(image_bits)/sizeof(image_bits[0])){
    int j;
    for(j = 0;j<8;j++){
      printf("%hu", bitRead(image_bits[i],j));
      if(bitRead(image_bits[i],j)){
	coordinate c = {rowCount,colCount};
	coords.push(c);
      }
      colCount++;
	if(colCount == image_width){
	  printf("\n");
	  rowCount++;
	  colCount = 0;
	}
    }
    i++;
  }
  while(!coords.empty()){
    coordinate c = coords.front();
    coords.pop();
    printf("Coord: (%d, %d)\n", c.x, c.y);
  }
  return 0;
}

















