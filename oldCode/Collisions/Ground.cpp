//Ground intstantiation

#include "SDL2/SDL.h"
#include "Ground.h"
#include "globalVars.h"

Ground::Ground(int xgrid, int ygrid)
        :NonMoving(xgrid, ygrid)
{
  size = blockSize;

//Ground sprite
  sprite.x = 373;
  sprite.y = 124;
  sprite.w = 16;
  sprite.h = 16;
}

void Ground::collision(){}
