//this is the Flag class, used to render Flags

#include "NonMoving.h"

#ifndef FLAG_H
#define FLAG_H

class Flag: public NonMoving{
  public:
        Flag(int, int);//constructor
        void collision();//collision animation
	void render(int,int);

};

#endif
