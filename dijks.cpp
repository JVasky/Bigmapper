#include "dijks.h"
 
void Dijkstra::setMat(int mat[25][25]){
	for(int i = 0; i<25; i++){
		for(int j = 0; j<25; j++){
			this->adjMatrix[i][j] = mat[i][j];
		}
	}
}

 
void Dijkstra::initialize(){
  for(int i=0;i<numOfVertices;i++) {
    mark[i] = false;
    predecessor[i] = -1;
    distance[i] = INFINITY;
  }
  distance[source]= 0;
}
 
 
int Dijkstra::getClosestUnmarkedNode(){
  int minDistance = INFINITY;
  int closestUnmarkedNode;
  for(int i=0;i<numOfVertices;i++) {
    if((!mark[i]) && ( minDistance >= distance[i])) {
      minDistance = distance[i];
      closestUnmarkedNode = i;
    }
  }
  return closestUnmarkedNode;
}
 
 
void Dijkstra::calculateDistance(){
  initialize();
  int minDistance = INFINITY;
  int closestUnmarkedNode;
  int count = 0;
  while(count < numOfVertices) {
    closestUnmarkedNode = getClosestUnmarkedNode();
    mark[closestUnmarkedNode] = true;
    for(int i=0;i<numOfVertices;i++) {
      if((!mark[i]) && (adjMatrix[closestUnmarkedNode][i]>0) ) {
	if(distance[i] > distance[closestUnmarkedNode]+adjMatrix[closestUnmarkedNode][i]) {
	  distance[i] = distance[closestUnmarkedNode]+adjMatrix[closestUnmarkedNode][i];
	  predecessor[i] = closestUnmarkedNode;
	}
      }
    }
    count++;
  }
}
 
 
void Dijkstra::printPath(int node){
  if(node == source)
    cout<<(char)(node + 97)<<"..";
  else if(predecessor[node] == -1)
    cout<<"No path from “<<source<<”to "<<(char)(node + 97)<<endl;
  else {
    printPath(predecessor[node]);
    cout<<(char) (node + 97)<<"..";
  }
}
 
 
void Dijkstra::output(){
  for(int i=0;i<numOfVertices;i++) {
    if(i == source)
      cout<<(char)(source + 97)<<".."<<source;
    else
      printPath(i);
    cout<<"->"<<distance[i]<<endl;
  }
}



