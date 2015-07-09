//brick intstantiation

#include "SDL2/SDL.h"
#include "Brick.h"
#include "globalVars.h"

Brick::Brick(int xgrid, int ygrid)
	:NonMoving(xgrid, ygrid)
{
  size = blockSize;

//brick sprite
  sprite.x = 373;
  sprite.y = 47;
  sprite.w = 16;
  sprite.h = 16;
}

void Brick::collision(){}
