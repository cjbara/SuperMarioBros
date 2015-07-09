//this is the brick class, used to render bricks

#include "NonMoving.h"

#ifndef BRICK_H
#define BRICK_H

class Brick: public NonMoving{
  public:
	Brick(int, int);//constructor
	void collision();//collision animation

};

#endif
