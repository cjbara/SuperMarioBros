//Question intstantiation

#include "SDL2/SDL.h"
#include "Question.h"
#include "globalVars.h"

Question::Question(int xgrid, int ygrid)
        :NonMoving(xgrid, ygrid)
{
  size = blockSize;

//question mark block sprite
  sprite.x = 372;
  sprite.y = 160;
  sprite.w = 16;
  sprite.h = 16;
}

void Question::collision(){
//change it to a dead question sprite
  sprite.x = 373;
  sprite.y = 65;
  sprite.w = 16;
  sprite.h = 16;
}

