//Stair intstantiation

#include "SDL2/SDL.h"
#include "Stair.h"
#include "globalVars.h"

Stair::Stair(int xgrid, int ygrid)
        :NonMoving(xgrid, ygrid)
{
  size = blockSize;

//Stair sprite
  sprite.x = 373;
  sprite.y = 142;
  sprite.w = 16;
  sprite.h = 16;
}

void Stair::collision(){}
