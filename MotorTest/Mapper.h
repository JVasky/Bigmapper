#ifndef Mapper_H
#define Mapper_H

struct coord{
  int x;
  int y;
};

class Mapper {
  coord* currentCoord;
  coord* prevCoord;
public:
  Mapper();
  ~Mapper();
  coord getCurrentCoord();
  coord getPrevCoord();
  void updateCoords(coord);
};


#endif
