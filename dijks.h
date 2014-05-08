/*
 * dijks.h
 *
 *  Created on: May 8, 2014
 *      Author: jim
 */

#ifndef DIJKS_H_
#define DIJKS_H_

#include<iostream>
#include<stdio.h>
#define INFINITY 9999

using namespace std;

class Dijkstra{
private:
  int adjMatrix[25][25];
  int predecessor[25],distance[25];
  bool mark[25]; //keep track of visited node
  int source = 1;
  int numOfVertices = 25;
public:
  /*
   * Function read() reads No of vertices, Adjacency Matrix and source
   * Matrix from the user. The number of vertices must be greather than
   * zero, all members of Adjacency Matrix must be postive as distances
   * are always positive. The source vertex must also be positive from 0
   * to noOfVertices - 1

   */


  void setMat(int mat[25][25]);

  /*
   * Function initialize initializes all the data members at the begining of
   * the execution. The distance between source to source is zero and all other
   * distances between source and vertices are infinity. The mark is initialized
   * to false and predecessor is initialized to -1
   */

  void initialize();

  /*
   * Function getClosestUnmarkedNode returns the node which is nearest from the
   * Predecessor marked node. If the node is already marked as visited, then it search
   * for another node.
   */

  int getClosestUnmarkedNode();
  /*
   * Function calculateDistance calculates the minimum distances from the source node to
   * Other node.
   */

  void calculateDistance();
  /*
   * Function output prints the results
   */

  void output();
  void printPath(int);
};


#endif /* DIJKS_H_ */
