#include "image.xbm"
#include<stdio.h>
#include<queue>
#include<cmath>
#include<vector>
#include<set>
#define bitRead(value, bit) (((value) >> (bit)) & 0x01) // Macro for bitRead()
using namespace std;

struct coord{
  int x;
  int y;
  int name;
};

bool operator < ( const coord & a, const coord & b ) {
  return a.x < b.x && a.y < b.y;
}


int main(){
  //std::queue<coordinate> coords;
  vector<coord> coords;
  int i = 0;
  int count;
  int colCount = 0;
  int rowCount = 0;
  coord c = {0,0,0};
  coords.push_back(c);
  //  coordinate coordinates[];
  while(i < sizeof(image_bits)/sizeof(image_bits[0])){
    int j;
    for(j = 0;j<8;j++){
      printf("%hu", bitRead(image_bits[i],j));
      if(bitRead(image_bits[i],j)){
	if(i == 0 && j == 0){}
	else{
	  coord c = {count,rowCount,colCount};
	  count++;
	  coords.push_back(c);
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
  //coordinate coordinates[numOfVertices];
  //for(int i = 0; i < numOfVertices; i++){
  //  coordinates[i] = coords.front();;
  //}
  double adjMatrix[25][25];
  for(int i = 0; i < numOfVertices; i++){
    coord c1 = coords[i];
    for(int j = 0; j < numOfVertices; j++){
      coord c2 = coords[j];
      adjMatrix[i][j] = sqrt((c2.x - c1.x)*(c2.x - c1.x) + (c2.y - c1.y)*(c2.y - c1.y));
    }
  }
  printf("Num of vertices: %d\n", numOfVertices);
  //for(int i = 0; i < numOfVertices; i++){
  //  for(int j = 0; j < numOfVertices; j++){
  //    printf("%4f ",adjMatrix[i][j]);
  //  }
  //  printf("\n");
  //}

  set<coord> explored;
  queue<coord> path;
  //queue<coord> remaining;
  coord cur = coords[0];
  coord nearest = coords[1];
  path.push(cur);
  explored.insert(cur);
  int counter = 1;
  while(path.size() != numOfVertices){
    printf("Cur = %d, Near = %d, Counter = %d\n", cur.name, nearest.name, counter);
    double nearDist = adjMatrix[cur.name][nearest.name];
    for(int i=0; i < numOfVertices;i++){
      typename set<coord>::iterator it = explored.find(coords[i]);
      if(it != explored.end()){}
      else{
	double tempDist = adjMatrix[cur.name][coords[i].name];
	if(tempDist < nearDist){
	  nearDist = tempDist;
	  nearest = coords[i];
	}
      }
    }
    counter++;
    cur = nearest;
    path.push(cur);
    explored.insert(cur);
    if(count < numOfVertices){
      nearest = coords[counter];
    }
    else{}
  }

  while(!path.empty()){
    coord temp = path.front();
    path.pop();
    printf("(%d, %d) -> ",temp.x, temp.y);
  }
  printf("end\n");

}

  
 




