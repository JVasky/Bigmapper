#include "image.xbm"
#include<stdio.h>
#include<queue>
#include<cmath>
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
  coordinate c = {0,0};
  coords.push(c);
  //  coordinate coordinates[];
  while(i < sizeof(image_bits)/sizeof(image_bits[0])){
    int j;
    for(j = 0;j<8;j++){
      printf("%hu", bitRead(image_bits[i],j));
      if(bitRead(image_bits[i],j)){
	if(i == 0 && j == 0){}
	else{
	  coordinate c = {rowCount,colCount};
	  coords.push(c);
	}
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
  int numOfVertices =  coords.size();
  coordinate coordinates[numOfVertices];
  for(int i = 0; i < numOfVertices; i++){
    coordinates[i] = coords.front();
    coords.pop();
  }
  int adjMatrix[numOfVertices][numOfVertices];
  for(int i = 0; i < numOfVertices; i++){
    coordinate c1 = coordinates[i];
    for(int j = 0; j < numOfVertices; j++){
      coordinate c2 = coordinates[j];
      adjMatrix[i][j] = sqrt((c2.x - c1.x)*(c2.x - c1.x) + (c2.y - c1.y)*(c2.y - c1.y));
    }
  }
  printf("Num of vertices: %d\n", numOfVertices);
  for(int i = 0; i < numOfVertices; i++){
    for(int j = 0; j < numOfVertices; j++){
      printf("%4d ",adjMatrix[i][j]);
    }
    printf("\n");
  }
  return 0;
}















