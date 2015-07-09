//Flag intstantiation

#include "SDL2/SDL.h"
#include "Flag.h"
#include "globalVars.h"
#include <iostream>
using namespace std;

Flag::Flag(int xgrid, int ygrid)
        :NonMoving(xgrid, ygrid)
{
  size = SCREEN_HEIGHT;
  position.y = 0;
  position.h = size - blockSize;
  position.x += blockSize/2-1;
  position.w = 3;

  renderPosition.y = position.y;
  renderPosition.x = position.x;
  renderPosition.w = position.w;
  renderPosition.h = position.h;

}

void Flag::render(int camX, int camY){
  if(position.x >= camX-2*blockSize && position.x <= camX+SCREEN_WIDTH){
    renderPosition.x = position.x - camX;
    renderPosition.y = position.y - camY;
    SDL_SetRenderDrawColor( gRenderer, 0x00, 0xFF, 0x00, 0x00 );
    SDL_RenderFillRect( gRenderer, &renderPosition );
  }
}

void Flag::collision(){
  cout << "The Game is Over! You Win!" << endl;
}
