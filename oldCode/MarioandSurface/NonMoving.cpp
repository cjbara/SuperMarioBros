//This is the interface for the nonmoving class
#include "globalVars.h"
#include "NonMoving.h"
#include <iostream>
using namespace std;

NonMoving::NonMoving(int xgrid, int ygrid){
  position.x = (xgrid-1) * blockSize;
  position.y = (ygrid-1) * blockSize;
//set the position's width and height (overwritten in pipe)
  position.w = blockSize-5;
  position.h = blockSize;

//set the initial render height and width (overwritten in Pipe)
  renderPosition.h = blockSize;
  renderPosition.w = blockSize;

}

void NonMoving::render(int camX, int camY){
  if(position.x >= camX-2*blockSize && position.x <= camX+SCREEN_WIDTH){
    renderPosition.x = position.x - camX;
    renderPosition.y = position.y - camY;

    SDL_RenderCopyEx( gRenderer, blockSheet, &sprite, &renderPosition, 0, NULL, SDL_FLIP_NONE );
  }  
}

SDL_Rect NonMoving::getPos(){
   return position;
};
