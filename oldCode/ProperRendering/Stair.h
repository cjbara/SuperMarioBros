//this is the Stair class, used to render Stairs

#include "NonMoving.h"

#ifndef STAIR_H
#define STAIR_H

class Stair: public NonMoving{
  public:
        Stair(int, int);//constructor
        void collision();//collision animation

};

#endif
