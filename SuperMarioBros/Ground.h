//this is the Ground class, used to render Grounds

#include "NonMoving.h"

#ifndef GROUND_H
#define GROUND_H

class Ground: public NonMoving{
  public:
        Ground(int, int);//constructor
        void collision();//collision animation

};

#endif
